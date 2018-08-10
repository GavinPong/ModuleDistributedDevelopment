#ifndef __HI_FB_H__
#define __HI_FB_H__

#include "cross_platform.h"

typedef struct _hi_fb_alpha_params_s{
	uint8_t	m_u8alpha_enable;		//使能alpha
	uint8_t m_u8alpha_chn_enable;	//使能通道alpha
	uint8_t m_u32alpha_chn_value;	//通道alpha值
	uint8_t m_u32alpha_value;		//alpha值
}hi_fb_alpha_params_t;

typedef struct _hi_fb_colorkey_param_s{
	uint8_t m_u8enable;
	uint32_t m_u8value;
}hi_fb_colorkey_param_t;

typedef struct _fb_params_s{
	char	m_s8name[16];			//设备名		
	uint8_t m_u8enable;				//是否使能
	uint8_t	m_u8colorkey_enable;	//使能colorkey
	uint8_t m_u8bpp;				//像素点字节数bits per pixel
	uint32_t m_u32colorkey_value;	//colorkey值
	hi_fb_alpha_params_t m_alpha_param;//alpha参数
	int32_t m_s32xpos;			//x起始坐标
	int32_t m_s32ypos;			//y起始坐标
	uint32_t m_u32width;			//设备分辨率宽			
	uint32_t m_u32height;			//设备分辨率高
	uint32_t m_u32virtual_width;	//显存分辨率宽
	uint32_t m_u32virtual_height;	//显存分辨率宽
	uint32_t m_u32_stride;			//屏幕跨度
	int32_t m_s32xoffset;			//显存显示的横坐标起点
	int32_t m_s32yoffset;			//显存显示的纵坐标起点
	int32_t m_s32fd;				//fb设备句柄
}fb_params_t;

typedef enum _hi_fb_color_fmt_e{
	HIFB_COLOR_FMT_RGB444 = 0,          /**< RGB444 format */
	HIFB_COLOR_FMT_BGR444,              /**< BGR444 format */    
	HIFB_COLOR_FMT_RGB555,              /**< RGB555 format */
	HIFB_COLOR_FMT_BGR555,              /**< BGR555 format */
	HIFB_COLOR_FMT_RGB565,              /**< RGB565 format */
	HIFB_COLOR_FMT_BGR565,              /**< BGR565 format */
	HIFB_COLOR_FMT_RGB888,              /**< RGB888 format */
	HIFB_COLOR_FMT_BGR888,              /**< BGR888 format */
	HIFB_COLOR_FMT_ARGB4444,            /**< ARGB4444 format */
	HIFB_COLOR_FMT_ABGR4444,            /**< ABGR4444 format */
	HIFB_COLOR_FMT_RGBA4444,            /**< RGBA4444 format */
	HIFB_COLOR_FMT_BGRA4444,            /**< BGRA4444 format */
	HIFB_COLOR_FMT_ARGB1555,            /**< ARGB1555 format */
	HIFB_COLOR_FMT_ABGR1555,            /**< ABGR1555 format */
	HIFB_COLOR_FMT_RGBA1555,            /**< RGBA1555 format */
	HIFB_COLOR_FMT_BGRA1555,            /**< BGRA1555 format */
	HIFB_COLOR_FMT_ARGB8565,            /**< ARGB8565 format */
	HIFB_COLOR_FMT_ABGR8565,            /**< ABGR8565 format */
	HIFB_COLOR_FMT_RGBA8565,            /**< RGBA8565 format */
	HIFB_COLOR_FMT_BGRA8565,            /**< BGRA8565 format */
	HIFB_COLOR_FMT_ARGB8888,            /**< ARGB8888 format */
	HIFB_COLOR_FMT_ABGR8888,            /**< ABGR8888 format */
	HIFB_COLOR_FMT_RGBA8888,            /**< RGBA8888 format */
	HIFB_COLOR_FMT_BGRA8888,            /**< BGRA8888 format */
	HIFB_COLOR_FMT_RABG8888,            /**<RABG8888 format*/
	HIFB_COLOR_FMT_CLUT1,               /**CLUT1 */
	HIFB_COLOR_FMT_CLUT2,               /**CLUT2 */
	HIFB_COLOR_FMT_CLUT4,               /**CLUT4 */
	HIFB_COLOR_FMT_CLUT8,               /**CLUT8 */
	HIFB_COLOR_FMT_ACLUT44,             /**CLUT44 */
	HIFB_COLOR_FMT_ACLUT88,             /**CLUT88 */
	HIFB_COLOR_FMT_A1,                  /**<alpha format??1bit */
	HIFB_COLOR_FMT_A8,                  /**<alpha format??8bit */
	HIFB_COLOR_FMT_YCbCr888,            /**<YUV packet format??no alpha*/
	HIFB_COLOR_FMT_AYCbCr8888,          /**<YUV packet format??with alpha*/
	HIFB_COLOR_FMT_YCbCr422,            /**<YUV packet422 format */
	HIFB_COLOR_FMT_byte,                /**<byte*/
	HIFB_COLOR_FMT_halfword,            /**<halfword*/
	HIFB_COLOR_FMT_JPG_YCbCr400MBP,     /**<Semi-planar YUV400 format in the JPEG encoding format */
	HIFB_COLOR_FMT_JPG_YCbCr422MBHP,    /**<Semi-planar YUV422 format (half of the horizontal sampling)*/
	HIFB_COLOR_FMT_JPG_YCbCr422MBVP,    /**<Semi-planar YUV422 format (half of the vertical sampling) */
	HIFB_COLOR_FMT_MP1_YCbCr420MBP,     /**<Semi-planar YUV420 format */
	HIFB_COLOR_FMT_MP2_YCbCr420MBP,     /**<Semi-planar YUV420 format */
	HIFB_COLOR_FMT_MP2_YCbCr420MBI,     /**<Semi-planar YUV400 format */
	HIFB_COLOR_FMT_JPG_YCbCr420MBP,     /**<Semi-planar YUV400 format in the JPEG encoding format */
	HIFB_COLOR_FMT_JPG_YCbCr444MBP,     /**<Semi-planar YUV444 format */
	HIFB_COLOR_FMT_BUTT   
}hi_fb_color_fmt_e;

typedef struct _bitmap_display_params_s{
	int32_t m_s32xpoint;		//显示起始位置在位图中x坐标
	int32_t m_s32ypoint;		//显示起始位置在位图中y坐标
	uint32_t m_u32operate_width;//位图操作区域的宽
	uint32_t m_u32operate_height;//位图操作区域的高
	uint32_t m_u32width;		//整个位图宽不能大于内存块宽
	uint32_t m_u32height;		//整个位图高不能大于内存块高
	uint32_t m_u32phy_addr;		//内存块物理地址
	char *m_vir_addr;			//内存块虚拟地址
	uint8_t m_enable_alpha;		//alpha使能
	uint8_t m_alpha_value;		//alpha值
	hi_fb_color_fmt_e m_color_fmt;//填充色格式
	uint32_t m_stride;			//位图跨度
}bitmap_display_params_t;

typedef struct _hi_fb_screen_info_s{
	uint32_t m_u32stride;			//跨度
	uint32_t m_u32vir_width;		//显存宽
	uint32_t m_u32vir_height;		//显存高
	uint32_t m_u32width;			//设备分辨率宽
	uint32_t m_u32height;			//设备分辨率高
	int32_t m_s32xpoint;			//画面显示位置x坐标
	int32_t m_s32ypoint;			//画面显示位置y坐标
}hi_fb_screen_info_t;

typedef void * hi_fb_handle_t;

#ifdef __cplusplus
extern "C"{
#endif

//初始化fb
int32_t  hi_fb_init();
//反初始化fb
int32_t  hi_fb_uninit();
//打开fb设备
int32_t  hi_fb_open(hi_fb_handle_t *hi_fb_handle, fb_params_t fb_params);
//关闭fb设备
int32_t  hi_fb_close(hi_fb_handle_t hi_fb_handle);
//显示图层
int32_t  hi_fb_show(hi_fb_handle_t hi_fb_handle);
//隐藏图层
int32_t  hi_fb_hide(hi_fb_handle_t hi_fb_handle);
//清屏
int32_t  hi_fb_clear_screen(hi_fb_handle_t hi_fb_handle);
//获取colorkey值
int32_t	 hi_fb_get_colorkey_value(hi_fb_handle_t hi_fb_handle, hi_fb_colorkey_param_t *colorkey_param);
//设置colorkey值
int32_t	 hi_fb_set_colorkey_value(hi_fb_handle_t hi_fb_handle, hi_fb_colorkey_param_t colorkey_param);
//获取alpha值
int32_t	 hi_fb_get_alpha_value(hi_fb_handle_t hi_fb_handle, hi_fb_alpha_params_t *alpha_params);
//设置alpha值
int32_t	 hi_fb_set_alpha_value(hi_fb_handle_t hi_fb_handle, hi_fb_alpha_params_t alpha_params);
//获取fb设备显示的起始位置
int32_t  hi_fb_get_origin_position(hi_fb_handle_t hi_fb_handle, int32_t *x, int32_t *y);
//设置fb设备显示的起始位置
int32_t  hi_fb_set_origin_position(hi_fb_handle_t hi_fb_handle, int32_t x, int32_t y);
//显示位图
int32_t  hi_fb_display_bitmap(hi_fb_handle_t hi_fb_handle, bitmap_display_params_t src_bitmap_dis_params, bitmap_display_params_t dst_bitmap_dis_params);
//获取FB的ID号
int32_t  hi_fb_query_graphic_layer_id_by_name(char *dev_name, int32_t *graphic_layer_id);
//获取屏幕信息
int32_t hi_fb_get_screen_info(hi_fb_handle_t hi_fb_handle, hi_fb_screen_info_t *hi_fb_screen_info);
//设置屏幕信息（暂时无效）
int32_t hi_fb_set_screen_info(hi_fb_handle_t hi_fb_handle, hi_fb_screen_info_t hi_fb_screen_info);


#ifdef __cplusplus
};
#endif

#endif