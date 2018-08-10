#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>
#include "module_hi3531a.h"
#include "hi_fb.h"
#include "hifb.h"
#include "filefunc.h"
#include "cJSON.h"
#include "hi_includes.h"
#include "log.h"

//none-one-double-standard
/*fb json format
{
	"buffer_cnt":"double"
}
*/

#define HI_FB_PRT(fmt...)   \
	do {\
	printf("[%s]-%d: ", __FUNCTION__, __LINE__);\
	printf(fmt);\
	}while(0)

typedef enum _hi_fb_init_status_e{
	HI_FB_STATUS_UNINIT,
	HI_FB_STATUS_INITED,
}hi_fb_init_status_e;

typedef struct _hi_fb_dev_param_s{
	fb_params_t m_fb_params;		//fb参数
	HI_U16 *m_scree_vir_addr;			//fb对应的虚拟地址
	HI_U32 m_scree_phy_addr;		//fb对应的物理地址
	HI_U32 m_scree_smen_len;		//fb帧长度
	HI_U32 m_canvas_vir_addr;		//画布虚拟地址
	HI_U32 m_canvas_phy_addr;		//画布物理地址
	HI_U32 m_canvas_smen_len;		//画布fb帧长度
}hi_fb_dev_param_t;

typedef struct _hi_fb_ctx_s{
	hi_fb_init_status_e m_eninited;				//初始化状态
	uint8_t m_u8buffer_cnt;						//fb缓存个数：0:0缓冲、1:单缓冲、2:双缓冲 3:标准
	uint8_t m_u8enable_tde;						//tde使能
}hi_fb_ctx_t;

static hi_fb_ctx_t hi_fb_ctx = {HI_FB_STATUS_UNINIT,0};
static struct fb_bitfield s_r16 = {10, 5, 0};
static struct fb_bitfield s_g16 = {5, 5, 0};
static struct fb_bitfield s_b16 = {0, 5, 0};
static struct fb_bitfield s_a16 = {15, 1, 0};

static struct fb_bitfield s_a32 = {24,8,0};
static struct fb_bitfield s_r32 = {16,8,0};
static struct fb_bitfield s_g32 = {8,8,0};
static struct fb_bitfield s_b32 = {0,8,0};

int32_t quick_copy_data(TDE2_RECT_S src_rect, TDE2_SURFACE_S src_surface, TDE2_RECT_S dst_rect, TDE2_SURFACE_S dst_surface)
{
	TDE_HANDLE s32Handle;
	HI_S32 s32Ret;

	/* 1. start job */
	s32Handle = HI_TDE2_BeginJob();
	if(HI_ERR_TDE_INVALID_HANDLE == s32Handle)
	{
		HI_FB_PRT("start job failed!\n");
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:HI_TDE2_BeginJob was failed", __FUNCTION__, __LINE__);
		return INTMODULE_HISI_FALSE;
	}

	s32Ret = HI_TDE2_QuickCopy(s32Handle, &src_surface, &src_rect,&dst_surface, &dst_rect);
	if(s32Ret < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:HI_TDE2_QuickCopy was failed width:0x%x", __FUNCTION__, __LINE__, s32Ret);
		HI_TDE2_CancelJob(s32Handle);
		return INTMODULE_HISI_FALSE;
	}

	/* 3. submit job */
	s32Ret = HI_TDE2_EndJob(s32Handle, HI_FALSE, HI_TRUE, 10);
	if(s32Ret < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:HI_TDE2_EndJob was failed width:0x%x", __FUNCTION__, __LINE__, s32Ret);
		HI_TDE2_CancelJob(s32Handle);
		return INTMODULE_HISI_FALSE;
	}
	return INTMODULE_HISI_OK;
}

//standard mode
int32_t draw_bitmap_by_standard_mode(hi_fb_handle_t hi_fb_handle, bitmap_display_params_t src_bitmap_dis_params, bitmap_display_params_t dst_bitmap_dis_params)
{
	if (!hi_fb_handle)
	{
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	hi_fb_dev_param_t *fb_dev_params_ptr = (hi_fb_dev_param_t *)hi_fb_handle;
	struct fb_var_screeninfo var;
	TDE2_RECT_S stSrcRect,stDstRect;
	TDE2_SURFACE_S stSrcSurface,stDstSurface;

	//operate rect
	stSrcRect.s32Xpos = src_bitmap_dis_params.m_s32xpoint;
	stSrcRect.s32Ypos = src_bitmap_dis_params.m_s32ypoint;
	stSrcRect.u32Width = src_bitmap_dis_params.m_u32operate_width;
	stSrcRect.u32Height = src_bitmap_dis_params.m_u32operate_height;
	stDstRect.s32Xpos = dst_bitmap_dis_params.m_s32xpoint;
	stDstRect.s32Ypos = dst_bitmap_dis_params.m_s32ypoint;
	stDstRect.u32Width = dst_bitmap_dis_params.m_u32operate_width;
	stDstRect.u32Height = dst_bitmap_dis_params.m_u32operate_height;
	//位图信息
	stSrcSurface.bAlphaMax255 = HI_TRUE;
	stSrcSurface.bAlphaExt1555 = HI_FALSE;
	stSrcSurface.u32PhyAddr = src_bitmap_dis_params.m_u32phy_addr;
	stSrcSurface.u32Stride = src_bitmap_dis_params.m_stride;
	stSrcSurface.u32Width = src_bitmap_dis_params.m_u32width;
	stSrcSurface.u32Height = src_bitmap_dis_params.m_u32height;
	if (HIFB_COLOR_FMT_ARGB1555 == src_bitmap_dis_params.m_color_fmt)
	{
		stSrcSurface.u32Stride = stSrcSurface.u32Width * 2;
		stSrcSurface.enColorFmt = TDE2_COLOR_FMT_ARGB1555;
	}
	else if (HIFB_COLOR_FMT_ARGB8888 == src_bitmap_dis_params.m_color_fmt)
	{
		stSrcSurface.u32Stride = stSrcSurface.u32Width * 4;
		stSrcSurface.enColorFmt = TDE2_COLOR_FMT_ARGB8888;
	}
	stSrcSurface.u8Alpha0 = 0xff;
	stSrcSurface.u8Alpha1 = 0xff;
	if (src_bitmap_dis_params.m_enable_alpha)
	{
		stSrcSurface.bAlphaExt1555 = HI_TRUE;
		stSrcSurface.u8Alpha1 = src_bitmap_dis_params.m_alpha_value;
	}
	if (HIFB_COLOR_FMT_ARGB1555 == dst_bitmap_dis_params.m_color_fmt)
	{
		stDstSurface.enColorFmt = TDE2_COLOR_FMT_ARGB1555;
	}
	else if (HIFB_COLOR_FMT_ARGB8888 == dst_bitmap_dis_params.m_color_fmt)
	{
		stDstSurface.enColorFmt = TDE2_COLOR_FMT_ARGB8888;
	}
	stDstSurface.u32Width = fb_dev_params_ptr->m_fb_params.m_u32virtual_width;
	stDstSurface.u32Height = fb_dev_params_ptr->m_fb_params.m_u32virtual_height;
	stDstSurface.u32Stride = fb_dev_params_ptr->m_fb_params.m_u32_stride;
	stDstSurface.u32PhyAddr = fb_dev_params_ptr->m_scree_phy_addr;
	memset((void *)fb_dev_params_ptr->m_scree_vir_addr, 0x00, fb_dev_params_ptr->m_scree_smen_len);

	if(INTMODULE_HISI_OK != quick_copy_data(stSrcRect, stSrcSurface, stDstRect, stDstSurface))
		return INTMODULE_HISI_FALSE;

	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOGET_VSCREENINFO, &var) < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOGET_VSCREENINFO was failed errno:%d", __FUNCTION__, __LINE__, errno);
		close(fb_dev_params_ptr->m_fb_params.m_s32fd);
		free(fb_dev_params_ptr);
		return INTMODULE_HISI_FALSE;
	}
	var.xres_virtual = fb_dev_params_ptr->m_fb_params.m_u32virtual_width;
	var.yres_virtual = fb_dev_params_ptr->m_fb_params.m_u32virtual_height;
	var.xres = fb_dev_params_ptr->m_fb_params.m_u32width;
	var.yres = fb_dev_params_ptr->m_fb_params.m_u32height;

	if (16 == fb_dev_params_ptr->m_fb_params.m_u8bpp)
	{
		var.transp= s_a16;
		var.red = s_r16;
		var.green = s_g16;
		var.blue = s_b16;
		var.bits_per_pixel = 16;
	}
	else if(32 == fb_dev_params_ptr->m_fb_params.m_u8bpp)
	{
		var.transp= s_a32;
		var.red = s_r32;
		var.green = s_g32;
		var.blue = s_b32;
		var.bits_per_pixel = 32;
	}
	var.activate = FB_ACTIVATE_NOW;
	var.xoffset = 0;
	var.yoffset = 0;
	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOPAN_DISPLAY, &var) < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOPAN_DISPLAY was failed errno:%d", __FUNCTION__, __LINE__, errno);
		return INTMODULE_HISI_FALSE;
	}	
	return INTMODULE_HISI_OK;
}
//double buffer mode
int32_t draw_bitmap_by_buffer_mode(hi_fb_handle_t hi_fb_handle, bitmap_display_params_t src_bitmap_dis_params, bitmap_display_params_t dst_bitmap_dis_params)
{
	if (!hi_fb_handle)
	{
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	hi_fb_dev_param_t *fb_dev_params_ptr = (hi_fb_dev_param_t *)hi_fb_handle;
	TDE2_RECT_S stSrcRect,stDstRect;
	TDE2_SURFACE_S stSrcSurface,stDstSurface;
	HIFB_BUFFER_S stCanvasBuf;
	HI_U16 *pBuf;
	HI_S32 ret_value = HI_FAILURE;

	stCanvasBuf.stCanvas.u32Height = fb_dev_params_ptr->m_fb_params.m_u32virtual_height;
	stCanvasBuf.stCanvas.u32Width = fb_dev_params_ptr->m_fb_params.m_u32virtual_width;
	if (16 == fb_dev_params_ptr->m_fb_params.m_u8bpp)
	{
		stCanvasBuf.stCanvas.u32Pitch = stCanvasBuf.stCanvas.u32Width * 2;
		stCanvasBuf.stCanvas.enFmt = HIFB_FMT_ARGB1555; 
	}
	else if(32 == fb_dev_params_ptr->m_fb_params.m_u8bpp)
	{
		stCanvasBuf.stCanvas.u32Pitch = stCanvasBuf.stCanvas.u32Width * 4;
		stCanvasBuf.stCanvas.enFmt = HIFB_FMT_ARGB8888; 
	}
	else
		return INTMODULE_HISI_FALSE;
#ifdef IMMEDIATELY
	if (HI_SUCCESS != (ret_value = HI_MPI_SYS_MmzAlloc(&(stCanvasBuf.stCanvas.u32PhyAddr), ((void**)&pBuf), 
		NULL, NULL, stCanvasBuf.stCanvas.u32Height * stCanvasBuf.stCanvas.u32Pitch)))
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:HI_MPI_SYS_MmzAlloc was failed width:0x%x", __FUNCTION__, __LINE__, ret_value);
		return INTMODULE_HISI_ERR_NOT_NOMEM;
	} 
#else
	if (0 == fb_dev_params_ptr->m_canvas_phy_addr && HI_SUCCESS != (ret_value = HI_MPI_SYS_MmzAlloc(&(stCanvasBuf.stCanvas.u32PhyAddr), ((void**)&pBuf), 
		NULL, NULL, stCanvasBuf.stCanvas.u32Height * stCanvasBuf.stCanvas.u32Pitch)))
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:HI_MPI_SYS_MmzAlloc was failed width:0x%x", __FUNCTION__, __LINE__, ret_value);
		return INTMODULE_HISI_ERR_NOT_NOMEM;
	} 
	if (fb_dev_params_ptr->m_canvas_phy_addr > 0)
	{
		stCanvasBuf.stCanvas.u32PhyAddr = fb_dev_params_ptr->m_canvas_phy_addr;
		pBuf = (HI_U16 *)fb_dev_params_ptr->m_canvas_vir_addr;
	}
	else
	{
		fb_dev_params_ptr->m_canvas_phy_addr = stCanvasBuf.stCanvas.u32PhyAddr;
		fb_dev_params_ptr->m_canvas_vir_addr = (HI_U32)pBuf;
	}
#endif
	memset(pBuf, 0x00, stCanvasBuf.stCanvas.u32Pitch*stCanvasBuf.stCanvas.u32Height);

	//operate rect
	stSrcRect.s32Xpos = src_bitmap_dis_params.m_s32xpoint;
	stSrcRect.s32Ypos = src_bitmap_dis_params.m_s32ypoint;
	stSrcRect.u32Width = src_bitmap_dis_params.m_u32operate_width;
	stSrcRect.u32Height = src_bitmap_dis_params.m_u32operate_height;
	stDstRect.s32Xpos = dst_bitmap_dis_params.m_s32xpoint;
	stDstRect.s32Ypos = dst_bitmap_dis_params.m_s32ypoint;
	stDstRect.u32Width = dst_bitmap_dis_params.m_u32operate_width;
	stDstRect.u32Height = dst_bitmap_dis_params.m_u32operate_height;
	//位图信息
	stSrcSurface.bAlphaMax255 = HI_TRUE;
	stSrcSurface.bAlphaExt1555 = HI_FALSE;
	stSrcSurface.u32PhyAddr = src_bitmap_dis_params.m_u32phy_addr;
	stSrcSurface.u32Stride = src_bitmap_dis_params.m_stride;
	stSrcSurface.u32Width = src_bitmap_dis_params.m_u32width;
	stSrcSurface.u32Height = src_bitmap_dis_params.m_u32height;
	if (HIFB_COLOR_FMT_ARGB1555 == src_bitmap_dis_params.m_color_fmt)
	{
		stSrcSurface.enColorFmt = TDE2_COLOR_FMT_ARGB1555;
		stSrcSurface.u32Stride = stSrcSurface.u32Width * 2;
	}
	else if (HIFB_COLOR_FMT_ARGB8888 == src_bitmap_dis_params.m_color_fmt)
	{
		stSrcSurface.enColorFmt = TDE2_COLOR_FMT_ARGB8888;
		stSrcSurface.u32Stride = stSrcSurface.u32Width * 4;
	}
	stSrcSurface.u8Alpha0 = 0xff;
	stSrcSurface.u8Alpha1 = 0xff;
	if (src_bitmap_dis_params.m_enable_alpha)
	{
		stSrcSurface.bAlphaExt1555 = HI_TRUE;
		stSrcSurface.u8Alpha1 = src_bitmap_dis_params.m_alpha_value;
	}
	if (HIFB_COLOR_FMT_ARGB1555 == dst_bitmap_dis_params.m_color_fmt)
	{
		stDstSurface.enColorFmt = TDE2_COLOR_FMT_ARGB1555;
	}
	else if (HIFB_COLOR_FMT_ARGB8888 == dst_bitmap_dis_params.m_color_fmt)
	{
		stDstSurface.enColorFmt = TDE2_COLOR_FMT_ARGB8888;
	}
	stDstSurface.u32Width = stCanvasBuf.stCanvas.u32Width;
	stDstSurface.u32Height = stCanvasBuf.stCanvas.u32Height;
	stDstSurface.u32Stride = stCanvasBuf.stCanvas.u32Pitch;
	stDstSurface.u32PhyAddr = stCanvasBuf.stCanvas.u32PhyAddr;
	 //quick_copy_data(stSrcRect, stSrcSurface, stDstRect, stDstSurface);
	 if(INTMODULE_HISI_OK != quick_copy_data(stSrcRect, stSrcSurface, stDstRect, stDstSurface))
		 return INTMODULE_HISI_FALSE;
	stCanvasBuf.UpdateRect.x = 0;
	stCanvasBuf.UpdateRect.y = 0;
	stCanvasBuf.UpdateRect.w = stCanvasBuf.stCanvas.u32Width;
	stCanvasBuf.UpdateRect.h = stCanvasBuf.stCanvas.u32Height;  
	if(ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIO_REFRESH, &stCanvasBuf) < 0)
	{
		HI_FB_PRT("REFRESH failed!\n");
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIO_REFRESH was failed errno:%d", __FUNCTION__, __LINE__, errno);
#ifdef IMMEDIATELY
		HI_MPI_SYS_MmzFree(stCanvasBuf.stCanvas.u32PhyAddr, pBuf);
		fb_dev_params_ptr->m_canvas_vir_addr = NULL
		fb_dev_params_ptr->m_canvas_phy_addr = 0;
#endif
		return INTMODULE_HISI_FALSE;
	}
	return INTMODULE_HISI_OK;
}

//初始化fb
int32_t  hi_fb_init()
{
	if (HI_FB_STATUS_INITED == hi_fb_ctx.m_eninited)
	{
		return INTMODULE_HISI_ERR_BUSY;
	}
	HI_S32 ret_value = HI_FAILURE;

	hi_fb_ctx.m_u8enable_tde = 1;
	if (hi_fb_ctx.m_u8enable_tde)
	{
		if((ret_value = HI_TDE2_Open()) < 0)
		{
			log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIO_REFRESH was failed width:0x%x", __FUNCTION__, __LINE__, ret_value);
			hi_fb_ctx.m_u8enable_tde = 0;
		}
	}
	hi_fb_ctx.m_eninited = HI_FB_STATUS_INITED;
	cJSON *fb_cfg_root_json, *tmp_json;
	if(FILE_FUNC_OK != FILE_FUNC_Get_Json_Form_File("/mnt/mtd/fbcfg.json", &fb_cfg_root_json))
	{
		hi_fb_ctx.m_eninited = HI_FB_STATUS_UNINIT;
		return INTMODULE_HISI_ERR_NOT_CONFIG;
	}
	tmp_json = cJSON_GetObjectItem(fb_cfg_root_json, "buffer_cnt");
	if (!tmp_json)
	{
		hi_fb_ctx.m_eninited = HI_FB_STATUS_UNINIT;
		return INTMODULE_HISI_ERR_NOT_CONFIG;
	}
	if (!strcmp(tmp_json->valuestring,"double"))
	{
		hi_fb_ctx.m_u8buffer_cnt = 2;
	}
	else if (!strcmp(tmp_json->valuestring,"one"))
	{
		hi_fb_ctx.m_u8buffer_cnt = 1;
	}
	else if (!strcmp(tmp_json->valuestring,"none"))
	{
		hi_fb_ctx.m_u8buffer_cnt = 0;
	}
	else if (!strcmp(tmp_json->valuestring,"standard"))
	{
		hi_fb_ctx.m_u8buffer_cnt = 3;
	}
	else
		hi_fb_ctx.m_u8buffer_cnt = 3;
	cJSON_Delete(fb_cfg_root_json);
	return INTMODULE_HISI_OK;
}

//反初始化fb
int32_t  hi_fb_uninit()
{
	hi_fb_ctx.m_eninited = HI_FB_STATUS_UNINIT;
	if (1 == hi_fb_ctx.m_u8enable_tde)
	{
		HI_TDE2_Close();
	}
	return INTMODULE_HISI_OK;
}

//初始化fb设备
int32_t  hi_fb_open(hi_fb_handle_t *hi_fb_handle, fb_params_t fb_params)
{
	if (HI_FB_STATUS_INITED != hi_fb_ctx.m_eninited)
	{
		return INTMODULE_HISI_ERR_SYS_NOTREADY;
	}
	if (!hi_fb_handle)
	{
		return INTMODULE_HISI_ERR_NULL_PTR;
	}
	if (access(fb_params.m_s8name, F_OK))
	{
		return INTMODULE_HISI_ERR_UNEXIST;
	}
	HI_BOOL bShow = HI_FALSE;
	HIFB_POINT_S stPoint = {0, 0};
	struct fb_fix_screeninfo fix;
	struct fb_var_screeninfo var;
	HIFB_LAYER_INFO_S stLayerInfo;
	memset(&stLayerInfo, 0, sizeof(HIFB_LAYER_INFO_S));
	hi_fb_dev_param_t *fb_dev_params_ptr = (hi_fb_dev_param_t *)calloc(1, sizeof(hi_fb_dev_param_t));
	if (!fb_dev_params_ptr)
	{
		return INTMODULE_HISI_ERR_NOT_NOMEM;
	}
	memcpy(&fb_dev_params_ptr->m_fb_params, &fb_params, sizeof(fb_dev_params_ptr->m_fb_params));
	fb_dev_params_ptr->m_fb_params.m_s32fd = open(fb_params.m_s8name, O_RDWR, 0);
	if (fb_dev_params_ptr->m_fb_params.m_s32fd < 0)
	{
		free(fb_dev_params_ptr);
		return INTMODULE_HISI_ERR_OPEN_DEV;
	}
	/* 3. get the variable screen info */
	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOGET_VSCREENINFO, &var) < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOGET_VSCREENINFO was failed errno:%d", __FUNCTION__, __LINE__, errno);
		close(fb_dev_params_ptr->m_fb_params.m_s32fd);
		free(fb_dev_params_ptr);
		return INTMODULE_HISI_FALSE;
	}
	/* 4. modify the variable screen info
          the screen size: IMAGE_WIDTH*IMAGE_HEIGHT
          the virtual screen size: VIR_SCREEN_WIDTH*VIR_SCREEN_HEIGHT
          (which equals to VIR_SCREEN_WIDTH*(IMAGE_HEIGHT*2))
          the pixel format: ARGB1555
    */
    usleep(2*1000*1000);
	var.xres_virtual = fb_params.m_u32virtual_width;
	var.yres_virtual = fb_params.m_u32virtual_height;
	var.xres = fb_params.m_u32width;
	var.yres = fb_params.m_u32height;
	if (16 == fb_params.m_u8bpp)
	{
		var.transp= s_a16;
		var.red = s_r16;
		var.green = s_g16;
		var.blue = s_b16;
		var.bits_per_pixel = 16;
	}
	else if(32 == fb_params.m_u8bpp)
	{
		var.transp= s_a32;
		var.red = s_r32;
		var.green = s_g32;
		var.blue = s_b32;
		var.bits_per_pixel = 32;
	}
    var.activate = FB_ACTIVATE_NOW;
	/* 5. set the variable screeninfo */
	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOPUT_VSCREENINFO, &var) < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOPUT_VSCREENINFO was failed errno:%d", __FUNCTION__, __LINE__, errno);
		close(fb_dev_params_ptr->m_fb_params.m_s32fd);
		free(fb_dev_params_ptr);
		return INTMODULE_HISI_FALSE;
	}
	stPoint.s32XPos = fb_params.m_s32xpos;
	stPoint.s32XPos = fb_params.m_s32ypos;
	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOPUT_SCREEN_ORIGIN_HIFB, &stPoint) < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOPUT_SCREEN_ORIGIN_HIFB was failed errno:%d", __FUNCTION__, __LINE__, errno);
		close(fb_dev_params_ptr->m_fb_params.m_s32fd);
		free(fb_dev_params_ptr);
		return INTMODULE_HISI_FALSE;
	}
	switch (hi_fb_ctx.m_u8buffer_cnt)
	{
	case 0 :
		{  
			stLayerInfo.BufMode = HIFB_LAYER_BUF_NONE;
			stLayerInfo.u32Mask = HIFB_LAYERMASK_BUFMODE;
			break;
		}

	case 1 :
		{
			stLayerInfo.BufMode = HIFB_LAYER_BUF_ONE;
			stLayerInfo.u32Mask = HIFB_LAYERMASK_BUFMODE;
			break;
		}
	case 2 :
		{
			stLayerInfo.BufMode = HIFB_LAYER_BUF_DOUBLE;
			stLayerInfo.u32Mask = HIFB_LAYERMASK_BUFMODE;
			break;
		}
	default:
		{
			stLayerInfo.BufMode = HIFB_LAYER_BUF_DOUBLE;
			stLayerInfo.u32Mask = HIFB_LAYERMASK_BUFMODE;
		}		
	}
	if (hi_fb_ctx.m_u8buffer_cnt != 3)
	{
		if(ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOPUT_LAYER_INFO, &stLayerInfo) < 0)
		{
			log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOPUT_LAYER_INFO was failed errno:%d", __FUNCTION__, __LINE__, errno);
			close(fb_dev_params_ptr->m_fb_params.m_s32fd);
			free(fb_dev_params_ptr);
			return INTMODULE_HISI_FALSE;
		} 
	}
	bShow = HI_FALSE;
	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOPUT_SHOW_HIFB, &bShow) < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOPUT_SHOW_HIFB was failed errno:%d", __FUNCTION__, __LINE__, errno);
		close(fb_dev_params_ptr->m_fb_params.m_s32fd);
		free(fb_dev_params_ptr);
		return INTMODULE_HISI_FALSE;
	}
	/* 6. get the fix screen info */
	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOGET_FSCREENINFO, &fix) < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOGET_FSCREENINFO was failed errno:%d", __FUNCTION__, __LINE__, errno);
		close(fb_dev_params_ptr->m_fb_params.m_s32fd);
		free(fb_dev_params_ptr);
		return INTMODULE_HISI_FALSE;
	}
	fb_dev_params_ptr->m_fb_params.m_u32_stride = fix.line_length;
	fb_dev_params_ptr->m_scree_vir_addr = (HI_U16 *)mmap(HI_NULL, fix.smem_len, PROT_READ|PROT_WRITE, MAP_SHARED, fb_dev_params_ptr->m_fb_params.m_s32fd, 0);
	if(MAP_FAILED == (void *)(fb_dev_params_ptr->m_scree_vir_addr))
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:mmap was failed", __FUNCTION__, __LINE__);
		close(fb_dev_params_ptr->m_fb_params.m_s32fd);
		free(fb_dev_params_ptr);
		return INTMODULE_HISI_FALSE;

	}
	fb_dev_params_ptr->m_scree_phy_addr = fix.smem_start;
	fb_dev_params_ptr->m_scree_smen_len = fix.smem_len;
	memset((void *)fb_dev_params_ptr->m_scree_vir_addr, 0x00, fix.smem_len);
	/* time to play*/
	bShow = HI_TRUE;
	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOPUT_SHOW_HIFB, &bShow) < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOPUT_SHOW_HIFB was failed errno:%d", __FUNCTION__, __LINE__, errno);
		munmap((void *)fb_dev_params_ptr->m_scree_vir_addr, fix.smem_len);
		close(fb_dev_params_ptr->m_fb_params.m_s32fd);
		free(fb_dev_params_ptr);
		return INTMODULE_HISI_FALSE;
	}
	*hi_fb_handle = (void *)fb_dev_params_ptr;
	return INTMODULE_HISI_OK;
}

//反初始化fb设备
int32_t  hi_fb_close(hi_fb_handle_t hi_fb_handle)
{
	if (!hi_fb_handle)
	{
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	hi_fb_dev_param_t *fb_dev_params_ptr = (hi_fb_dev_param_t *)hi_fb_handle;
	HI_BOOL bShow = HI_FALSE;
	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOPUT_SHOW_HIFB, &bShow) < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOPUT_SHOW_HIFB was failed errno:%d", __FUNCTION__, __LINE__, errno);
	}
	if (fb_dev_params_ptr->m_fb_params.m_s32fd > 0)
	{
		close(fb_dev_params_ptr->m_fb_params.m_s32fd);
	}
	if (fb_dev_params_ptr->m_scree_vir_addr != 0 && fb_dev_params_ptr->m_scree_smen_len > 0)
	{
		munmap((void *)fb_dev_params_ptr->m_scree_vir_addr, fb_dev_params_ptr->m_scree_smen_len);
	}
	if (fb_dev_params_ptr->m_canvas_phy_addr > 0 && fb_dev_params_ptr->m_canvas_vir_addr > 0)
	{
		HI_VOID * pBuf = (HI_VOID *)fb_dev_params_ptr->m_canvas_vir_addr;
		HI_MPI_SYS_MmzFree(fb_dev_params_ptr->m_canvas_phy_addr, pBuf);
	}
	free(fb_dev_params_ptr);
	return INTMODULE_HISI_OK;
}

//显示图层
int32_t  hi_fb_show(hi_fb_handle_t hi_fb_handle)
{
	if (!hi_fb_handle)
	{
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	hi_fb_dev_param_t *fb_dev_params_ptr = (hi_fb_dev_param_t *)hi_fb_handle;
	HI_BOOL bshow = HI_TRUE;
	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOPUT_SHOW_HIFB, &bshow) < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOPUT_SHOW_HIFB was failed errno:%d", __FUNCTION__, __LINE__, errno);
		return INTMODULE_HISI_ERR_UNEXIST;
	}
	return INTMODULE_HISI_OK;
}

//隐藏图层
int32_t  hi_fb_hide(hi_fb_handle_t hi_fb_handle)
{
	if (!hi_fb_handle)
	{
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	hi_fb_dev_param_t *fb_dev_params_ptr = (hi_fb_dev_param_t *)hi_fb_handle;
	HI_BOOL bshow = HI_FALSE;
	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOPUT_SHOW_HIFB, &bshow) < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOPUT_SHOW_HIFB was failed errno:%d", __FUNCTION__, __LINE__, errno);
		return INTMODULE_HISI_ERR_UNEXIST;
	}
	return INTMODULE_HISI_OK;
}

//清屏
int32_t  hi_fb_clear_screen(hi_fb_handle_t hi_fb_handle)
{
	if (!hi_fb_handle)
	{
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	hi_fb_dev_param_t *fb_dev_params_ptr = (hi_fb_dev_param_t *)hi_fb_handle;
	void *pShowScreen = (void *)fb_dev_params_ptr->m_scree_vir_addr;

	memset(pShowScreen, 0, fb_dev_params_ptr->m_scree_smen_len);
	return INTMODULE_HISI_OK;
}

//获取colorkey值
int32_t	 hi_fb_get_colorkey_value(hi_fb_handle_t hi_fb_handle, hi_fb_colorkey_param_t *colorkey_param)
{
	if (!hi_fb_handle || !colorkey_param)
	{
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	hi_fb_dev_param_t *fb_dev_params_ptr = (hi_fb_dev_param_t *)hi_fb_handle;
	HIFB_COLORKEY_S stColorKey;

	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOGET_COLORKEY_HIFB, &stColorKey) < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOGET_COLORKEY_HIFB was failed errno:%d", __FUNCTION__, __LINE__, errno);
		return INTMODULE_HISI_FALSE;
	}
	colorkey_param->m_u8enable = stColorKey.bKeyEnable;
	colorkey_param->m_u8value = stColorKey.u32Key;
	return INTMODULE_HISI_OK;
}

//设置colorkey值
int32_t	 hi_fb_set_colorkey_value(hi_fb_handle_t hi_fb_handle, hi_fb_colorkey_param_t colorkey_param)
{
	if (!hi_fb_handle)
	{
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	hi_fb_dev_param_t *fb_dev_params_ptr = (hi_fb_dev_param_t *)hi_fb_handle;
	HIFB_COLORKEY_S stColorKey;
	stColorKey.bKeyEnable = (HI_BOOL)colorkey_param.m_u8enable;
	stColorKey.u32Key = colorkey_param.m_u8value;
	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOPUT_COLORKEY_HIFB, &stColorKey) < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOPUT_COLORKEY_HIFB was failed errno:%d", __FUNCTION__, __LINE__, errno);
		return INTMODULE_HISI_FALSE;
	}
	return INTMODULE_HISI_OK;
}

//获取alpha值
int32_t	 hi_fb_get_alpha_value(hi_fb_handle_t hi_fb_handle, hi_fb_alpha_params_t *alpha_params)
{
	if (!hi_fb_handle || !alpha_params)
	{
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	HIFB_ALPHA_S stAlpha;
	hi_fb_dev_param_t *fb_dev_params_ptr = (hi_fb_dev_param_t *)hi_fb_handle;
	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOGET_ALPHA_HIFB,  &stAlpha))
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOGET_ALPHA_HIFB was failed errno:%d", __FUNCTION__, __LINE__, errno);
		return INTMODULE_HISI_FALSE;
	}
	alpha_params->m_u32alpha_chn_value = stAlpha.u8GlobalAlpha;
	alpha_params->m_u8alpha_chn_enable = stAlpha.bAlphaChannel;
	alpha_params->m_u8alpha_enable = stAlpha.bAlphaEnable;
	alpha_params->m_u32alpha_value = stAlpha.u8Alpha1;

	return INTMODULE_HISI_OK;
}

//设置alpha值
int32_t	 hi_fb_set_alpha_value(hi_fb_handle_t hi_fb_handle, hi_fb_alpha_params_t alpha_params)
{
	if (!hi_fb_handle)
	{
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	HIFB_ALPHA_S stAlpha;
	hi_fb_dev_param_t *fb_dev_params_ptr = (hi_fb_dev_param_t *)hi_fb_handle;
	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOGET_ALPHA_HIFB,  &stAlpha))
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOGET_ALPHA_HIFB was failed errno:%d", __FUNCTION__, __LINE__, errno);
		return INTMODULE_HISI_FALSE;
	}
	stAlpha.u8GlobalAlpha = alpha_params.m_u32alpha_chn_value;
	stAlpha.bAlphaChannel = (HI_BOOL)alpha_params.m_u8alpha_chn_enable;
	stAlpha.bAlphaEnable = (HI_BOOL)alpha_params.m_u8alpha_enable;
	stAlpha.u8Alpha1 = alpha_params.m_u32alpha_value;
	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOPUT_ALPHA_HIFB,  &stAlpha) < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOPUT_ALPHA_HIFB was failed errno:%d", __FUNCTION__, __LINE__, errno);
		return INTMODULE_HISI_FALSE;
	}
	return INTMODULE_HISI_OK;
}

//获取fb设备显示的起始位置
int32_t  hi_fb_get_origin_position(hi_fb_handle_t hi_fb_handle, int32_t *x, int32_t *y)
{
	if (!hi_fb_handle || !x || !y)
	{
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	hi_fb_dev_param_t *fb_dev_params_ptr = (hi_fb_dev_param_t *)hi_fb_handle;
	HIFB_POINT_S stPoint = {0};
	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOGET_SCREEN_ORIGIN_HIFB, &stPoint) < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOGET_SCREEN_ORIGIN_HIFB was failed errno:%d", __FUNCTION__, __LINE__, errno);
		return INTMODULE_HISI_FALSE;
	}
	*x = stPoint.s32XPos;
	*y = stPoint.s32YPos;

	return INTMODULE_HISI_OK;
}

//设置fb设备显示的起始位置
int32_t  hi_fb_set_origin_position(hi_fb_handle_t hi_fb_handle, int32_t x, int32_t y)
{
	if (!hi_fb_handle || x < 0 || y < 0)
	{
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	hi_fb_dev_param_t *fb_dev_params_ptr = (hi_fb_dev_param_t *)hi_fb_handle;
	HIFB_POINT_S stPoint = {0};
	stPoint.s32XPos = x;
	stPoint.s32YPos = y;
	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOPUT_SCREEN_ORIGIN_HIFB, &stPoint) < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOPUT_SCREEN_ORIGIN_HIFB was failed errno:%d", __FUNCTION__, __LINE__, errno);
		return INTMODULE_HISI_FALSE;
	}

	return INTMODULE_HISI_OK;
}
//显示位图
int32_t  hi_fb_display_bitmap(hi_fb_handle_t hi_fb_handle, bitmap_display_params_t src_bitmap_dis_params, bitmap_display_params_t dst_bitmap_dis_params)
{
	if (0 == hi_fb_ctx.m_u8buffer_cnt || \
		1 == hi_fb_ctx.m_u8buffer_cnt || \
		2 == hi_fb_ctx.m_u8buffer_cnt)
	{
		draw_bitmap_by_buffer_mode(hi_fb_handle, src_bitmap_dis_params, dst_bitmap_dis_params);
	}
	else
	{
		draw_bitmap_by_standard_mode(hi_fb_handle, src_bitmap_dis_params, dst_bitmap_dis_params);
	}
	return INTMODULE_HISI_OK;
}

//获取FB的ID号
int32_t  hi_fb_query_graphic_layer_id_by_name(char *dev_name, int32_t *graphic_layer_id)
{
	if (!dev_name || !graphic_layer_id)
	{
		return INTMODULE_HISI_ERR_NULL_PTR;
	}
	//31a的图层ID表 start
	if (strstr(dev_name, "fb0"))
	{
		*graphic_layer_id = 0;
	}
	else if (strstr(dev_name, "fb1"))
	{
		*graphic_layer_id = 4;
	}
	else if (strstr(dev_name, "fb2"))
	{
		*graphic_layer_id = 1;
	}
	else if (strstr(dev_name, "fb3"))
	{
		*graphic_layer_id = 2;
	}
	else if (strstr(dev_name, "fb4"))
	{
		*graphic_layer_id = 3;
	}
	//31a的图层ID表 end
	return INTMODULE_HISI_OK;
}

//获取屏幕信息
int32_t hi_fb_get_screen_info(hi_fb_handle_t hi_fb_handle, hi_fb_screen_info_t *hi_fb_screen_info)
{
	if (!hi_fb_handle || !hi_fb_screen_info)
	{
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	struct fb_var_screeninfo var;
	hi_fb_dev_param_t *fb_dev_params_ptr = (hi_fb_dev_param_t *)hi_fb_handle;
	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOGET_VSCREENINFO, &var) < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOGET_VSCREENINFO was failed errno:%d", __FUNCTION__, __LINE__, errno);
		close(fb_dev_params_ptr->m_fb_params.m_s32fd);
		free(fb_dev_params_ptr);
		return INTMODULE_HISI_FALSE;
	}
	return INTMODULE_HISI_OK;
}

//设置屏幕信息（暂时无效）
int32_t hi_fb_set_screen_info(hi_fb_handle_t hi_fb_handle, hi_fb_screen_info_t hi_fb_screen_info)
{
	if (!hi_fb_handle)
	{
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	struct fb_var_screeninfo var;
	hi_fb_dev_param_t *fb_dev_params_ptr = (hi_fb_dev_param_t *)hi_fb_handle;
	/* 3. get the variable screen info */
	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOGET_VSCREENINFO, &var) < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOGET_VSCREENINFO was failed errno:%d", __FUNCTION__, __LINE__, errno);
		close(fb_dev_params_ptr->m_fb_params.m_s32fd);
		free(fb_dev_params_ptr);
		return INTMODULE_HISI_FALSE;
	}
	    /* 4. modify the variable screen info
          the screen size: IMAGE_WIDTH*IMAGE_HEIGHT
          the virtual screen size: VIR_SCREEN_WIDTH*VIR_SCREEN_HEIGHT
          (which equals to VIR_SCREEN_WIDTH*(IMAGE_HEIGHT*2))
          the pixel format: ARGB1555
    */
    usleep(4*1000*1000);
	var.xres_virtual = hi_fb_screen_info.m_u32vir_width;
	var.yres_virtual = hi_fb_screen_info.m_u32vir_height;
	var.xres = hi_fb_screen_info.m_u32width;
	var.yres = hi_fb_screen_info.m_u32height;

	if (16 == fb_dev_params_ptr->m_fb_params.m_u8bpp)
	{
		var.transp= s_a16;
		var.red = s_r16;
		var.green = s_g16;
		var.blue = s_b16;
		var. bits_per_pixel= 16;
	}
	else if(32 == fb_dev_params_ptr->m_fb_params.m_u8bpp)
	{
		var.transp= s_a32;
		var.red = s_r32;
		var.green = s_g32;
		var.blue = s_b32;
		var.bits_per_pixel = 32;
	}
    var.activate = FB_ACTIVATE_NOW;
	/* 5. set the variable screeninfo */
	if (ioctl(fb_dev_params_ptr->m_fb_params.m_s32fd, FBIOPUT_VSCREENINFO, &var) < 0)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:FBIOPUT_VSCREENINFO was failed errno:%d", __FUNCTION__, __LINE__, errno);
		close(fb_dev_params_ptr->m_fb_params.m_s32fd);
		free(fb_dev_params_ptr);
		return INTMODULE_HISI_FALSE;
	}
	return INTMODULE_HISI_OK;
}