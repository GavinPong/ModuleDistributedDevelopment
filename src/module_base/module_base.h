#ifndef __MODULE_BASE_H__
#define __MODULE_BASE_H__

#define MODULE_OK 1
#define MODULE_FALSE 0
typedef enum _module_err_e{
	MODULE_ERR_INVALIDPARAM = 0xA0000001,			//参数异常
}module_err_e;

struct module_pub_data;
struct _module_s;

typedef struct list_node{
	struct list_node *next, *prev;
}LIST_NODE, *PLIST_NODE;

typedef struct _module_s{
	struct list_node m_list_node;
	char *m_name;			//module name
	char *m_desc;			//module desciption
	int m_module_id;		//module id
	void *m_priv_data;		//私有数据指针
	int *m_data_size;		//私有数据块大小
	int (*init)(module_t *pmodule);		//模块初始化接口
	int (*uninit)(module_t *pmodule);	//模块反初始化接口
	//供外部发命令给模块内部，或者使用模块内部某功能
	int (*command_process)(struct _module_s *pmodule, struct module_pub_data *pmodule_pub_data);
	//供外部发状态命令给模块内部，或者让模块将该状态通知到他的下级服务
	int (*sdk_process)(struct _module_s *pmodule, struct module_pub_data *pmodule_pub_data);
	//设置模块配置参数
	int (*config_set)(struct _module_s *pmodule, struct module_pub_data *pmodule_pub_data);
	//获取模块配置参数
	int (*config_get)(struct _module_s *pmodule, struct module_pub_data *pmodule_pub_data);
}module_t;

#endif