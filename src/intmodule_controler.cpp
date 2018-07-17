/*******************************
module_controler作用：
1、调用module_base的接口完成将所有模块填充到module_base模块表中；
2、读取配置表，根据配置表模块启动的参数，从module_base模块表中取出对应模块公共数据块地址存放到m_module_table_ptr中，供controler接口使用

*******************************/

#include "intmodule_external.h"	//必须放module_base.h前面否则可能编译不过
#include "module_base.h"
#include "intmodule_controler.h"
#include "filefunc.h"
#include "cJSON.h"
#include "global_def.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//功能模块启动项配置文件
#define  INTMODULE_JSON "/mnt/mtd/int_mod.json"

typedef struct module_ctrl_ctx_s{
	int32_t m_inited;						//是否已经初始化
	int32_t m_max_module_cnt;				//最大模块数
	module_t **m_module_arry;			//指向模块数组的指针
	struct list_head m_err_info_list_head;//错误信息链表头
}module_ctrl_ctx_t, *pmodule_ctrl_ctx_t;

static module_ctrl_ctx_t s_module_ctrl_ctx;

int32_t err_info_list_uninit(struct list_head *list_head);

int32_t err_info_list_init(struct list_head *list_head)
{
	if (!list_head)
	{
		return INTMODULE_CTR_ERR_NULL_PTR;
	}
	gavin_err_info_list_init(list_head);
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_INVALID_DEVID), INVALID_DEVID))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_INVALID_CHNID), INVALID_CHNID))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_ILLEGAL_PARAM), ILLEGAL_PARAM))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_EXIST), EXIST))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_UNEXIST), UNEXIST))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_NULL_PTR), NULL_PTR))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_NOT_CONFIG), NOT_CONFIG))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_NOT_SUPPORT), NOT_SUPPORT))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_NOT_PERM), NOT_PERM))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_NOT_NOMEM), NOT_NOMEM))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_NOT_NOBUF), NOT_NOBUF))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_BUF_EMPTY), BUF_EMPTY))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_BUF_FULL), BUF_FULLE))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_SYS_NOTREADY), SYS_NOTREADY))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_BADADDR), BADADDR))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_BUSY), BUSY))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_MODULE_ID), ERR_MODULE_ID))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_PARSE_JSON), ERR_PARSE_JSON))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_JSON_OBJ_EMPTY), JSON_OBJ_EMPTY))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_SET_EMPTY), SET_EMPTY))
		goto info_list_init_err;
	if(INTMODULE_CTR_OK != gavin_err_info_list_add_node(list_head, GAVIN_GET_ERR_ID_BY_ERR(INTMODULE_CTR_ERR_MATCH), MATCH))
		goto info_list_init_err;
	
	return INTMODULE_CTR_OK;

info_list_init_err:	
	err_info_list_uninit(list_head);
	return INTMODULE_CTR_ERR_NOT_NOMEM;
}

int32_t err_info_list_uninit(struct list_head *list_head)
{
	if (!list_head)
	{
		return INTMODULE_CTR_ERR_NULL_PTR;
	}
	gavin_err_info_list_uninit(list_head);
		
	return INTMODULE_CTR_OK;
}

int32_t err_info_list_find_err_info(struct list_head *list_head, int32_t err_id, char *out_buf, int32_t buf_size)
{
	if (!list_head || !out_buf || buf_size <=0)
	{
		return INTMODULE_CTR_ERR_NULL_PTR;
	}

	if(GAVIN_SUCCESS !=gavin_err_info_list_find_err_info(list_head, err_id, out_buf, buf_size))
		return INTMODULE_CTR_FALSE;
	
	return INTMODULE_CTR_OK;
}

int32_t get_err_info_callback(int32_t err_value, char *out_buf, int32_t buf_size)
{
	if (!out_buf || buf_size <= 0)
	{
		return INTMODULE_CTR_ERR_NULL_PTR;
	}
	
	int32_t errid = GAVIN_GET_ERR_ID_BY_ERR(err_value);
	if (errid > INT_MOD_CTR_ERR_MATCH)
	{
		strncpy(out_buf, "unknown err", buf_size);
		return INTMODULE_CTR_ERR_ILLEGAL_PARAM;
	}
	return err_info_list_find_err_info(&s_module_ctrl_ctx.m_err_info_list_head, errid, out_buf, buf_size);
}

static int32_t int_module_ctrl_module_match(int32_t module_id, const char *module_name)
{
	if (!s_module_ctrl_ctx.m_inited)
	{
		return INTMODULE_CTR_ERR_SYS_NOTREADY;
	}
	if (module_id >= s_module_ctrl_ctx.m_max_module_cnt)
	{
		return INTMODULE_CTR_ERR_MODULE_ID;
	}
	if (!s_module_ctrl_ctx.m_module_arry)
	{
		return INTMODULE_CTR_ERR_SET_EMPTY;
	}
	module_t *p_module = s_module_ctrl_ctx.m_module_arry[module_id];
	if (p_module && (!strcmp(p_module->m_name, module_name)))
	{
		return INTMODULE_CTR_OK;
	}
	return INTMODULE_CTR_ERR_MATCH;
}

static int32_t intmodule_ctrl_load_module(cJSON *in_json){
	if(!in_json)
		return INTMODULE_CTR_ERR_ILLEGAL_PARAM;
	cJSON *module_enable_arry_json, *sub_json, *module_json;
	int32_t arry_size = 0, i = 0;
	module_t *pmodule = NULL;

	module_enable_arry_json = cJSON_GetObjectItem(in_json, "module_enable");
	if (!module_enable_arry_json)
	{
		return INTMODULE_CTR_ERR_PARSE_JSON;
	}
	arry_size = cJSON_GetArraySize(module_enable_arry_json);
	if (!arry_size)
	{
		return INTMODULE_CTR_ERR_JSON_OBJ_EMPTY;
	}
	for (i = 0;i < arry_size;i++)
	{
		sub_json = cJSON_GetArrayItem(module_enable_arry_json, i);
		if (!sub_json)
		{
			continue;
		}
		module_json = cJSON_GetObjectItem(sub_json, "enable");
		if (1 == module_json->valueint)
		{
			module_json = cJSON_GetObjectItem(sub_json, "name");			
			module_json && module_base_find_module_by_name(&pmodule, module_json->valuestring);
			if (pmodule)
			{
				pmodule->init();
				printf("%s->%d:%s module load success\n", __FILE__, __LINE__, module_json->valuestring);
				s_module_ctrl_ctx.m_module_arry[pmodule->m_module_id] = pmodule;
			}
			else
			{
				if (module_json)
				{
					printf("%s->%d:%s module load failed\n", __FILE__, __LINE__, module_json->valuestring);
				}	
			}
		}
		
	}
	
	
	return INTMODULE_CTR_OK;
}

int32_t intmodule_ctrl_init_ctx(){
	memset(&s_module_ctrl_ctx, 0, sizeof(s_module_ctrl_ctx));
	s_module_ctrl_ctx.m_inited = 1;
	s_module_ctrl_ctx.m_max_module_cnt = 0;
	s_module_ctrl_ctx.m_module_arry = NULL;
	module_base_manager_ctx_init();
	return INTMODULE_CTR_OK;
}

int32_t intmodule_ctrl_uninit_ctx(){
	module_base_manager_ctx_uninit();
	s_module_ctrl_ctx.m_inited = 0;

	return INTMODULE_CTR_OK;
}

int32_t intmodule_ctrl_startup(){
	cJSON *root_json;
	gavin_err_register_output_func(GAVIN_MODE_ID_INT_MOD_CTR, "intmodule_ctr", get_err_info_callback);
	intmodule_ctrl_init_ctx();
	//申请存储所有模块公共数据块地址的地址表
	if ((s_module_ctrl_ctx.m_max_module_cnt = module_base_register_all_module()) <= 0)
	{
		printf("%s-%d:intmodule_ctrl_startup was failed because:register_all_module was failed\n", __FILE__, __LINE__);
		intmodule_ctrl_uninit_ctx();
		return INTMODULE_CTR_FALSE;
	}
	s_module_ctrl_ctx.m_module_arry = (module_t **)calloc(s_module_ctrl_ctx.m_max_module_cnt, sizeof(module_t *));
	if (!s_module_ctrl_ctx.m_module_arry)
	{
		intmodule_ctrl_shutdown();
		return INTMODULE_CTR_ERR_NOT_NOMEM;
	}
	
	if(FILE_FUNC_OK != FILE_FUNC_Get_Json_Form_File(INTMODULE_JSON, &root_json))
	{
		intmodule_ctrl_shutdown();
		return INTMODULE_CTR_ERR_PARSE_JSON;
	}
	intmodule_ctrl_load_module(root_json);

	return INTMODULE_CTR_OK;
}

int intmodule_ctrl_shutdown(){
	int32_t i = 0;

	for (i = 0;i < s_module_ctrl_ctx.m_max_module_cnt;i++)
	{
		if (s_module_ctrl_ctx.m_module_arry[i])
		{
			s_module_ctrl_ctx.m_module_arry[i]->uninit();
		}	
	}
	module_base_unregister_all_module();
	intmodule_ctrl_uninit_ctx();
	return INTMODULE_CTR_OK;
}

int32_t intmodule_ctrl_process_cmd(module_pub_data_t *module_pub_data){
	if (!module_pub_data)
	{
		return INTMODULE_CTR_ERR_NULL_PTR;
	}
	
	int32_t ret_value = INTMODULE_CTR_OK;
	int32_t module_id = module_pub_data->m_module_id;
	char name[32] = "";

	strncpy(name, module_pub_data->m_name, sizeof(name));
	if (INTMODULE_CTR_OK != (ret_value = int_module_ctrl_module_match(module_id, name)))
	{
		return ret_value;
	}
	module_t *p_module = s_module_ctrl_ctx.m_module_arry[module_id];
	p_module->process_command(module_pub_data);
	return INTMODULE_CTR_OK;
}

int32_t intmodule_ctrl_get_config(module_pub_data_t *module_pub_data, char *buf, uint32_t buf_size){
	if (!module_pub_data || !buf || buf_size <= 0)
	{
		return INTMODULE_CTR_ERR_NULL_PTR;
	}
	int32_t ret_value = INTMODULE_CTR_OK;
	int32_t module_id = module_pub_data->m_module_id;
	char name[32] = "";

	strncpy(name, module_pub_data->m_name, sizeof(name));
	if (INTMODULE_CTR_OK != (ret_value = int_module_ctrl_module_match(module_id, name)))
	{
		return ret_value;
	}
	module_t *p_module = s_module_ctrl_ctx.m_module_arry[module_id];
	p_module->config_get(module_pub_data, buf, buf_size);
	return INTMODULE_CTR_OK;
}

int32_t intmodule_ctrl_set_config(module_pub_data_t *module_pub_data){
	if (!module_pub_data)
	{
		return INTMODULE_CTR_ERR_NULL_PTR;
	}
	int32_t ret_value = INTMODULE_CTR_OK;
	int32_t module_id = module_pub_data->m_module_id;
	char name[32] = "";

	strncpy(name, module_pub_data->m_name, sizeof(name));
	if (INTMODULE_CTR_OK != (ret_value = int_module_ctrl_module_match(module_id, name)))
	{
		return ret_value;
	}
	module_t *p_module = s_module_ctrl_ctx.m_module_arry[module_id];
	p_module->config_set(module_pub_data);
	return INTMODULE_CTR_OK;
}

int32_t intmodule_ctrl_register_callback(int32_t (*callback)(module_pub_data_t *module_pub_data)){
	if (!callback)
	{
		return INTMODULE_CTR_ERR_NULL_PTR;
	}
	
	g_module_base_callback = callback;
	return INTMODULE_CTR_OK;
}