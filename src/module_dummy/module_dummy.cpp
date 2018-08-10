#include "../module_base.h"
#include "module_dummy.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _dummy_ctx_s{
	int32_t m_inited;
}dummy_ctx_t;

static dummy_ctx_t dummy_ctx = {0};
module_t *module_dummy = NULL;

static int32_t init()
{
	log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:into %s", __FUNCTION__, __LINE__, __FUNCTION__);
	if(1 == dummy_ctx.m_inited)
		return INTMODULE_DUMMY_ERR_INITED;

	return INTMODULE_DUMMY_OK;
}

static int32_t uninit()
{
	log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:into %s", __FUNCTION__, __LINE__, __FUNCTION__);
	if(0 == dummy_ctx.m_inited)
		return INTMODULE_DUMMY_ERR_SYS_NOTREADY;

	return INTMODULE_DUMMY_OK;
}

static int32_t process_command(struct module_pub_data *pmodule_pub_data)
{
	log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:into %s", __FUNCTION__, __LINE__, __FUNCTION__);
	return INTMODULE_DUMMY_OK;
}

static int32_t config_set(struct module_pub_data *pmodule_pub_data)
{
	log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:into %s", __FUNCTION__, __LINE__, __FUNCTION__);
	return INTMODULE_DUMMY_OK;
}

static int32_t config_get(struct module_pub_data *pmodule_pub_data, char *buf, int32_t buf_size)
{
	log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:into %s", __FUNCTION__, __LINE__, __FUNCTION__);
	return INTMODULE_DUMMY_OK;
}

static int32_t process_status(struct module_pub_data *pmodule_pub_data)
{
	log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:into %s", __FUNCTION__, __LINE__, __FUNCTION__);
	return INTMODULE_DUMMY_OK;
}

int32_t module_dummy_alloc()
{
	log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:into %s", __FUNCTION__, __LINE__, __FUNCTION__);
	module_dummy = (module_t *)calloc(1, sizeof(module_t));
	if (!module_dummy)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:malloc was failed", __FUNCTION__, __LINE__);
		return INTMODULE_DUMMY_FALSE;
	}
	module_dummy->m_name = "dummy";
	module_dummy->m_desc = "int mod dummy";
	module_dummy->init = init;
	module_dummy->uninit = uninit;
	module_dummy->process_command = process_command;
	module_dummy->process_status = process_status;
	module_dummy->config_set = config_set;
	module_dummy->config_get = config_get;
	return INTMODULE_DUMMY_OK;
}

int32_t module_dummy_free()
{
	log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:into %s", __FUNCTION__, __LINE__, __FUNCTION__);
	if (module_dummy)
	{
		free(module_dummy);
		module_dummy = NULL;
	}
	return INTMODULE_DUMMY_OK;
}