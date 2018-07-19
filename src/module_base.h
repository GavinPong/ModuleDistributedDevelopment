#ifndef __MODULE_BASE_H__
#define __MODULE_BASE_H__

#include "list.h"
#include "cross_platform.h"

#define MODULE_OK 1
#define MODULE_FALSE 0

#ifdef __cplusplus
extern "C"{
#endif

#define MODULE_SUCCESS 1
#define MODULE_FAILURE 0
typedef enum _module_err_e{
	MODULE_ERR_INVALIDPARAM = 0xA0000001,			//参数异常
}module_err_e;

struct module_pub_data;


typedef struct _module_s{
	struct list_head m_list;
	const char *m_name;			//module name
	const char *m_desc;			//module desciption
	int32_t m_module_id;		//module id
	void *m_priv_data;		//私有数据指针
	int32_t *m_data_size;		//私有数据块大小
	int32_t (*init)();		//模块初始化接口
	int32_t (*uninit)();	//模块反初始化接口
	//供外部发命令给模块内部，或者使用模块内部某功能
	int32_t (*process_command)(struct module_pub_data *pmodule_pub_data);
	//供外部发状态命令给模块内部，或者让模块将该状态通知到他的下级服务
	int32_t (*process_status)(struct module_pub_data *pmodule_pub_data);
	//设置模块配置参数
	int32_t (*config_set)(struct module_pub_data *pmodule_pub_data);
	//获取模块配置参数
	int32_t (*config_get)(struct module_pub_data *pmodule_pub_data, char *buf, int32_t buf_size);
}module_t;

typedef int32_t (*module_base_callback_t)(struct module_pub_data *pmodule_pub_data);
extern module_base_callback_t g_module_base_callback;

int32_t module_base_manager_ctx_init();
int32_t module_base_manager_ctx_uninit();
int32_t module_base_register_all_module();
void module_base_unregister_all_module();
int32_t module_base_find_module_by_name(module_t **pmodule, const char *module_name);

#ifdef __cplusplus
}
#endif

#endif