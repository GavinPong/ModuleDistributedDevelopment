/******************************
global_def.h is a file that storing global macro
*******************************/

//######����ģ�����ĺ궨�嶼�����������#########
//####### module name end ####################
#define  DUMMY "dummy"
//####### module name end ####################

//level 2 ����������Ϣ���з���,ֻ��ͨ��ģ���intmoduleģ��֪��
typedef enum _interface_2_level_id_e{
	INTERFACE_SET_CONFIG,		//��������	
	INTERFACE_GET_CONFIG,		//��ȡ����
	INTERFACE_CMD,				//��������
	INTERFACE_MSG_STATUS,		//״̬ͬ��
	INTERFACE_MSG_CONFIG,		//����ͬ��
	INTERFACE_INTMODULE,		//�·���intmodule
	INTERFACE_LOG,				//��־��Ϣ
}interface_2_level_id_e;

//level 3 �·����������ģ��,��intmodule����
typedef enum _module_table_e{
	INTERFACE_DUMMY,			//��������	
}module_table_e;