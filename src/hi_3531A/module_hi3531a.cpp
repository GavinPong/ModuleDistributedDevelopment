#include "../module_base.h"
#include "log.h"
#include "module_hi3531a.h"
#include "hi3531a_platform.h"
#include "hi_mpp_vo.h"
#include "hi_mpp_sys.h"
#include "hi_mpp_vi.h"
#include "hi_fb.h"
#include "hi_ui_manager.h"


typedef struct hi3531a_ctx_s{
	int32_t m_inited;
}hi3531a_ctx_t;


static hi3531a_ctx_t hi3531a_ctx = {0};
module_t *module_hi3531a = NULL;


static int32_t init()
{
	log_output(LOG_LEVEL_FILE_SCREEN,"%s->%d:into %s",__FUNCTION__, __LINE__, __FUNCTION__);

	int cycle = 0;
	int vodev_cnt = sizeof(hi_platform_param.m_mpp_vo_dev_params)/sizeof(hi_platform_param.m_mpp_vo_dev_params[0]);
	int32_t ret_value = INTMODULE_HISI_FALSE;
	char err_info[256] = "";

	hi3531a_platform_init();
	hi3531a_platform_load();
	hi_mpp_sys_init();
	for (cycle = 0;cycle < vodev_cnt;cycle++)
	{
		if(INTMODULE_HISI_OK != (ret_value = hi_mpp_vo_start_dev(hi_platform_param.m_mpp_vo_dev_params[cycle].m_devid, hi_platform_param.m_mpp_vo_dev_params[cycle])))
		{
			gavin_err_get_err_reason(ret_value, err_info, sizeof(err_info));
			log_output(LOG_LEVEL_FILE_SCREEN,"%s->%d:hi_mpp_vo_start_dev:%s",__FUNCTION__, __LINE__, err_info);
		}
	}
	hi_fb_init();
	hi_ui_manager_init();

	return INTMODULE_HISI_OK;
}

static int32_t uninit()
{
	log_output(LOG_LEVEL_FILE_SCREEN,"%s->%d:into %s",__FUNCTION__, __LINE__, __FUNCTION__);

	int cycle = 0;
	int vodev_cnt = sizeof(hi_platform_param.m_mpp_vo_dev_params)/sizeof(hi_platform_param.m_mpp_vo_dev_params[0]);
	int32_t ret_value = INTMODULE_HISI_FALSE;
	char err_info[256] = "";

	hi_ui_manager_uninit();
	for (cycle = 0;cycle < vodev_cnt;cycle++)
	{
		if(INTMODULE_HISI_OK != (ret_value = hi_mpp_vo_stop_dev(hi_platform_param.m_mpp_vo_dev_params[cycle].m_devid)))
		{
			gavin_err_get_err_reason(ret_value, err_info, sizeof(err_info));
			log_output(LOG_LEVEL_FILE_SCREEN,"%s->%d:hi_mpp_vo_stop_dev:%s",__FUNCTION__, __LINE__, err_info);
		}
	}
	hi_mpp_sys_uninit();
	hi3531a_platform_uninit();

	return INTMODULE_HISI_OK;
}

//供外部发命令给模块内部，或者使用模块内部某功能
static  int32_t process_command(struct module_pub_data *pmodule_pub_data)
{
	log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:into %s", __FUNCTION__, __LINE__, __FUNCTION__);
	return INTMODULE_HISI_OK;
}

//供外部发状态命令给模块内部，或者让模块将该状态通知到他的下级服务
static int32_t process_status(struct module_pub_data *pmodule_pub_data)
{
	log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:into %s", __FUNCTION__, __LINE__, __FUNCTION__);
	return INTMODULE_HISI_OK;
}

//设置模块配置参数
static int32_t config_set(struct module_pub_data *pmodule_pub_data)
{
	log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:into %s", __FUNCTION__, __LINE__, __FUNCTION__);
	return INTMODULE_HISI_OK;
}

//获取模块配置参数
static int32_t config_get(struct module_pub_data *pmodule_pub_data, char *buf, int32_t buf_size)
{
	log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:into %s", __FUNCTION__, __LINE__, __FUNCTION__);
	return INTMODULE_HISI_OK;
}

int32_t module_hi3531a_alloc()
{
	log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:into %s", __FUNCTION__, __LINE__, __FUNCTION__);
	if (module_hi3531a)
	{
		return INTMODULE_HISI_ERR_EXIST;
	}
	module_hi3531a = (module_t *)calloc(1, sizeof(module_t));
	if (!module_hi3531a)
	{
		return INTMODULE_HISI_ERR_NOT_NOMEM;
	}
	module_hi3531a->m_name = "hi3531a";
	module_hi3531a->m_desc = "int mod hi3531a";
	module_hi3531a->init = init;
	module_hi3531a->uninit = uninit;
	module_hi3531a->process_command = process_command;
	module_hi3531a->process_status = process_status;
	module_hi3531a->config_set = config_set;
	module_hi3531a->config_get = config_get;

	return INTMODULE_HISI_OK;
}

int32_t  module_hi3531a_free()
{
	log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:into %s", __FUNCTION__, __LINE__, __FUNCTION__);
	if (module_hi3531a)
	{
		free(module_hi3531a);
		module_hi3531a = NULL;
	}

	return INTMODULE_HISI_OK;
}

