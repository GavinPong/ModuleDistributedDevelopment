/******************************
global_def.h is a file that storing global macro
*******************************/

//######所有模块名的宏定义都放在这里管理#########
//####### module name end ####################
#define  DUMMY "dummy"
//####### module name end ####################

//level 2 第三步对消息进行分类,只有通用模块和intmodule模块知道
typedef enum _interface_2_level_id_e{
	INTERFACE_SET_CONFIG,		//设置配置	
	INTERFACE_GET_CONFIG,		//获取配置
	INTERFACE_CMD,				//命令请求
	INTERFACE_MSG_STATUS,		//状态同步
	INTERFACE_MSG_CONFIG,		//配置同步
	INTERFACE_INTMODULE,		//下发给intmodule
	INTERFACE_LOG,				//日志信息
}interface_2_level_id_e;

//level 3 下发任务给具体模块,对intmodule开放
typedef enum _module_table_e{
	INTERFACE_DUMMY,			//设置配置	
}module_table_e;