#include <stdio.h>
#include <string.h>
#include "hi_mpp_vo.h"
#include "module_hi3531a.h"
#include "hi_includes.h"
#include "log.h"

#define HI_MPP_VO_PRT(fmt...)   \
	do {\
	printf("[%s]-%d: ", __FUNCTION__, __LINE__);\
	printf(fmt);\
	}while(0)

int32_t get_vo_dev_get_wh_by_intfsync(VO_INTF_SYNC_E enIntfSync, uint32_t *pu32w, uint32_t *pu32h, uint32_t *pu32frm)
{
	if (!pu32w || !pu32h || !pu32frm)
	{
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	switch (enIntfSync)
	{
	case VO_OUTPUT_PAL       :  *pu32w = 720;  *pu32h = 576;  *pu32frm = 25; break;
	case VO_OUTPUT_NTSC      :  *pu32w = 720;  *pu32h = 480;  *pu32frm = 30; break;        
	case VO_OUTPUT_576P50    :  *pu32w = 720;  *pu32h = 576;  *pu32frm = 50; break;
	case VO_OUTPUT_480P60    :  *pu32w = 720;  *pu32h = 480;  *pu32frm = 60; break;
	case VO_OUTPUT_800x600_60:  *pu32w = 800;  *pu32h = 600;  *pu32frm = 60; break;
	case VO_OUTPUT_720P50    :  *pu32w = 1280; *pu32h = 720;  *pu32frm = 50; break;
	case VO_OUTPUT_720P60    :  *pu32w = 1280; *pu32h = 720;  *pu32frm = 60; break;        
	case VO_OUTPUT_1080I50   :  *pu32w = 1920; *pu32h = 1080; *pu32frm = 50; break;
	case VO_OUTPUT_1080I60   :  *pu32w = 1920; *pu32h = 1080; *pu32frm = 60; break;
	case VO_OUTPUT_1080P24   :  *pu32w = 1920; *pu32h = 1080; *pu32frm = 24; break;        
	case VO_OUTPUT_1080P25   :  *pu32w = 1920; *pu32h = 1080; *pu32frm = 25; break;
	case VO_OUTPUT_1080P30   :  *pu32w = 1920; *pu32h = 1080; *pu32frm = 30; break;
	case VO_OUTPUT_1080P50   :  *pu32w = 1920; *pu32h = 1080; *pu32frm = 50; break;
	case VO_OUTPUT_1080P60   :  *pu32w = 1920; *pu32h = 1080; *pu32frm = 60; break;
	case VO_OUTPUT_1024x768_60:  *pu32w = 1024; *pu32h = 768;  *pu32frm = 60; break;
	case VO_OUTPUT_1280x1024_60: *pu32w = 1280; *pu32h = 1024; *pu32frm = 60; break;
	case VO_OUTPUT_1366x768_60:  *pu32w = 1366; *pu32h = 768;  *pu32frm = 60; break;
	case VO_OUTPUT_1440x900_60:  *pu32w = 1440; *pu32h = 900;  *pu32frm = 60; break;
	case VO_OUTPUT_1280x800_60:  *pu32w = 1280; *pu32h = 800;  *pu32frm = 60; break;        
	case VO_OUTPUT_1600x1200_60: *pu32w = 1600; *pu32h = 1200; *pu32frm = 60; break;
	case VO_OUTPUT_1680x1050_60: *pu32w = 1680; *pu32h = 1050; *pu32frm = 60; break;
	case VO_OUTPUT_1920x1200_60: *pu32w = 1920; *pu32h = 1200; *pu32frm = 60; break;
	case VO_OUTPUT_3840x2160_30: *pu32w = 3840; *pu32h = 2160; *pu32frm = 30; break;
	case VO_OUTPUT_3840x2160_60: *pu32w = 3840; *pu32h = 2160; *pu32frm = 60; break;
	case VO_OUTPUT_USER    :     *pu32w = 720;  *pu32h = 576;  *pu32frm = 25; break;
	default: 
		HI_MPP_VO_PRT("vo enIntfSync not support!\n");
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:vo enIntfSync not support!", __FUNCTION__, __LINE__);
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	return INTMODULE_HISI_OK;
}

static int32_t get_vo_dev_hdmi_fmt(VO_INTF_SYNC_E enIntfSync, HI_HDMI_VIDEO_FMT_E *penVideoFmt)
{
	switch (enIntfSync)
	{
	case VO_OUTPUT_PAL:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_PAL;
		break;
	case VO_OUTPUT_NTSC:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_NTSC;
		break;
	case VO_OUTPUT_1080P24:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_1080P_24;
		break;
	case VO_OUTPUT_1080P25:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_1080P_25;
		break;
	case VO_OUTPUT_1080P30:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_1080P_30;
		break;
	case VO_OUTPUT_720P50:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_720P_50;
		break;
	case VO_OUTPUT_720P60:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_720P_60;
		break;
	case VO_OUTPUT_1080I50:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_1080i_50;
		break;
	case VO_OUTPUT_1080I60:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_1080i_60;
		break;
	case VO_OUTPUT_1080P50:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_1080P_50;
		break;
	case VO_OUTPUT_1080P60:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_1080P_60;
		break;
	case VO_OUTPUT_576P50:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_576P_50;
		break;
	case VO_OUTPUT_480P60:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_480P_60;
		break;
	case VO_OUTPUT_800x600_60:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_VESA_800X600_60;
		break;
	case VO_OUTPUT_1024x768_60:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_VESA_1024X768_60;
		break;
	case VO_OUTPUT_1280x1024_60:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_VESA_1280X1024_60;
		break;
	case VO_OUTPUT_1366x768_60:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_VESA_1366X768_60;
		break;
	case VO_OUTPUT_1440x900_60:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_VESA_1440X900_60;
		break;
	case VO_OUTPUT_1280x800_60:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_VESA_1280X800_60;
		break;
	case VO_OUTPUT_1600x1200_60:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_VESA_1600X1200_60;
		break;
	case VO_OUTPUT_2560x1440_30:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_2560x1440_30;
		break;
	case VO_OUTPUT_2560x1600_60:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_2560x1600_60;
		break;
	case VO_OUTPUT_3840x2160_30:
		*penVideoFmt = HI_HDMI_VIDEO_FMT_3840X2160P_30;
		break;
	default :
		HI_MPP_VO_PRT("Unkonw VO_INTF_SYNC_E value!\n");
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
		break;
	}

	return INTMODULE_HISI_OK;
}

static int32_t get_vo_dev_pixel_format(hi_mpp_vo_pixel_format_e hi_mpp_vo_pixel_format, PIXEL_FORMAT_E *vo_pixel_format)
{
	if (!vo_pixel_format)
	{
		return INTMODULE_HISI_ERR_NULL_PTR;
	}
	switch(hi_mpp_vo_pixel_format)
	{
	case HI_MPP_VO_PIXEL_FORMAT_RGB_1BPP:
		{
			*vo_pixel_format = PIXEL_FORMAT_RGB_1BPP;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_RGB_2BPP:
		{
			*vo_pixel_format = PIXEL_FORMAT_RGB_2BPP;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_RGB_4BPP:
		{
			*vo_pixel_format = PIXEL_FORMAT_RGB_4BPP;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_RGB_8BPP:
		{
			*vo_pixel_format = PIXEL_FORMAT_RGB_8BPP;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_RGB_444:
		{
			*vo_pixel_format = PIXEL_FORMAT_RGB_444;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_RGB_4444:
		{
			*vo_pixel_format = PIXEL_FORMAT_RGB_4444;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_RGB_555:
		{
			*vo_pixel_format = PIXEL_FORMAT_RGB_555;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_RGB_565:
		{
			*vo_pixel_format = PIXEL_FORMAT_RGB_565;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_RGB_1555:
		{
			*vo_pixel_format = PIXEL_FORMAT_RGB_1555;
		}
		break;
			/*  9 reserved */
	case HI_MPP_VO_PIXEL_FORMAT_RGB_888:
		{
			*vo_pixel_format = PIXEL_FORMAT_RGB_888;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_RGB_8888:
		{
			*vo_pixel_format = PIXEL_FORMAT_RGB_8888;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_RGB_PLANAR_888:
		{
			*vo_pixel_format = PIXEL_FORMAT_RGB_PLANAR_888;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_RGB_BAYER_8BPP:
		{
			*vo_pixel_format = PIXEL_FORMAT_RGB_BAYER_8BPP;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_RGB_BAYER_10BPP:
		{
			*vo_pixel_format = PIXEL_FORMAT_RGB_BAYER_10BPP;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_RGB_BAYER_12BPP:
		{
			*vo_pixel_format = PIXEL_FORMAT_RGB_BAYER_12BPP;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_RGB_BAYER_14BPP:
		{
			*vo_pixel_format = PIXEL_FORMAT_RGB_BAYER_14BPP;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_RGB_BAYER:
		{
			*vo_pixel_format = PIXEL_FORMAT_RGB_BAYER;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_YUV_A422:
		{
			*vo_pixel_format = PIXEL_FORMAT_YUV_A422;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_YUV_A444:
		{
			*vo_pixel_format = PIXEL_FORMAT_YUV_A444;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_YUV_PLANAR_422:
		{
			*vo_pixel_format = PIXEL_FORMAT_YUV_PLANAR_422;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_YUV_PLANAR_420:
		{
			*vo_pixel_format = PIXEL_FORMAT_YUV_PLANAR_420;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_YUV_PLANAR_444:
		{
			*vo_pixel_format = PIXEL_FORMAT_YUV_PLANAR_444;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_YUV_SEMIPLANAR_422:
		{
			*vo_pixel_format = PIXEL_FORMAT_YUV_SEMIPLANAR_422;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_YUV_SEMIPLANAR_420:
		{
			*vo_pixel_format = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_YUV_SEMIPLANAR_444:
		{
			*vo_pixel_format = PIXEL_FORMAT_YUV_SEMIPLANAR_444;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_UYVY_PACKAGE_422:
		{
			*vo_pixel_format = PIXEL_FORMAT_UYVY_PACKAGE_422;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_YUYV_PACKAGE_422:
		{
			*vo_pixel_format = PIXEL_FORMAT_YUYV_PACKAGE_422;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_VYUY_PACKAGE_422:
		{
			*vo_pixel_format = PIXEL_FORMAT_VYUY_PACKAGE_422;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_YCbCr_PLANAR:
		{
			*vo_pixel_format = PIXEL_FORMAT_YCbCr_PLANAR;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_YUV_400:
		{
			*vo_pixel_format = PIXEL_FORMAT_YUV_400;
		}
		break;
	case HI_MPP_VO_PIXEL_FORMAT_BUTT:
		{
			*vo_pixel_format = PIXEL_FORMAT_BUTT;
		}
		break;
	default:
		return INTMODULE_HISI_FALSE;
		break;
	}
	return INTMODULE_HISI_OK;
}

static int32_t get_vo_dev_intf_sync(hi_mpp_vo_intf_sync_e intf_sync, VO_INTF_SYNC_E *vo_intf_sync)
{
	if (!vo_intf_sync)
	{
		return INTMODULE_HISI_ERR_NULL_PTR;
	}
	switch(intf_sync)
	{
	case HI_MPP_VO_OUTPUT_PAL:
		{
			*vo_intf_sync = VO_OUTPUT_PAL;
		}
		break;
	case HI_MPP_VO_OUTPUT_NTSC:
		{
			*vo_intf_sync = VO_OUTPUT_NTSC;
		}
		break;
	case HI_MPP_VO_OUTPUT_960H_PAL:              /* ITU-R BT.1302 960 x 576 at 50 Hz (interlaced)*/
		{
			*vo_intf_sync = VO_OUTPUT_960H_PAL;
		}
		break;	
	case HI_MPP_VO_OUTPUT_960H_NTSC:             /* ITU-R BT.1302 960 x 480 at 60 Hz (interlaced)*/
		{
			*vo_intf_sync = VO_OUTPUT_960H_NTSC;
		}
		break;
	case HI_MPP_VO_OUTPUT_1080P24:
		{
			*vo_intf_sync = VO_OUTPUT_1080P24;
		}
		break;
	case HI_MPP_VO_OUTPUT_1080P25:
		{
			*vo_intf_sync = VO_OUTPUT_1080P25;
		}
		break;
	case HI_MPP_VO_OUTPUT_1080P30:
		{
			*vo_intf_sync = VO_OUTPUT_1080P30;
		}
		break;
	case HI_MPP_VO_OUTPUT_720P50:
		{
			*vo_intf_sync = VO_OUTPUT_720P50;
		}
		break;
	case HI_MPP_VO_OUTPUT_720P60:
		{
			*vo_intf_sync = VO_OUTPUT_720P60;
		}
		break;
	case HI_MPP_VO_OUTPUT_1080I50:
		{
			*vo_intf_sync = VO_OUTPUT_1080I50;
		}
		break;
	case HI_MPP_VO_OUTPUT_1080I60:
		{
			*vo_intf_sync = VO_OUTPUT_1080I60;
		}
		break;
	case HI_MPP_VO_OUTPUT_1080P50:
		{
			*vo_intf_sync = VO_OUTPUT_1080P50;
		}
		break;
	case HI_MPP_VO_OUTPUT_1080P60:
		{
			*vo_intf_sync = VO_OUTPUT_1080P60;
		}
		break;
	case HI_MPP_VO_OUTPUT_576P50:
		{
			*vo_intf_sync = VO_OUTPUT_576P50;
		}
		break;
	case HI_MPP_VO_OUTPUT_480P60:
		{
			*vo_intf_sync = VO_OUTPUT_480P60;
		}
		break;
	case HI_MPP_VO_OUTPUT_640x480_60:            /* VESA 640 x 480 at 60 Hz (non-interlaced) CVT */
		{
			*vo_intf_sync = VO_OUTPUT_640x480_60;
		}
		break;
	case HI_MPP_VO_OUTPUT_800x600_60:            /* VESA 800 x 600 at 60 Hz (non-interlaced) */
		{
			*vo_intf_sync = VO_OUTPUT_800x600_60;
		}
		break;
	case HI_MPP_VO_OUTPUT_1024x768_60:           /* VESA 1024 x 768 at 60 Hz (non-interlaced) */
		{
			*vo_intf_sync = VO_OUTPUT_1024x768_60;
		}
		break;
	case HI_MPP_VO_OUTPUT_1280x1024_60:          /* VESA 1280 x 1024 at 60 Hz (non-interlaced) */
		{
			*vo_intf_sync = VO_OUTPUT_1280x1024_60;
		}
		break;
	case HI_MPP_VO_OUTPUT_1366x768_60:           /* VESA 1366 x 768 at 60 Hz (non-interlaced) */
		{
			*vo_intf_sync = VO_OUTPUT_1366x768_60;
		}	
		break;
	case HI_MPP_VO_OUTPUT_1440x900_60:           /* VESA 1440 x 900 at 60 Hz (non-interlaced) CVT Compliant */
		{
			*vo_intf_sync = VO_OUTPUT_1440x900_60;
		}	
		break;
	case HI_MPP_VO_OUTPUT_1280x800_60:           /* 1280*800@60Hz VGA@60Hz*/    
		{
			*vo_intf_sync = VO_OUTPUT_1280x800_60;
		}
		break;
	case HI_MPP_VO_OUTPUT_1680x1050_60:          /* VESA 1680 x 1050 at 60 Hz (non-interlaced) */
		{
			*vo_intf_sync = VO_OUTPUT_1680x1050_60;
		}	
		break;
	case HI_MPP_VO_OUTPUT_1920x2160_30:         /* 1920x2160_30 */
		{
			*vo_intf_sync = VO_OUTPUT_1920x2160_30;
		}	
		break;
	case HI_MPP_VO_OUTPUT_1600x1200_60:          /* VESA 1600 x 1200 at 60 Hz (non-interlaced) */
		{
			*vo_intf_sync = VO_OUTPUT_1600x1200_60;
		}	
		break;
	case HI_MPP_VO_OUTPUT_1920x1200_60:          /* VESA 1920 x 1600 at 60 Hz (non-interlaced) CVT (Reduced Blanking)*/ 
		{
			*vo_intf_sync = VO_OUTPUT_1920x1200_60;
		}	
		break;
	case HI_MPP_VO_OUTPUT_2560x1440_30:          /* 2560x1440_30 */
		{
			*vo_intf_sync = VO_OUTPUT_2560x1440_30;
		}	
		break;
	case HI_MPP_VO_OUTPUT_2560x1600_60:          /* 2560x1600_60 */
		{
			*vo_intf_sync = VO_OUTPUT_2560x1600_60;
		}	
		break;
	case HI_MPP_VO_OUTPUT_3840x2160_30:          /* 3840x2160_30 */
		{
			*vo_intf_sync = VO_OUTPUT_3840x2160_30;
		}	
		break;
	case HI_MPP_VO_OUTPUT_3840x2160_60:          /* 3840x2160_60 */
		{
			*vo_intf_sync = VO_OUTPUT_3840x2160_60;
		}	
		break;
	case HI_MPP_VO_OUTPUT_USER:
		{
			*vo_intf_sync = VO_OUTPUT_USER;
		}	
		break;
	case HI_MPP_VO_OUTPUT_BUTT:
		{
			*vo_intf_sync = VO_OUTPUT_BUTT;
		}
		break;
	default:
		return INTMODULE_HISI_FALSE;
		break;
	}
	return INTMODULE_HISI_OK;
}

int32_t hi_mpp_vo_get_layer_id(int32_t dev_id, int32_t *graphic_layer_id)
{
	if (dev_id < 0 || !graphic_layer_id)
	{
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	switch(dev_id)
	{
	case 0:
	case 1:
		*graphic_layer_id = dev_id;
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		*graphic_layer_id = dev_id + 1;
		break;
	default:
		return INTMODULE_HISI_ERR_INVALID_DEVID;
		break;
	}
	return INTMODULE_HISI_OK;
}

int32_t hi_mpp_vo_bind_graphic_layer(int32_t graphic_layer_id, int32_t vodev_id)
{
	if (graphic_layer_id < 0 || vodev_id < 0)
	{
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	HI_S32 s32Ret = HI_FAILURE;
	if (HI_SUCCESS != (s32Ret = HI_MPI_VO_BindGraphicLayer(graphic_layer_id, vodev_id)))
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:BindGraphicLayer vo:%d - graphic:%d failed width:0x%x", __FUNCTION__, __LINE__,graphic_layer_id, vodev_id, s32Ret);
	}
	return INTMODULE_HISI_OK;
}

int32_t hi_mpp_vo_unbind_graphic_layer(int32_t graphic_layer_id, int32_t vodev_id)
{
	if (graphic_layer_id < 0 || vodev_id < 0)
	{
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	HI_S32 s32Ret = HI_FAILURE;
	if (HI_SUCCESS != (s32Ret = HI_MPI_VO_UnBindGraphicLayer(graphic_layer_id, vodev_id)))
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:HI_MPI_VO_UnBindGraphicLayer vo:%d - graphic:%d failed width:0x%x", __FUNCTION__, __LINE__,graphic_layer_id, vodev_id, s32Ret);
		return INTMODULE_HISI_FALSE;
	}
	return INTMODULE_HISI_OK;
}

int32_t hi_mpp_start_hdmi(VO_INTF_SYNC_E enIntfSync)
{
	HI_HDMI_ATTR_S      stAttr;
	HI_HDMI_VIDEO_FMT_E enVideoFmt;
	HI_HDMI_INIT_PARA_S stHdmiPara;
	int32_t ret_value = INTMODULE_HISI_FALSE;

	if(INTMODULE_HISI_OK != (ret_value = get_vo_dev_hdmi_fmt(enIntfSync, &enVideoFmt)))
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:get_vo_dev_hdmi_fmt failed width:0x%x", __FUNCTION__, __LINE__,ret_value);
		return INTMODULE_HISI_FALSE;
	}

	stHdmiPara.pfnHdmiEventCallback = NULL;
	stHdmiPara.pCallBackArgs = NULL;
	stHdmiPara.enForceMode = HI_HDMI_FORCE_HDMI;
	HI_MPI_HDMI_Init(&stHdmiPara);

	HI_MPI_HDMI_Open(HI_HDMI_ID_0);

	HI_MPI_HDMI_GetAttr(HI_HDMI_ID_0, &stAttr);

	stAttr.bEnableHdmi = HI_TRUE;

	stAttr.bEnableVideo = HI_TRUE;
	stAttr.enVideoFmt = enVideoFmt;

	stAttr.enVidOutMode = HI_HDMI_VIDEO_MODE_YCBCR444;
	stAttr.enDeepColorMode = HI_HDMI_DEEP_COLOR_OFF;
	stAttr.bxvYCCMode = HI_FALSE;

	stAttr.bEnableAudio = HI_FALSE;
	stAttr.enSoundIntf = HI_HDMI_SND_INTERFACE_I2S;
	stAttr.bIsMultiChannel = HI_FALSE;

	stAttr.enBitDepth = HI_HDMI_BIT_DEPTH_16;

	stAttr.bEnableAviInfoFrame = HI_TRUE;
	stAttr.bEnableAudInfoFrame = HI_TRUE;
	stAttr.bEnableSpdInfoFrame = HI_FALSE;
	stAttr.bEnableMpegInfoFrame = HI_FALSE;

	stAttr.bDebugFlag = HI_FALSE;          
	stAttr.bHDCPEnable = HI_FALSE;

	stAttr.b3DEnable = HI_FALSE;

	HI_MPI_HDMI_SetAttr(HI_HDMI_ID_0, &stAttr);

	HI_MPI_HDMI_Start(HI_HDMI_ID_0);

	HI_MPP_VO_PRT("HDMI start success.\n");
	return INTMODULE_HISI_OK;
}

int32_t hi_mpp_stop_hdmi()
{
	HI_MPI_HDMI_Stop(HI_HDMI_ID_0);
	HI_MPI_HDMI_Close(HI_HDMI_ID_0);
	HI_MPI_HDMI_DeInit();

	HI_MPP_VO_PRT("HDMI stop success.\n");
	return INTMODULE_HISI_OK;
}

int32_t hi_mpp_vo_start_dev(int32_t dev_id, hi_mpp_vo_param_t vo_param)
{
	if (dev_id < 0)
	{
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	}
	int32_t VoLayer = 0;
	VO_PUB_ATTR_S stPubAttr;
	VO_VIDEO_LAYER_ATTR_S stLayerAttr;
	VO_INTF_SYNC_E  enIntfSync = VO_OUTPUT_720P50; 
	PIXEL_FORMAT_E enPixFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
	uint32_t width = 0, height = 0, frame_rate = 0; 
	int32_t graphic_layer_id = -1;
	HI_S32 ret;

	if(INTMODULE_HISI_OK != get_vo_dev_intf_sync(vo_param.m_enintf_sync, &enIntfSync))
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	if(INTMODULE_HISI_OK != get_vo_dev_pixel_format(vo_param.m_pixel_format, &enPixFormat))
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	if(INTMODULE_HISI_OK != get_vo_dev_get_wh_by_intfsync(enIntfSync, &width, &height, &frame_rate))
		return INTMODULE_HISI_ERR_ILLEGAL_PARAM;
	if (INTMODULE_HISI_OK != hi_mpp_vo_get_layer_id(dev_id, &VoLayer))
		return INTMODULE_HISI_ERR_INVALID_DEVID;
	memset(&stPubAttr, 0, sizeof(VO_PUB_ATTR_S));
	memset(&stLayerAttr, 0, sizeof(VO_VIDEO_LAYER_ATTR_S));

	stPubAttr.enIntfSync = enIntfSync;
	stPubAttr.enIntfType = vo_param.m_s32intf_type;
	stPubAttr.u32BgColor = vo_param.m_u32bg_color;

	stLayerAttr.bClusterMode = HI_FALSE;
	stLayerAttr.bDoubleFrame = HI_FALSE;
	stLayerAttr.enPixFormat = enPixFormat;
	if (vo_param.m_dis_frame_rate >= 30)
	{
		stLayerAttr.u32DispFrmRt = 30 ;//太高实际也没有什么特别之处，但会消耗更多资源
	}
	else if (vo_param.m_dis_frame_rate > 0 && vo_param.m_dis_frame_rate < 30)
	{
		stLayerAttr.u32DispFrmRt = vo_param.m_dis_frame_rate;//如果设置的比实际的小，则会浪费资源
	}
	else
	{
		return INTMODULE_HISI_ERR_FRAME_RATE;
	}
	
	stLayerAttr.stDispRect.s32X = vo_param.m_dis_xpos;
	stLayerAttr.stDispRect.s32Y = vo_param.m_dis_ypos;
	stLayerAttr.stDispRect.u32Width = vo_param.m_dis_width;
	stLayerAttr.stDispRect.u32Height = vo_param.m_dis_height;
	stLayerAttr.stImageSize.u32Width = stLayerAttr.stDispRect.u32Width;
	stLayerAttr.stImageSize.u32Height = stLayerAttr.stDispRect.u32Height;

	if(INTMODULE_HISI_OK != hi_mpp_vo_get_layer_id(dev_id, &graphic_layer_id))
		return INTMODULE_HISI_ERR_INVALID_DEVID;
	//先尝试先关闭要打开的设备以及对应的视频层，否则可能出现怪异现象
	HI_MPI_VO_DisableVideoLayer((VO_LAYER)graphic_layer_id);
	HI_MPI_VO_Disable((VO_DEV)dev_id);

	if ((ret = HI_MPI_VO_SetPubAttr((VO_DEV)dev_id, &stPubAttr)) != HI_SUCCESS)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:HI_MPI_VO_SetPubAttr void:%d failed width:0x%x", __FUNCTION__, __LINE__,dev_id, ret);
		return INTMODULE_HISI_ERR_OPEN_DEV;
	}
	if ((ret = HI_MPI_VO_Enable((VO_DEV)dev_id)) != HI_SUCCESS)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:HI_MPI_VO_Enable devid:%d failed width:0x%x", __FUNCTION__, __LINE__,dev_id, ret);
		return INTMODULE_HISI_ERR_OPEN_DEV;
	}
	if ((ret = HI_MPI_VO_SetVideoLayerAttr((VO_LAYER)VoLayer, &stLayerAttr)) != HI_SUCCESS)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:HI_MPI_VO_SetVideoLayerAttr:%d failed width:0x%x", __FUNCTION__, __LINE__, VoLayer, ret);
		HI_MPI_VO_Disable((VO_DEV)dev_id);
		return INTMODULE_HISI_ERR_OPEN_DEV;
	}
	if ((ret = HI_MPI_VO_EnableVideoLayer((VO_LAYER)VoLayer)) != HI_SUCCESS)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:HI_MPI_VO_EnableVideoLayer %d failed width:0x%x", __FUNCTION__, __LINE__,VoLayer, ret);
		HI_MPI_VO_Disable((VO_DEV)dev_id);
		return INTMODULE_HISI_ERR_OPEN_DEV;
	}
	if (HI_MPP_VO_INTF_HDMI == vo_param.m_s32intf_type)
	{
		if(INTMODULE_HISI_OK != hi_mpp_start_hdmi(enIntfSync))
		{
			HI_MPI_VO_DisableVideoLayer((VO_LAYER)VoLayer);
			HI_MPI_VO_Disable((VO_DEV)dev_id);
			return INTMODULE_HISI_ERR_OPEN_DEV;
		}
	}

	return INTMODULE_HISI_OK;
}

int32_t hi_mpp_vo_stop_dev(int32_t dev_id)
{
	int32_t VoLayer;
	if (INTMODULE_HISI_OK != hi_mpp_vo_get_layer_id(dev_id, &VoLayer))
		return INTMODULE_HISI_ERR_INVALID_DEVID;
	HI_MPI_VO_DisableVideoLayer((VO_LAYER)VoLayer);
	HI_MPI_VO_Disable((VO_DEV)dev_id);
	hi_mpp_stop_hdmi();
	return INTMODULE_HISI_OK;
}
