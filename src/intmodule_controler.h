/******************************************************************************

  Copyright (C), 2018-2020, .

 ******************************************************************************
  File Name     : intmodule_controler.h
  Version       : Initial Draft
  Author        : zp
  Created       : 2018/1/16
  Last Modified :
  Description   : intmodule_controler.c header file
  Function List :
  History       :
  1.Date        : 2018/1/30
    Author      : zp
    Modification: modify file
******************************************************************************/
#ifndef __MODULE_CONTROLER_H__
#define __MODULE_CONTROLER_H__

#include "gavin_error.h"
#include "intmodule_external.h"
#include "cross_platform.h"

typedef enum _int_mod_ctr_err_code_e{
	INT_MOD_CTR_ERR_MODULE_ID = 64,		//非法模块ID
	INT_MOD_CTR_ERR_PARSE_JSON,			//解析json异常
	INT_MOD_CTR_ERR_JSON_OBJ_EMPTY,		//json对象为空
	INT_MOD_CTR_ERR_SET_EMPTY,			//module集合为空
	INT_MOD_CTR_ERR_MATCH,				//module匹配失败
}int_mod_ctr_err_code_e;

#define INTMODULE_CTR_OK 1
#define INTMODULE_CTR_FALSE 0
#define INTMODULE_CTR_ERR_INVALID_DEVID			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_INVALID_DEVID)//无效设备ID
#define INTMODULE_CTR_ERR_INVALID_CHNID			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_INVALID_CHNID)//无效通道ID
#define INTMODULE_CTR_ERR_ILLEGAL_PARAM			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_ILLEGAL_PARAM)//非法参数
#define INTMODULE_CTR_ERR_EXIST			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_EXIST)//源已经存在
#define INTMODULE_CTR_ERR_UNEXIST			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_UNEXIST)//源已不存在
#define INTMODULE_CTR_ERR_NULL_PTR			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_NULL_PTR)//空指针
#define INTMODULE_CTR_ERR_NOT_CONFIG			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_NOT_CONFIG)//未初始化配置属性
#define INTMODULE_CTR_ERR_NOT_SUPPORT			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_NOT_SUPPORT)//操作或类型不支持
#define INTMODULE_CTR_ERR_NOT_PERM			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_NOT_PERM)//操作不允许
#define INTMODULE_CTR_ERR_NOT_NOMEM			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_NOMEM)//申请内存失败
#define INTMODULE_CTR_ERR_NOT_NOBUF			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_NOBUF)//申请buffer失败
#define INTMODULE_CTR_ERR_BUF_EMPTY			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_BUF_EMPTY)//buffer没有数据
#define INTMODULE_CTR_ERR_BUF_FULL			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_BUF_FULL)//buffer满了
#define INTMODULE_CTR_ERR_SYS_NOTREADY			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_SYS_NOTREADY)//系统未准备
#define INTMODULE_CTR_ERR_BADADDR			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_BADADDR)//错误地址
#define INTMODULE_CTR_ERR_BUSY			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_BUSY)//资源被占用
#define INTMODULE_CTR_ERR_MODULE_ID			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, INT_MOD_CTR_ERR_MODULE_ID)//非法模块ID
#define INTMODULE_CTR_ERR_PARSE_JSON			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, INT_MOD_CTR_ERR_PARSE_JSON)//解析json异常
#define INTMODULE_CTR_ERR_JSON_OBJ_EMPTY			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, INT_MOD_CTR_ERR_JSON_OBJ_EMPTY)//json对象为空
#define INTMODULE_CTR_ERR_SET_EMPTY			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, INT_MOD_CTR_ERR_SET_EMPTY)//模块集合为空
#define INTMODULE_CTR_ERR_MATCH			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, INT_MOD_CTR_ERR_MATCH)//模块匹配失败

#ifdef __cplusplus
extern "C"{
#endif

/************************************************************************/
/* 
启动intmodule，根据外部配置完成各个模块的启动
*/
/************************************************************************/
int32_t intmodule_ctrl_startup();
/************************************************************************/
/* 
关闭intmodule，关闭各个模块的启动
*/
/************************************************************************/
int32_t intmodule_ctrl_shutdown();
/************************************************************************/
/* 
根据参数调用模块的指定接口，完成指定的操作
*/
/************************************************************************/
int32_t intmodule_ctrl_process_cmd(module_pub_data_t *module_pub_data);
/************************************************************************/
/* 
根据参数调用模块的指定接口，获取对应模块的配置参数
*/
/************************************************************************/
int32_t intmodule_ctrl_get_config(module_pub_data_t *module_pub_data, char *buf, uint32_t buf_size);
/************************************************************************/
/* 
根据参数调用模块的指定接口，设置对应模块的配置参数
*/
/************************************************************************/
int32_t intmodule_ctrl_set_config(module_pub_data_t *module_pub_data);
/************************************************************************/
/* 
根据参数调用模块的指定接口，设置对应模块的配置参数
*/
/************************************************************************/
int32_t intmodule_ctrl_register_callback(int32_t (*callback)(module_pub_data_t *module_pub_data));
#ifdef __cplusplus
}
#endif

#endif