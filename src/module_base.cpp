/*********************
module_base 作用：
1、提供接口将各个模块填充到模块表中；
2、提供接口让controler通过模块ID获取模块表中模块公共数据块，供外部调用对应模块的功能接口
*********************/

#include "module_base.h"
#include "cJSON.h"
#include <stdio.h>


//module管理字段
typedef struct _module_magager_ctx{
	int m_inited;
	struct list_head m_module_list_head;
	cJSON *m_root_module_table_json;//指向module table对应的json数据
	int m_module_cnt;//表中模块数，但不代表被注册进来的模块数，有的可能在表中，但是没有被注册进来
}module_magager_ctx_t;

static module_magager_ctx_t s_module_magager_ctx_t;
module_base_callback_t g_module_base_callback = NULL;//模块内部调用上层接口的入口

//每注册一个模块必须在表中填充模块名对应的id，每个模块的id必须唯一，参考dummy
static char module_table[] = {
	"{\"module_table\":"
	"["
		"{\"dummy\":0},"
		"{\"rec_muxer\":1}"
	"]}"
};

static int module_in_module_table(const char *module_name){
	if (!s_module_magager_ctx_t.m_root_module_table_json)
	{
		return MODULE_FAILURE;
	}	
	if (!module_name)
	{
		return MODULE_ERR_INVALIDPARAM;
	}
	cJSON *arry_json, *sub_json, *module_json;
	int table_size = 0, i = 0;
	int find_ok = 0;
	int module_id = -1;

	arry_json = cJSON_GetObjectItem(s_module_magager_ctx_t.m_root_module_table_json, "module_table");
	if (!arry_json)
	{
		return MODULE_FAILURE;
	}
	table_size = cJSON_GetArraySize(arry_json);
	if (!table_size)
	{
		return MODULE_FAILURE;
	}
	for (i = 0;i < table_size;i++)
	{
		sub_json = cJSON_GetArrayItem(arry_json, i);
		if (sub_json)
		{
			module_json = cJSON_GetObjectItem(sub_json, module_name);
			if (module_json)
			{
				find_ok = 1;
				module_id = module_json->valueint;
				break;
			}
		}
	}
	if (!find_ok)
	{
		return MODULE_FAILURE;
	}
	return module_id;
}

static int register_module(module_t *pmodule, int module_id){
	if (!pmodule)
	{
		return MODULE_ERR_INVALIDPARAM;
	}
	pmodule->m_module_id = module_id;
	list_add(&pmodule->m_list, &s_module_magager_ctx_t.m_module_list_head);

	return MODULE_OK;
}

static int unregister_module(module_t *pmodule){
	if (!pmodule)
	{
		return MODULE_ERR_INVALIDPARAM;
	}
	list_del(&pmodule->m_list);

	return MODULE_OK;
}

//每个函数必须定义int module_name_module_all() 和 int module_name_module_free()接口申请和释放模块内部管理字段
#define DECLARE_MODULE_ALLOC_FUNCTION(module_name) int32_t module_##module_name##_alloc()
#define DECLARE_MODULE_FREE_FUNCTION(module_name) int32_t module_##module_name##_free()
#define MODULE_NAME_TO_STR(module_name) #module_name 
#define MODULE_CHECK(module_name) module_in_module_table(#module_name)

#define REGISTER_MODULE(module_name) {\
	DECLARE_MODULE_ALLOC_FUNCTION(module_name);\
	extern module_t *module_##module_name;\
	int32_t module_id = MODULE_FALSE;\
	module_id = MODULE_CHECK(module_name);\
	if (module_id < 0)\
	{\
		printf("%s->%d:%s does not register in the registry", __FILE__, __LINE__, MODULE_NAME_TO_STR(module_name));\
		return MODULE_FAILURE;\
	}\
	module_##module_name##_alloc();\
	register_module(module_##module_name, module_id);\
}

#define UNREGISTER_MODULE(module_name) {\
	DECLARE_MODULE_FREE_FUNCTION(module_name);\
	extern module_t *module_##module_name;\
	int32_t module_id = MODULE_FALSE;\
	module_id = MODULE_CHECK(module_name);\
	if (module_id < 0)\
	{\
		printf("%s->%d:%s does not register in the registry", __FILE__, __LINE__, MODULE_NAME_TO_STR(module_name));\
		return ;\
	}\
	unregister_module(module_##module_name);\
	module_##module_name##_free();\
}

int module_base_manager_ctx_init(){
	s_module_magager_ctx_t.m_inited = 1;
	s_module_magager_ctx_t.m_module_cnt = 0;
	s_module_magager_ctx_t.m_root_module_table_json = NULL;
	INIT_LIST_HEAD(&s_module_magager_ctx_t.m_module_list_head);
	return MODULE_OK;
}

int module_base_manager_ctx_uninit(){
	s_module_magager_ctx_t.m_inited = 0;
	s_module_magager_ctx_t.m_module_cnt = 0;
	s_module_magager_ctx_t.m_root_module_table_json = NULL;

	return MODULE_OK;
}

//每新增一个module,则需在此函数内注册对应模块
int32_t module_base_register_all_module(){
	s_module_magager_ctx_t.m_root_module_table_json = cJSON_Parse(module_table);
	if (!s_module_magager_ctx_t.m_root_module_table_json)
	{
		printf("%s->%d:register_all_module failed because parse module table was failed.....\n", __FILE__, __LINE__);
		return MODULE_FAILURE;
	}
	/*****start 所有模块注册******/
	REGISTER_MODULE(dummy);	//注册样例模块
	REGISTER_MODULE(rec_muxer);	//注册样例模块
	/*****end 所有模块注册******/
	s_module_magager_ctx_t.m_module_cnt = cJSON_GetObjectItem(s_module_magager_ctx_t.m_root_module_table_json, "module_table")?cJSON_GetArraySize(cJSON_GetObjectItem(s_module_magager_ctx_t.m_root_module_table_json, "module_table")):0;
	cJSON_Delete(s_module_magager_ctx_t.m_root_module_table_json);
	s_module_magager_ctx_t.m_root_module_table_json = NULL;

	return s_module_magager_ctx_t.m_module_cnt;
}

	//每新增一个module,则需在此函数内注册对应模块
void module_base_unregister_all_module(){
	s_module_magager_ctx_t.m_root_module_table_json = cJSON_Parse(module_table);
	if (!s_module_magager_ctx_t.m_root_module_table_json)
	{
		printf("%s->%d:register_all_module failed because parse module table was failed.....\n", __FILE__, __LINE__);
		return ;
	}
	/*****start 所有模块反注册******/
	UNREGISTER_MODULE(dummy);	//注册样例模块
	/*****end 所有模块反注册******/
	cJSON_Delete(s_module_magager_ctx_t.m_root_module_table_json);
	s_module_magager_ctx_t.m_root_module_table_json = NULL;
}

int32_t module_base_find_module_by_name(module_t **pmodule, const char *module_name){
	if (!pmodule || !module_name)
	{
		return MODULE_ERR_INVALIDPARAM;
	}
	module_t *cur, *n;
	list_for_each_entry_safe(module_t, cur, n, &s_module_magager_ctx_t.m_module_list_head, m_list){
		if (!strcmp(cur->m_name, module_name))
		{
			*pmodule = cur;
			return MODULE_SUCCESS;
		}
	}
	return MODULE_FAILURE;
}