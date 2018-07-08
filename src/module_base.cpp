/*********************
module_base ���ã�
1���ṩ�ӿڽ�����ģ����䵽ģ����У�
2���ṩ�ӿ���controlerͨ��ģ��ID��ȡģ�����ģ�鹫�����ݿ飬���ⲿ���ö�Ӧģ��Ĺ��ܽӿ�
*********************/

#include "module_base.h"
#include "cJSON.h"
#include <stdio.h>


//module�����ֶ�
typedef struct _module_magager_ctx{
	int m_inited;
	struct list_head m_module_list_head;
}module_magager_ctx_t;

static module_magager_ctx_t s_module_magager_ctx_t;
static cJSON *root_module_table_json = NULL;

//ÿע��һ��ģ������ڱ������ģ������Ӧ��id��ÿ��ģ���id����Ψһ���ο�dummy dummy1
static char module_table[] = {
	"{\
		\"dummy\":0\
		\"dummy1\":1,\
	}"
};

int module_manager_ctx_init(){
	s_module_magager_ctx_t.m_inited = 1;
	INIT_LIST_HEAD(&s_module_magager_ctx_t.m_module_list_head);
	return MODULE_OK;
}

int module_manager_ctx_uninit(){
	s_module_magager_ctx_t.m_inited = 0;

	return MODULE_OK;
}

static int register_module(module_t *pmodule){
	if (!pmodule)
	{
		return MODULE_ERR_INVALIDPARAM;
	}
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

//ÿ���������붨��int module_name_module_all() �� int module_name_module_free()�ӿ�������ͷ�ģ���ڲ������ֶ�
#define DECLARE_MODULE_ALLOC_FUNCTION(module_name) int module_##module_name##_alloc()
#define DECLARE_MODULE_FREE_FUNCTION(module_name) int module_##module_name##_free()
#define MODULE_NAME_TO_STR(module_name) #module_name 

#define REGISTER_MODULE(module_name) {\
	DECLARE_MODULE_ALLOC_FUNCTION(module_name);\
	extern module_t module_##module_name;\
	cJSON *module_json;\
	module_json = cJSON_GetObjectItem(root_module_table_json,#module_name);\
	if (!module_json)\
	{\
		printf("%s->%d:%s does not register in the registry", MODULE_NAME_TO_STR(module_name));\
		return ;\
	}\
	module_##module_name##_alloc();\
	register_module(&module_##module_name);\
}

#define UNREGISTER_MODULE(module_name) {\
	DECLARE_MODULE_FREE_FUNCTION(module_name);\
	extern module_t module_##module_name;\
	cJSON *module_json;\
	module_json = cJSON_GetObjectItem(root_module_table_json,#module_name);\
	if (!module_json)\
	{\
		printf("%s->%d:%s does not register in the registry", MODULE_NAME_TO_STR(module_name));\
		return ;\
	}\
	unregister_module(&module_##module_name);\
	module_##module_name##_free();\
}

//ÿ����һ��module,�����ڴ˺�����ע���Ӧģ��
void register_all_module(){
	root_module_table_json = cJSON_Parse(module_table);
	if (!root_module_table_json)
	{
		printf("%s->%d:register_all_module failed because parse module table was failed.....\n", __FILE__, __LINE__);
	}
	/*****start ����ģ��ע��******/
	REGISTER_MODULE(dummy);	//ע������ģ��
	/*****end ����ģ��ע��******/
	cJSON_Delete(root_module_table_json);
	root_module_table_json = NULL;
}

	//ÿ����һ��module,�����ڴ˺�����ע���Ӧģ��
void unregister_all_module(){
	/*****start ����ģ�鷴ע��******/
	UNREGISTER_MODULE(dummy);	//ע������ģ��
	/*****end ����ģ�鷴ע��******/
}

int find_module_by_name(module_t *pmodule, const char *module_name){
	if (!pmodule || !module_name)
	{
		return MODULE_ERR_INVALIDPARAM;
	}
	module_t *n;
	list_for_each_entry_safe(module_t, pmodule, n, &s_module_magager_ctx_t.m_module_list_head, m_list){
		if (!strcmp(pmodule->m_name, module_name))
		{
			return MODULE_SUCCESS;
		}
	}
	return MODULE_FAILURE;
}