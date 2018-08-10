#ifndef __HI_FB_H__
#define __HI_FB_H__

#include "cross_platform.h"

typedef struct _hi_fb_alpha_params_s{
	uint8_t	m_u8alpha_enable;		//ʹ��alpha
	uint8_t m_u8alpha_chn_enable;	//ʹ��ͨ��alpha
	uint8_t m_u32alpha_chn_value;	//ͨ��alphaֵ
	uint8_t m_u32alpha_value;		//alphaֵ
}hi_fb_alpha_params_t;

typedef struct _hi_fb_colorkey_param_s{
	uint8_t m_u8enable;
	uint32_t m_u8value;
}hi_fb_colorkey_param_t;

typedef struct _fb_params_s{
	char	m_s8name[16];			//�豸��		
	uint8_t m_u8enable;				//�Ƿ�ʹ��
	uint8_t	m_u8colorkey_enable;	//ʹ��colorkey
	uint8_t m_u8bpp;				//���ص��ֽ���bits per pixel
	uint32_t m_u32colorkey_value;	//colorkeyֵ
	hi_fb_alpha_params_t m_alpha_param;//alpha����
	int32_t m_s32xpos;			//x��ʼ����
	int32_t m_s32ypos;			//y��ʼ����
	uint32_t m_u32width;			//�豸�ֱ��ʿ�			
	uint32_t m_u32height;			//�豸�ֱ��ʸ�
	uint32_t m_u32virtual_width;	//�Դ�ֱ��ʿ�
	uint32_t m_u32virtual_height;	//�Դ�ֱ��ʿ�
	uint32_t m_u32_stride;			//��Ļ���
	int32_t m_s32xoffset;			//�Դ���ʾ�ĺ��������
	int32_t m_s32yoffset;			//�Դ���ʾ�����������
	int32_t m_s32fd;				//fb�豸���
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
	int32_t m_s32xpoint;		//��ʾ��ʼλ����λͼ��x����
	int32_t m_s32ypoint;		//��ʾ��ʼλ����λͼ��y����
	uint32_t m_u32operate_width;//λͼ��������Ŀ�
	uint32_t m_u32operate_height;//λͼ��������ĸ�
	uint32_t m_u32width;		//����λͼ���ܴ����ڴ���
	uint32_t m_u32height;		//����λͼ�߲��ܴ����ڴ���
	uint32_t m_u32phy_addr;		//�ڴ�������ַ
	char *m_vir_addr;			//�ڴ�������ַ
	uint8_t m_enable_alpha;		//alphaʹ��
	uint8_t m_alpha_value;		//alphaֵ
	hi_fb_color_fmt_e m_color_fmt;//���ɫ��ʽ
	uint32_t m_stride;			//λͼ���
}bitmap_display_params_t;

typedef struct _hi_fb_screen_info_s{
	uint32_t m_u32stride;			//���
	uint32_t m_u32vir_width;		//�Դ��
	uint32_t m_u32vir_height;		//�Դ��
	uint32_t m_u32width;			//�豸�ֱ��ʿ�
	uint32_t m_u32height;			//�豸�ֱ��ʸ�
	int32_t m_s32xpoint;			//������ʾλ��x����
	int32_t m_s32ypoint;			//������ʾλ��y����
}hi_fb_screen_info_t;

typedef void * hi_fb_handle_t;

#ifdef __cplusplus
extern "C"{
#endif

//��ʼ��fb
int32_t  hi_fb_init();
//����ʼ��fb
int32_t  hi_fb_uninit();
//��fb�豸
int32_t  hi_fb_open(hi_fb_handle_t *hi_fb_handle, fb_params_t fb_params);
//�ر�fb�豸
int32_t  hi_fb_close(hi_fb_handle_t hi_fb_handle);
//��ʾͼ��
int32_t  hi_fb_show(hi_fb_handle_t hi_fb_handle);
//����ͼ��
int32_t  hi_fb_hide(hi_fb_handle_t hi_fb_handle);
//����
int32_t  hi_fb_clear_screen(hi_fb_handle_t hi_fb_handle);
//��ȡcolorkeyֵ
int32_t	 hi_fb_get_colorkey_value(hi_fb_handle_t hi_fb_handle, hi_fb_colorkey_param_t *colorkey_param);
//����colorkeyֵ
int32_t	 hi_fb_set_colorkey_value(hi_fb_handle_t hi_fb_handle, hi_fb_colorkey_param_t colorkey_param);
//��ȡalphaֵ
int32_t	 hi_fb_get_alpha_value(hi_fb_handle_t hi_fb_handle, hi_fb_alpha_params_t *alpha_params);
//����alphaֵ
int32_t	 hi_fb_set_alpha_value(hi_fb_handle_t hi_fb_handle, hi_fb_alpha_params_t alpha_params);
//��ȡfb�豸��ʾ����ʼλ��
int32_t  hi_fb_get_origin_position(hi_fb_handle_t hi_fb_handle, int32_t *x, int32_t *y);
//����fb�豸��ʾ����ʼλ��
int32_t  hi_fb_set_origin_position(hi_fb_handle_t hi_fb_handle, int32_t x, int32_t y);
//��ʾλͼ
int32_t  hi_fb_display_bitmap(hi_fb_handle_t hi_fb_handle, bitmap_display_params_t src_bitmap_dis_params, bitmap_display_params_t dst_bitmap_dis_params);
//��ȡFB��ID��
int32_t  hi_fb_query_graphic_layer_id_by_name(char *dev_name, int32_t *graphic_layer_id);
//��ȡ��Ļ��Ϣ
int32_t hi_fb_get_screen_info(hi_fb_handle_t hi_fb_handle, hi_fb_screen_info_t *hi_fb_screen_info);
//������Ļ��Ϣ����ʱ��Ч��
int32_t hi_fb_set_screen_info(hi_fb_handle_t hi_fb_handle, hi_fb_screen_info_t hi_fb_screen_info);


#ifdef __cplusplus
};
#endif

#endif