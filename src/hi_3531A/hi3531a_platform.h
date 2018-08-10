/**************************
此文件中全部存放31a平台固化的，用户无法修改的参数
**************************/
#ifndef __HI3531a_PLATFORM_H__
#define __HI3531a_PLATFORM_H__

#include "cross_platform.h"
#include "hi_mpp_vo.h"
#include "hi_ui_manager.h"

#define HI_3531A_DHD0 0//设备，即高清显示设备0。
#define HI_3531A_DHD1 1//设备，即高清显示设备1。
#define HI_3531A_DSD0 2//设备，即标清显示设备0。
#define HI_3531A_VO_VIRT_DEV_0 	3//设备，即虚拟设备0。
#define HI_3531A_VO_VIRT_DEV_1 	4//设备，即虚拟设备1。
#define HI_3531A_VO_VIRT_DEV_2 	5//设备，即虚拟设备2。
#define HI_3531A_VO_VIRT_DEV_3 	6//设备，即虚拟设备3。
#define HI_3531A_VO_CAS_DEV_1	7//即级联设备0。
#define HI_3531A_VO_CAS_DEV_2	8//即级联设备1。

typedef struct _hi_platform_param_s{
	uint8_t m_u8inited;			//是否初始化
	uint8_t m_u8vb_16m_cnt;		//4K画面-16M缓存块的个数
	uint8_t m_u8vb_4m_cnt;		//1080p画面-4M缓存块的个数
	uint8_t m_u8vb_1m_cnt;		//小码流p画面-1M缓存块的个数
	char m_strpixel_format[32];	//像素格式
	hi_mpp_vo_param_t m_mpp_vo_dev_params[3];
	hi_ui_params_t m_ui_params[3];
}hi_platform_param_t;

#ifdef __cplusplus
extern "C"{
#endif
//流程:代码初始化-->从文件中加载参数，成功加载了的参数直接覆盖掉代码初始化的参数-->反初始化（一般用不着）
//代码直接初始化（指定）平台参数的接口
int32_t hi3531a_platform_init();
//代码反初始化（指定）平台参数的接口
int32_t hi3531a_platform_uninit();
//从配置文件中加载平台参数的接口
int32_t hi3531a_platform_load();

#ifdef __cplusplus
};
#endif

extern hi_platform_param_t hi_platform_param;

#endif