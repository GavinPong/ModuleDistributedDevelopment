#include "../module_base.h"
#include "module_dummy.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _dummy_ctx_s{
	int m_inited;
}dummy_ctx_t;

static dummy_ctx_t dummy_ctx = {0};
module_t *module_dummy = NULL;

static int init()
{
	if(1 == dummy_ctx.m_inited)
		return INTMODULE_DUMMY_ERR_INITED;

	LOG_PACKAGE_STR(init);
	return INTMODULE_DUMMY_OK;
}

static int uninit()
{
	if(0 == dummy_ctx.m_inited)
		return INTMODULE_DUMMY_ERR_SYS_NOTREADY;

	LOG_PACKAGE_STR(uninit);
	return INTMODULE_DUMMY_OK;
}

static int process_command(struct module_pub_data *pmodule_pub_data)
{
	LOG_PACKAGE_STR(process_command);
	return INTMODULE_DUMMY_OK;
}

static int config_set(struct module_pub_data *pmodule_pub_data)
{
	LOG_PACKAGE_STR(config_set);
	return INTMODULE_DUMMY_OK;
}

static int config_get(struct module_pub_data *pmodule_pub_data, char *buf, int buf_size)
{
	LOG_PACKAGE_STR(config_get);
	return INTMODULE_DUMMY_OK;
}

static int process_status(struct module_pub_data *pmodule_pub_data)
{
	LOG_PACKAGE_STR(process_status);
	return INTMODULE_DUMMY_OK;
}

int module_dummy_alloc()
{
	LOG_PACKAGE_STR(module_dummy_alloc);
	module_dummy = (module_t *)calloc(1, sizeof(module_t));
	if (!module_dummy)
	{
		LOG_PACKAGE_STR(malloc module_dummy structor was failed);
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

int module_dummy_free()
{
	LOG_PACKAGE_STR(module_dummy_free);
	if (module_dummy)
	{
		free(module_dummy);
		module_dummy = NULL;
	}
	return INTMODULE_DUMMY_OK;
}