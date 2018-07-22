#include "../module_base.h"
#include "log.h"
#include "module_rec_muxer.h"


typedef struct rec_muxer_ctx_s{
	int32_t m_inited;
}rec_muxer_ctx_s;


static rec_muxer_ctx_s rec_muxer_ctx = {0};
module_t *module_rec_muxer = NULL;


static int32_t init()
{
	LOG_PACKAGE_STR(init);
	return INTMODULE_REC_MUXER_OK;
}

static int32_t uninit()
{
	LOG_PACKAGE_STR(uninit);
	return INTMODULE_REC_MUXER_OK;
}

//供外部发命令给模块内部，或者使用模块内部某功能
static  int32_t process_command(struct module_pub_data *pmodule_pub_data)
{
	LOG_PACKAGE_STR(process_command);
	return INTMODULE_REC_MUXER_OK;
}

//供外部发状态命令给模块内部，或者让模块将该状态通知到他的下级服务
static int32_t process_status(struct module_pub_data *pmodule_pub_data)
{
	LOG_PACKAGE_STR(process_status);
	return INTMODULE_REC_MUXER_OK;
}

//设置模块配置参数
static int32_t config_set(struct module_pub_data *pmodule_pub_data)
{
	LOG_PACKAGE_STR(config_set);
	return INTMODULE_REC_MUXER_OK;
}

//获取模块配置参数
static int32_t config_get(struct module_pub_data *pmodule_pub_data, char *buf, int32_t buf_size)
{
	LOG_PACKAGE_STR(config_get);
	return INTMODULE_REC_MUXER_OK;
}

int32_t module_rec_muxer_alloc()
{
	LOG_PACKAGE_STR(module_rec_muxer_alloc);
	if (module_rec_muxer)
	{
		return INTMODULE_REC_MUXER_ERR_EXIST;
	}
	module_rec_muxer = (module_t *)calloc(1, sizeof(module_t));
	if (!module_rec_muxer)
	{
		return INTMODULE_REC_MUXER_ERR_NOT_NOMEM;
	}
	module_rec_muxer->m_name = "rec_muxer";
	module_rec_muxer->m_desc = "int mod rec muxer";
	module_rec_muxer->init = init;
	module_rec_muxer->uninit = uninit;
	module_rec_muxer->process_command = process_command;
	module_rec_muxer->process_status = process_status;
	module_rec_muxer->config_set = config_set;
	module_rec_muxer->config_get = config_get;

	return INTMODULE_REC_MUXER_OK;
}

int32_t  module_rec_muxer_free()
{
	LOG_PACKAGE_STR(module_rec_muxer_alloc);
	if (module_rec_muxer)
	{
		free(module_rec_muxer);
		module_rec_muxer = NULL;
	}

	return INTMODULE_REC_MUXER_OK;
}

