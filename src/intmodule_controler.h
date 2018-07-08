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

#define INTMODULE_CTR_OK 1
#define INTMODULE_CTR_FALSE 0
#define INTMODULE_CTR_ERR_OVERLOW -1

#include "intmodule_external.h"
#include "cross_platform.h"

#ifdef __cplusplus
extern "C"{
#endif

/************************************************************************/
/* 
启动intmodule，根据外部配置完成各个模块的启动
*/
/************************************************************************/
int intmodule_ctrl_startup();
/************************************************************************/
/* 
关闭intmodule，关闭各个模块的启动
*/
/************************************************************************/
int intmodule_ctrl_shutdown();
/************************************************************************/
/* 
根据参数调用模块的指定接口，完成指定的操作
*/
/************************************************************************/
int intmodule_ctrl_process_cmd(module_pub_data_t *module_pub_data);
/************************************************************************/
/* 
根据参数调用模块的指定接口，获取对应模块的配置参数
*/
/************************************************************************/
int intmodule_ctrl_get_config(module_pub_data_t *module_pub_data, char *buf, uint32_t buf_size);
/************************************************************************/
/* 
根据参数调用模块的指定接口，设置对应模块的配置参数
*/
/************************************************************************/
int intmodule_ctrl_set_config();
/************************************************************************/
/* 
根据参数调用模块的指定接口，设置对应模块的配置参数
*/
/************************************************************************/
int intmodule_ctrl_register_callback();
#ifdef __cplusplus
}
#endif

#endif