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

//功能模块启动项配置文件
#define  INTMODULE_JSON "/mnt/mtd/intmod.json"


typedef struct module_ctrl_ctx_s{
	int m_inited;						//是否已经初始化
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
	//申请存储所有模块公共数据块地址的地址表
	
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