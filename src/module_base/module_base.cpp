#include "module_base.h"
#include "list.h"

typedef struct _module_magager_ctx{
	struct list_head m_module_list_head;
}module_magager_ctx_t;

static module_magager_ctx_t s_module_magager_ctx_t;

int module_manager_ctx_init(){
	INIT_LIST_HEAD(&s_module_magager_ctx_t.m_module_list_head);

	return MODULE_OK;
}

static int register_module(module_t *pmodule){
	if (!pmodule)
	{
		return MODULE_ERR_INVALIDPARAM;
	}
	list_add((struct list_head *)&pmodule->m_list_node, &s_module_magager_ctx_t.m_module_list_head);

	return MODULE_OK;
}

#define REGISTER_MODULE(module_name) {\
	extern module_t module_name##_module;\
	register_module(&module_name##_module);\
}

//ÿ����һ��module,�����ڴ˺�����ע���Ӧģ��
void register_all_module(){
	REGISTER_MODULE(dummy);	//ע������ģ��

}