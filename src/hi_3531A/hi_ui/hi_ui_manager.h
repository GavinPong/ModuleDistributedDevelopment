#ifndef __HI_UI_MANAGER_H__
#define __HI_UI_MANAGER_H__

typedef struct _hi_ui_params_s{
	uint8_t m_enable;				//ʹ��ui
	uint8_t m_has_mouse;			//�Ƿ�֧�����
	int32_t m_vo_dev_id;			//vo�豸id
	char m_fb_name[16];				//framebuffer������fb0��fb1
	char m_ui_name[32];				//ui����
}hi_ui_params_t;

#ifdef __cplusplus
extern "C"{
#endif

int32_t hi_ui_manager_init();
int32_t hi_ui_manager_uninit();

#ifdef __cplusplus
};
#endif

#endif