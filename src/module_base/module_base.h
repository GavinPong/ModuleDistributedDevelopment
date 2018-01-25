#ifndef __MODULE_BASE_H__
#define __MODULE_BASE_H__

#define MODULE_OK 1
#define MODULE_FALSE 0
typedef enum _module_err_e{
	MODULE_ERR_INVALIDPARAM = 0xA0000001,			//�����쳣
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
	void *m_priv_data;		//˽������ָ��
	int *m_data_size;		//˽�����ݿ��С
	int (*init)(module_t *pmodule);		//ģ���ʼ���ӿ�
	int (*uninit)(module_t *pmodule);	//ģ�鷴��ʼ���ӿ�
	//���ⲿ�������ģ���ڲ�������ʹ��ģ���ڲ�ĳ����
	int (*command_process)(struct _module_s *pmodule, struct module_pub_data *pmodule_pub_data);
	//���ⲿ��״̬�����ģ���ڲ���������ģ�齫��״̬֪ͨ�������¼�����
	int (*sdk_process)(struct _module_s *pmodule, struct module_pub_data *pmodule_pub_data);
	//����ģ�����ò���
	int (*config_set)(struct _module_s *pmodule, struct module_pub_data *pmodule_pub_data);
	//��ȡģ�����ò���
	int (*config_get)(struct _module_s *pmodule, struct module_pub_data *pmodule_pub_data);
}module_t;

#endif