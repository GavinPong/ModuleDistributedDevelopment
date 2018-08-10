#include "module_hi3531a.h"
#include "hi3531a_platform.h"
#include "hi_ui_manager.h"
#include "hi_ui_osdpic_test.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "log.h"
#include "loadbmp.h"
#include <pthread.h>
#include <unistd.h>
#include "hi_fb.h"
#include "hi_includes.h"

typedef struct _osdpic_param_s{
	hi_fb_handle_t fb_handle;
	bitmap_display_params_t src_bitmap_display_params;
	bitmap_display_params_t dst_bitmap_display_params;
}osdpic_param_t;

hi_fb_handle_t direct_fb_handle = 0;
hi_fb_handle_t touch_fb_handle = 0;
hi_fb_handle_t panel_fb_handle = 0;

pthread_t osd_direct_thread_id = 0;
uint8_t direct_thread_cmd = 0;
pthread_t osd_touch_thread_id = 0;
uint8_t touch_thread_cmd = 0;
pthread_t osd_panel_thread_id = 0;
uint8_t panel_thread_cmd = 0;



static void *osdpic_direct_thread_process(void *param)
{
	osdpic_param_t *osdpic_param_ptr = (osdpic_param_t *)param;
	uint8_t move_flag = 0;
	int32_t xpos = 0;
	int32_t ypos = 0;
	uint32_t xpos_tmp;
	uint32_t ypos_tmp;

	hi_fb_display_bitmap(osdpic_param_ptr->fb_handle, osdpic_param_ptr->src_bitmap_display_params, osdpic_param_ptr->dst_bitmap_display_params);

	while(!direct_thread_cmd)
	{
		xpos_tmp = (uint32_t)xpos;
		ypos_tmp = (uint32_t)ypos;
		osdpic_param_ptr->dst_bitmap_display_params.m_s32xpoint = xpos;
		osdpic_param_ptr->dst_bitmap_display_params.m_s32ypoint = ypos;
		hi_fb_display_bitmap(osdpic_param_ptr->fb_handle, osdpic_param_ptr->src_bitmap_display_params, osdpic_param_ptr->dst_bitmap_display_params);
		if (0 == move_flag)
		{
			if (xpos_tmp >= hi_platform_param.m_mpp_vo_dev_params[0].m_dis_width)
			{
				move_flag = 1;
				continue;
			}
			xpos += 5;
			if (ypos_tmp < hi_platform_param.m_mpp_vo_dev_params[0].m_dis_height - 50)
			{
				ypos += 3;
			}
			else
			{
				ypos = hi_platform_param.m_mpp_vo_dev_params[0].m_dis_height - 50;
			}
		}
		else if (1 == move_flag)
		{
			xpos -= 5;
			ypos -= 3;
			if (xpos < 0 || ypos < 0)
			{
				move_flag = 0;
				xpos = ypos = 0;
			}
		}
		//hi_fb_show(osdpic_param_ptr->fb_handle);
		usleep(1 * 500 * 1000);
	}
	printf("exit %s\n", __FUNCTION__);

	return NULL;
}

static void *osdpic_touch_thread_process(void *param)
{
	osdpic_param_t *osdpic_param_ptr = (osdpic_param_t *)param;
	uint8_t move_flag = 0;
	int32_t xpos = 0;
	int32_t ypos = 0;
	uint32_t xpos_tmp;
	uint32_t ypos_tmp;

	hi_fb_display_bitmap(osdpic_param_ptr->fb_handle, osdpic_param_ptr->src_bitmap_display_params, osdpic_param_ptr->dst_bitmap_display_params);

	while(!touch_thread_cmd)
	{
		xpos_tmp = (uint32_t)xpos;
		ypos_tmp = (uint32_t)ypos;
		osdpic_param_ptr->dst_bitmap_display_params.m_s32xpoint = xpos;
		osdpic_param_ptr->dst_bitmap_display_params.m_s32ypoint = ypos;
		hi_fb_display_bitmap(osdpic_param_ptr->fb_handle, osdpic_param_ptr->src_bitmap_display_params, osdpic_param_ptr->dst_bitmap_display_params);
		if (0 == move_flag)
		{
			if (xpos_tmp >= hi_platform_param.m_mpp_vo_dev_params[2].m_dis_width)
			{
				move_flag = 1;
				continue;
			}
			xpos += 5;
			if (ypos_tmp < hi_platform_param.m_mpp_vo_dev_params[2].m_dis_height - 50)
			{
				ypos += 3;
			}
			else
			{
				ypos = hi_platform_param.m_mpp_vo_dev_params[2].m_dis_height - 50;
			}
		}
		else if (1 == move_flag)
		{
			xpos -= 5;
			ypos -= 3;
			if (xpos < 0 || ypos < 0)
			{
				move_flag = 0;
				xpos = ypos = 0;
			}
		}
		//hi_fb_show(osdpic_param_ptr->fb_handle);
		usleep(1 * 500 * 1000);
#if 0
		int32_t sleep_cnt = 0;
		if (sleep_cnt++ > 10)
		{
			char *p = NULL;
			*p = 1;
		}
#endif
	}
	printf("exit %s\n", __FUNCTION__);
	return NULL;
}

static void *osdpic_panel_thread_process(void *param)
{
	osdpic_param_t *osdpic_param_ptr = (osdpic_param_t *)param;
	uint8_t move_flag = 0;
	int32_t xpos = 0;
	int32_t ypos = 0;
	uint32_t xpos_tmp;
	uint32_t ypos_tmp;

	hi_fb_display_bitmap(osdpic_param_ptr->fb_handle, osdpic_param_ptr->src_bitmap_display_params, osdpic_param_ptr->dst_bitmap_display_params);

	while(!panel_thread_cmd)
	{
		xpos_tmp = (uint32_t)xpos;
		ypos_tmp = (uint32_t)xpos;
		osdpic_param_ptr->dst_bitmap_display_params.m_s32xpoint = xpos;
		osdpic_param_ptr->dst_bitmap_display_params.m_s32ypoint = ypos;
		hi_fb_display_bitmap(osdpic_param_ptr->fb_handle, osdpic_param_ptr->src_bitmap_display_params, osdpic_param_ptr->dst_bitmap_display_params);
		if (0 == move_flag)
		{
			if (xpos_tmp >= hi_platform_param.m_mpp_vo_dev_params[2].m_dis_width)
			{
				move_flag = 1;
				continue;
			}
			xpos += 5;
			if (ypos_tmp < hi_platform_param.m_mpp_vo_dev_params[2].m_dis_height - 50)
			{
				ypos += 3;
			}
			else
			{
				ypos = hi_platform_param.m_mpp_vo_dev_params[2].m_dis_height - 50;
			}
		}
		else if (1 == move_flag)
		{
			xpos -= 5;
			ypos -= 3;
			if (xpos < 0 || ypos < 0)
			{
				move_flag = 0;
				xpos = ypos = 0;
			}
		}
		//hi_fb_show(osdpic_param_ptr->fb_handle);
		usleep(1 * 500 * 1000);
	}
	printf("exit %s\n", __FUNCTION__);

	return NULL;
}

static int32_t hi_load_bmp()
{

	return INTMODULE_HISI_OK;
}

int32_t hi_ui_osdpic_test_open(const char *pic_pathname)
{
	if (!pic_pathname)
	{
		return INTMODULE_HISI_ERR_NULL_PTR;
	}
	OSD_BITMAPFILEHEADER  bmpFileHeader;
	OSD_BITMAPINFO            bmpInfo;
	OSD_SURFACE_S Surface;
	int32_t ui_cnt = sizeof(hi_platform_param.m_ui_params) / sizeof(hi_platform_param.m_ui_params[0]);
	int32_t cycle = 0, ret = -1;
	fb_params_t fb_params;
	osdpic_param_t *osdpic_param;
	HI_U32 Phyaddr;
	HI_VOID *Viraddr;
	HI_S32 ret_value = HI_FAILURE;

	for(cycle = 0;cycle < ui_cnt;cycle++)
	{
		if (hi_platform_param.m_ui_params[cycle].m_enable)
		{
			memset(&fb_params, 0, sizeof(fb_params));
			fb_params.m_alpha_param.m_u8alpha_chn_enable = 0;
			fb_params.m_alpha_param.m_u32alpha_chn_value = 0;
			fb_params.m_alpha_param.m_u32alpha_value = 0x0;
			fb_params.m_alpha_param.m_u8alpha_enable = 1;
			fb_params.m_s32xoffset = 0;
			fb_params.m_s32xpos = 0;
			fb_params.m_s32yoffset = 0;
			fb_params.m_s32ypos = 0;
			plat_sprintf(fb_params.m_s8name, sizeof(fb_params.m_s8name),"%s", hi_platform_param.m_ui_params[cycle].m_fb_name);
			//fb_params.m_u32_stride = 0;//内部根据颜色格式自己计算
			fb_params.m_u8colorkey_enable = 0;
			fb_params.m_u32colorkey_value = 0x00;
			fb_params.m_u32virtual_width = hi_platform_param.m_mpp_vo_dev_params[cycle].m_dis_width;
			fb_params.m_u32virtual_height = hi_platform_param.m_mpp_vo_dev_params[cycle].m_dis_height;
			fb_params.m_u32width = hi_platform_param.m_mpp_vo_dev_params[cycle].m_dis_width;
			fb_params.m_u32height = hi_platform_param.m_mpp_vo_dev_params[cycle].m_dis_height;
			fb_params.m_u8bpp = 16;
			if (!strcmp(hi_platform_param.m_ui_params[cycle].m_ui_name, "direct"))
			{
				if(INTMODULE_HISI_OK != (ret = hi_fb_open(&direct_fb_handle, fb_params)))
				{
					log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:hi_fb_open %s was failed", __FUNCTION__, __LINE__, fb_params.m_s8name);
				}
				else
				{
					if(GetBmpInfo(pic_pathname, &bmpFileHeader, &bmpInfo) < 0)
					{
						return INTMODULE_HISI_FALSE;
					}
					if (HI_SUCCESS != (ret_value = HI_MPI_SYS_MmzAlloc(&Phyaddr, ((void**)&Viraddr), 
						NULL, NULL, bmpInfo.bmiHeader.biWidth * bmpInfo.bmiHeader.biHeight*2)))
					{
						log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:HI_MPI_SYS_MmzAlloc failed width:0x%x", __FUNCTION__, __LINE__, ret_value);
						return INTMODULE_HISI_ERR_NOT_NOMEM;
					} 
					osdpic_param = (osdpic_param_t *)calloc(1, sizeof(osdpic_param_t));
					osdpic_param->fb_handle = direct_fb_handle;
					osdpic_param->src_bitmap_display_params.m_alpha_value = 0;
					osdpic_param->src_bitmap_display_params.m_color_fmt = HIFB_COLOR_FMT_ARGB1555;
					osdpic_param->src_bitmap_display_params.m_enable_alpha = 1;
					osdpic_param->src_bitmap_display_params.m_s32xpoint = 0;
					osdpic_param->src_bitmap_display_params.m_s32ypoint = 0;
					osdpic_param->src_bitmap_display_params.m_u32height = bmpInfo.bmiHeader.biHeight;
					osdpic_param->src_bitmap_display_params.m_u32width = bmpInfo.bmiHeader.biWidth;
					osdpic_param->src_bitmap_display_params.m_u32operate_width = bmpInfo.bmiHeader.biWidth;
					osdpic_param->src_bitmap_display_params.m_u32operate_height = bmpInfo.bmiHeader.biHeight;     
					osdpic_param->src_bitmap_display_params.m_u32phy_addr = (uint32_t)Phyaddr;
					osdpic_param->src_bitmap_display_params.m_vir_addr = (char *)Viraddr;

					osdpic_param->dst_bitmap_display_params.m_u32operate_width = bmpInfo.bmiHeader.biWidth;
					osdpic_param->dst_bitmap_display_params.m_u32operate_height = bmpInfo.bmiHeader.biHeight;
					osdpic_param->dst_bitmap_display_params.m_color_fmt = HIFB_COLOR_FMT_ARGB1555;
					Surface.enColorFmt = OSD_COLOR_FMT_RGB1555;
					;	printf("%s->%d:height:%d width:%d\n",__FUNCTION__, __LINE__, bmpInfo.bmiHeader.biHeight,bmpInfo.bmiHeader.biWidth);
					CreateSurfaceByBitMap(pic_pathname,&Surface,(HI_U8 *)Viraddr);
					if(!pthread_create(&osd_direct_thread_id, NULL, osdpic_direct_thread_process,(void *)osdpic_param))
					{
						pthread_detach(osd_direct_thread_id);
					}
				}
			}
			else if(!strcmp(hi_platform_param.m_ui_params[cycle].m_ui_name, "touch"))
			{
				if(INTMODULE_HISI_OK != (ret = hi_fb_open(&touch_fb_handle, fb_params)))
				{
					log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:hi_fb_open %s was failed", fb_params.m_s8name);
				}
				else
				{
					if(GetBmpInfo(pic_pathname, &bmpFileHeader, &bmpInfo) < 0)
					{
						return INTMODULE_HISI_FALSE;
					}
					if (HI_SUCCESS != (ret_value = HI_MPI_SYS_MmzAlloc(&Phyaddr, ((void**)&Viraddr), 
						NULL, NULL, bmpInfo.bmiHeader.biWidth * bmpInfo.bmiHeader.biHeight*2)))
					{
						log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:HI_MPI_SYS_MmzAlloc failed width:0x%x", __FUNCTION__, __LINE__, ret_value);
						return INTMODULE_HISI_ERR_NOT_NOMEM;
					} 
					osdpic_param = (osdpic_param_t *)calloc(1, sizeof(osdpic_param_t));
					osdpic_param->fb_handle = touch_fb_handle;
					osdpic_param->src_bitmap_display_params.m_alpha_value = 0;
					osdpic_param->src_bitmap_display_params.m_color_fmt = HIFB_COLOR_FMT_ARGB1555;
					osdpic_param->src_bitmap_display_params.m_enable_alpha = 1;
					osdpic_param->src_bitmap_display_params.m_s32xpoint = 0;
					osdpic_param->src_bitmap_display_params.m_s32ypoint = 0;
					osdpic_param->src_bitmap_display_params.m_u32height = bmpInfo.bmiHeader.biHeight;
					osdpic_param->src_bitmap_display_params.m_u32width = bmpInfo.bmiHeader.biWidth;
					osdpic_param->src_bitmap_display_params.m_u32operate_width = bmpInfo.bmiHeader.biWidth;
					osdpic_param->src_bitmap_display_params.m_u32operate_height = bmpInfo.bmiHeader.biHeight;     
					osdpic_param->src_bitmap_display_params.m_u32phy_addr = (uint32_t)Phyaddr;
					osdpic_param->src_bitmap_display_params.m_vir_addr = (char *)Viraddr;
					
					osdpic_param->dst_bitmap_display_params.m_u32operate_width = bmpInfo.bmiHeader.biWidth;
					osdpic_param->dst_bitmap_display_params.m_u32operate_height = bmpInfo.bmiHeader.biHeight;
					osdpic_param->dst_bitmap_display_params.m_color_fmt = HIFB_COLOR_FMT_ARGB1555;
					Surface.enColorFmt = OSD_COLOR_FMT_RGB1555;
					printf("%s->%d:height:%d width:%d\n",__FUNCTION__, __LINE__, bmpInfo.bmiHeader.biHeight,bmpInfo.bmiHeader.biWidth);
					CreateSurfaceByBitMap(pic_pathname,&Surface,(HI_U8 *)Viraddr);
					if(!pthread_create(&osd_touch_thread_id, NULL, osdpic_touch_thread_process,(void *)osdpic_param))
						pthread_detach(osd_touch_thread_id);
				}
			}
			else if (!strcmp(hi_platform_param.m_ui_params[cycle].m_ui_name, "panel"))
			{
				if(INTMODULE_HISI_OK != hi_fb_open(&panel_fb_handle, fb_params))
				{
					log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:hi_fb_open %s was failed", __FUNCTION__, __LINE__,fb_params.m_s8name);
				}
				else
				{
					if(GetBmpInfo("./res/cursor.bmp", &bmpFileHeader, &bmpInfo) < 0)
					{
						return INTMODULE_HISI_FALSE;
					}
					if (HI_FAILURE == (ret_value = HI_MPI_SYS_MmzAlloc(&Phyaddr, ((void**)&Viraddr), 
						NULL, NULL, bmpInfo.bmiHeader.biWidth * bmpInfo.bmiHeader.biHeight*2)))
					{
						log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:HI_MPI_SYS_MmzAlloc failed width:0x%x", __FUNCTION__, __LINE__, ret_value);
						return INTMODULE_HISI_ERR_NOT_NOMEM;
					} 
					osdpic_param = (osdpic_param_t *)calloc(1, sizeof(osdpic_param_t));
					osdpic_param->fb_handle = panel_fb_handle;
					osdpic_param->src_bitmap_display_params.m_alpha_value = 0;
					osdpic_param->src_bitmap_display_params.m_color_fmt = HIFB_COLOR_FMT_ARGB1555;
					osdpic_param->src_bitmap_display_params.m_enable_alpha = 1;
					osdpic_param->src_bitmap_display_params.m_s32xpoint = 0;
					osdpic_param->src_bitmap_display_params.m_s32ypoint = 0;
					osdpic_param->src_bitmap_display_params.m_u32height = bmpInfo.bmiHeader.biHeight;
					osdpic_param->src_bitmap_display_params.m_u32width = bmpInfo.bmiHeader.biWidth;
					osdpic_param->src_bitmap_display_params.m_u32operate_width = bmpInfo.bmiHeader.biWidth;
					osdpic_param->src_bitmap_display_params.m_u32operate_height = bmpInfo.bmiHeader.biHeight;     
					osdpic_param->src_bitmap_display_params.m_u32phy_addr = (uint32_t)Phyaddr;
					osdpic_param->src_bitmap_display_params.m_vir_addr = (char *)Viraddr;

					osdpic_param->dst_bitmap_display_params.m_u32operate_width = bmpInfo.bmiHeader.biWidth;
					osdpic_param->dst_bitmap_display_params.m_u32operate_height = bmpInfo.bmiHeader.biHeight;
					osdpic_param->dst_bitmap_display_params.m_color_fmt = HIFB_COLOR_FMT_ARGB1555;
					Surface.enColorFmt = OSD_COLOR_FMT_RGB1555;
					printf("%s->%d:height:%d width:%d\n",__FUNCTION__, __LINE__, bmpInfo.bmiHeader.biHeight,bmpInfo.bmiHeader.biWidth);
					CreateSurfaceByBitMap("./res/cursor.bmp",&Surface,(HI_U8 *)Viraddr);
					if(!pthread_create(&osd_panel_thread_id, NULL, osdpic_panel_thread_process,(void *)osdpic_param))
						pthread_detach(osd_panel_thread_id);
				}
			}	
		}
	}
	return INTMODULE_HISI_OK;
}

int32_t hi_ui_osdpic_test_close()
{
	direct_thread_cmd = 1;
	touch_thread_cmd = 1;
	panel_thread_cmd = 1;

	return INTMODULE_HISI_OK;
}