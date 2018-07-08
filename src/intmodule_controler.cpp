/*******************************
module_controler���ã�
1������module_base�Ľӿ���ɽ�����ģ����䵽module_baseģ����У�
2����ȡ���ñ��������ñ�ģ�������Ĳ�������module_baseģ�����ȡ����Ӧģ�鹫�����ݿ��ַ��ŵ�m_module_table_ptr�У���controler�ӿ�ʹ��

*******************************/

#include "intmodule_external.h"	//�����module_base.hǰ�������ܱ��벻��
#include "module_base.h"
#include "intmodule_controler.h"
#include "filefunc.h"
#include "cJSON.h"
#include "global_def.h"

//����ģ�������������ļ�
#define  INTMODULE_JSON "/mnt/mtd/intmod.json"


typedef struct module_ctrl_ctx_s{
	int m_inited;						//�Ƿ��Ѿ���ʼ��
}module_ctrl_ctx_t, *pmodule_ctrl_ctx_t;

static module_ctrl_ctx_t s_module_ctrl_ctx;

static int intmodule_ctrl_load_module(){

	return INTMODULE_CTR_OK;
}

int intmodule_ctrl_init_ctx(){
	memset(&s_module_ctrl_ctx, 0, sizeof(s_module_ctrl_ctx));
	s_module_ctrl_ctx.m_inited = 1;
	return INTMODULE_CTR_OK;
}

int intmodule_ctrl_uninit_ctx(){
	s_module_ctrl_ctx.m_inited = 0;

	return INTMODULE_CTR_OK;
}

int intmodule_ctrl_startup(){
	cJSON *root_json;
	//����洢����ģ�鹫�����ݿ��ַ�ĵ�ַ��
	
	intmodule_ctrl_init_ctx();
	register_all_module();
	FILE_FUNC_Get_Json_Form_File(INTMODULE_JSON, &root_json);

	return INTMODULE_CTR_OK;
}

int intmodule_ctrl_shutdown(){

	return INTMODULE_CTR_OK;
}

int intmodule_ctrl_process_cmd(){

	return INTMODULE_CTR_OK;
}

int intmodule_ctrl_get_config(){
	
}

int intmodule_ctrl_set_config(){


}