#ifndef __MODULE_BASE_H__
#define __MODULE_BASE_H__

#define MODULE_OK 1
#define MODULE_FALSE 0

#ifdef __cplusplus
extern "C"{
#endif

#include "list.h"

#define MODULE_SUCCESS 1
#define MODULE_FAILURE 0
typedef enum _module_err_e{
	MODULE_ERR_INVALIDPARAM = 0xA0000001,			//�����쳣
}module_err_e;

struct module_pub_data;


typedef struct _module_s{
	struct list_head m_list;
	char *m_name;			//module name
	char *m_desc;			//module desciption
	int m_module_id;		//module id
	void *m_priv_data;		//˽������ָ��
	int *m_data_size;		//˽�����ݿ��С
	int (*init)(struct _module_s *pmodule);		//ģ���ʼ���ӿ�
	int (*uninit)(struct _module_s *pmodule);	//ģ�鷴��ʼ���ӿ�
	//���ⲿ�������ģ���ڲ�������ʹ��ģ���ڲ�ĳ����
	int (*process_command)(struct _module_s *pmodule, struct module_pub_data *pmodule_pub_data);
	//���ⲿ��״̬�����ģ���ڲ���������ģ�齫��״̬֪ͨ�������¼�����
	int (*process_status)(struct _module_s *pmodule, struct module_pub_data *pmodule_pub_data);
	//����ģ�����ò���
	int (*config_set)(struct _module_s *pmodule, struct module_pub_data *pmodule_pub_data);
	//��ȡģ�����ò���
	int (*config_get)(struct _module_s *pmodule, struct module_pub_data *pmodule_pub_data);
}module_t;

int module_manager_ctx_init();
int module_manager_ctx_uninit();
void register_all_module();
int find_module_by_name(module_t *pmodule, const char *module_name);

#ifdef __cplusplus
}
#endif

#endif