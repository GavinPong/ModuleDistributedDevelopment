/**************************
���ļ���ȫ�����31aƽ̨�̻��ģ��û��޷��޸ĵĲ���
**************************/
#ifndef __HI3531a_PLATFORM_H__
#define __HI3531a_PLATFORM_H__

#include "cross_platform.h"
#include "hi_mpp_vo.h"
#include "hi_ui_manager.h"

#define HI_3531A_DHD0 0//�豸����������ʾ�豸0��
#define HI_3531A_DHD1 1//�豸����������ʾ�豸1��
#define HI_3531A_DSD0 2//�豸����������ʾ�豸0��
#define HI_3531A_VO_VIRT_DEV_0 	3//�豸���������豸0��
#define HI_3531A_VO_VIRT_DEV_1 	4//�豸���������豸1��
#define HI_3531A_VO_VIRT_DEV_2 	5//�豸���������豸2��
#define HI_3531A_VO_VIRT_DEV_3 	6//�豸���������豸3��
#define HI_3531A_VO_CAS_DEV_1	7//�������豸0��
#define HI_3531A_VO_CAS_DEV_2	8//�������豸1��

typedef struct _hi_platform_param_s{
	uint8_t m_u8inited;			//�Ƿ��ʼ��
	uint8_t m_u8vb_16m_cnt;		//4K����-16M�����ĸ���
	uint8_t m_u8vb_4m_cnt;		//1080p����-4M�����ĸ���
	uint8_t m_u8vb_1m_cnt;		//С����p����-1M�����ĸ���
	char m_strpixel_format[32];	//���ظ�ʽ
	hi_mpp_vo_param_t m_mpp_vo_dev_params[3];
	hi_ui_params_t m_ui_params[3];
}hi_platform_param_t;

#ifdef __cplusplus
extern "C"{
#endif
//����:�����ʼ��-->���ļ��м��ز������ɹ������˵Ĳ���ֱ�Ӹ��ǵ������ʼ���Ĳ���-->����ʼ����һ���ò��ţ�
//����ֱ�ӳ�ʼ����ָ����ƽ̨�����Ľӿ�
int32_t hi3531a_platform_init();
//���뷴��ʼ����ָ����ƽ̨�����Ľӿ�
int32_t hi3531a_platform_uninit();
//�������ļ��м���ƽ̨�����Ľӿ�
int32_t hi3531a_platform_load();

#ifdef __cplusplus
};
#endif

extern hi_platform_param_t hi_platform_param;

#endif