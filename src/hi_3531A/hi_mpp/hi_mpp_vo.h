#ifndef __HI_MPP_VO_H__
#define __HI_MPP_VO_H__

#include "cross_platform.h"

typedef enum _hi_mpp_vo_intf_sync_e
{
	HI_MPP_VO_OUTPUT_PAL = 0,
	HI_MPP_VO_OUTPUT_NTSC,
	HI_MPP_VO_OUTPUT_960H_PAL,              /* ITU-R BT.1302 960 x 576 at 50 Hz (interlaced)*/
	HI_MPP_VO_OUTPUT_960H_NTSC,             /* ITU-R BT.1302 960 x 480 at 60 Hz (interlaced)*/

	HI_MPP_VO_OUTPUT_1080P24,
	HI_MPP_VO_OUTPUT_1080P25,
	HI_MPP_VO_OUTPUT_1080P30,

	HI_MPP_VO_OUTPUT_720P50, 
	HI_MPP_VO_OUTPUT_720P60,   
	HI_MPP_VO_OUTPUT_1080I50,
	HI_MPP_VO_OUTPUT_1080I60,    
	HI_MPP_VO_OUTPUT_1080P50,
	HI_MPP_VO_OUTPUT_1080P60,            

	HI_MPP_VO_OUTPUT_576P50,
	HI_MPP_VO_OUTPUT_480P60,

	HI_MPP_VO_OUTPUT_640x480_60,            /* VESA 640 x 480 at 60 Hz (non-interlaced) CVT */
	HI_MPP_VO_OUTPUT_800x600_60,            /* VESA 800 x 600 at 60 Hz (non-interlaced) */
	HI_MPP_VO_OUTPUT_1024x768_60,           /* VESA 1024 x 768 at 60 Hz (non-interlaced) */
	HI_MPP_VO_OUTPUT_1280x1024_60,          /* VESA 1280 x 1024 at 60 Hz (non-interlaced) */
	HI_MPP_VO_OUTPUT_1366x768_60,           /* VESA 1366 x 768 at 60 Hz (non-interlaced) */
	HI_MPP_VO_OUTPUT_1440x900_60,           /* VESA 1440 x 900 at 60 Hz (non-interlaced) CVT Compliant */
	HI_MPP_VO_OUTPUT_1280x800_60,           /* 1280*800@60Hz VGA@60Hz*/    
	HI_MPP_VO_OUTPUT_1680x1050_60,          /* VESA 1680 x 1050 at 60 Hz (non-interlaced) */
	HI_MPP_VO_OUTPUT_1920x2160_30,          /* 1920x2160_30 */
	HI_MPP_VO_OUTPUT_1600x1200_60,          /* VESA 1600 x 1200 at 60 Hz (non-interlaced) */
	HI_MPP_VO_OUTPUT_1920x1200_60,          /* VESA 1920 x 1600 at 60 Hz (non-interlaced) CVT (Reduced Blanking)*/ 
	HI_MPP_VO_OUTPUT_2560x1440_30,          /* 2560x1440_30 */
	HI_MPP_VO_OUTPUT_2560x1600_60,          /* 2560x1600_60 */
	HI_MPP_VO_OUTPUT_3840x2160_30,          /* 3840x2160_30 */
	HI_MPP_VO_OUTPUT_3840x2160_60,          /* 3840x2160_60 */
	HI_MPP_VO_OUTPUT_USER,
	HI_MPP_VO_OUTPUT_BUTT
} hi_mpp_vo_intf_sync_e;

typedef enum _hi_mpp_vo_pixel_format_e
{   
	HI_MPP_VO_PIXEL_FORMAT_RGB_1BPP = 0,
	HI_MPP_VO_PIXEL_FORMAT_RGB_2BPP,
	HI_MPP_VO_PIXEL_FORMAT_RGB_4BPP,
	HI_MPP_VO_PIXEL_FORMAT_RGB_8BPP,    
	HI_MPP_VO_PIXEL_FORMAT_RGB_444,

	HI_MPP_VO_PIXEL_FORMAT_RGB_4444,
	HI_MPP_VO_PIXEL_FORMAT_RGB_555,
	HI_MPP_VO_PIXEL_FORMAT_RGB_565,
	HI_MPP_VO_PIXEL_FORMAT_RGB_1555,

	/*  9 reserved */
	HI_MPP_VO_PIXEL_FORMAT_RGB_888,    
	HI_MPP_VO_PIXEL_FORMAT_RGB_8888,

	HI_MPP_VO_PIXEL_FORMAT_RGB_PLANAR_888,
	HI_MPP_VO_PIXEL_FORMAT_RGB_BAYER_8BPP,
	HI_MPP_VO_PIXEL_FORMAT_RGB_BAYER_10BPP,
	HI_MPP_VO_PIXEL_FORMAT_RGB_BAYER_12BPP,
	HI_MPP_VO_PIXEL_FORMAT_RGB_BAYER_14BPP,

	HI_MPP_VO_PIXEL_FORMAT_RGB_BAYER,         /* 16 bpp */

	HI_MPP_VO_PIXEL_FORMAT_YUV_A422,
	HI_MPP_VO_PIXEL_FORMAT_YUV_A444,

	HI_MPP_VO_PIXEL_FORMAT_YUV_PLANAR_422,
	HI_MPP_VO_PIXEL_FORMAT_YUV_PLANAR_420,

	HI_MPP_VO_PIXEL_FORMAT_YUV_PLANAR_444,

	HI_MPP_VO_PIXEL_FORMAT_YUV_SEMIPLANAR_422,
	HI_MPP_VO_PIXEL_FORMAT_YUV_SEMIPLANAR_420,
	HI_MPP_VO_PIXEL_FORMAT_YUV_SEMIPLANAR_444,

	HI_MPP_VO_PIXEL_FORMAT_UYVY_PACKAGE_422,
	HI_MPP_VO_PIXEL_FORMAT_YUYV_PACKAGE_422,
	HI_MPP_VO_PIXEL_FORMAT_VYUY_PACKAGE_422,
	HI_MPP_VO_PIXEL_FORMAT_YCbCr_PLANAR,

	HI_MPP_VO_PIXEL_FORMAT_YUV_400,

	HI_MPP_VO_PIXEL_FORMAT_BUTT   
} hi_mpp_vo_pixel_format_e;

#define HI_MPP_VO_INTF_CVBS     (0x01L<<0)
#define HI_MPP_VO_INTF_YPBPR    (0x01L<<1)
#define HI_MPP_VO_INTF_VGA      (0x01L<<2)
#define HI_MPP_VO_INTF_BT656    (0x01L<<3)
#define HI_MPP_VO_INTF_BT1120   (0x01L<<4)
#define HI_MPP_VO_INTF_HDMI     (0x01L<<5)
#define HI_MPP_VO_INTF_LCD      (0x01L<<6)
#define HI_MPP_VO_INTF_BT656_H  (0x01L<<7)
#define HI_MPP_VO_INTF_BT656_L  (0x01L<<8)

typedef struct _hi_mpp_vo_param_s{
	int32_t m_devid;		//设备id号
	hi_mpp_vo_intf_sync_e m_enintf_sync;	//接口时序
	int32_t m_s32intf_type;	//接口类型
	uint32_t m_u32bg_color;	//背景颜色
	hi_mpp_vo_pixel_format_e m_pixel_format;	//像素格式
	uint32_t m_dis_frame_rate;	//显示帧率
	int32_t m_dis_xpos;			//显示起点x坐标
	int32_t m_dis_ypos;			//显示起点y坐标
	uint32_t m_dis_width;		//显示宽度 
	uint32_t m_dis_height;		//显示高度 
	int32_t m_audio;			//是否带音频
}hi_mpp_vo_param_t;

#ifdef __cplusplus
extern "C"{
#endif

int32_t hi_mpp_vo_bind_graphic_layer(int32_t graphic_layer_id, int32_t vodev_id);
int32_t hi_mpp_vo_unbind_graphic_layer(int32_t graphic_layer_id, int32_t vodev_id);
int32_t hi_mpp_vo_start_dev(int32_t dev_id, hi_mpp_vo_param_t vo_param);
int32_t hi_mpp_vo_stop_dev(int32_t dev_id);

#ifdef __cplusplus
};
#endif

#endif