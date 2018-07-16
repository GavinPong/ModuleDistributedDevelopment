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
	INT_MOD_CTR_ERR_MODULE_ID = 64,		//�Ƿ�ģ��ID
	INT_MOD_CTR_ERR_PARSE_JSON,			//����json�쳣
	INT_MOD_CTR_ERR_JSON_OBJ_EMPTY,		//json����Ϊ��
	INT_MOD_CTR_ERR_SET_EMPTY,			//module����Ϊ��
	INT_MOD_CTR_ERR_MATCH,				//moduleƥ��ʧ��
}int_mod_ctr_err_code_e;

#define INTMODULE_CTR_OK 1
#define INTMODULE_CTR_FALSE 0
#define INTMODULE_CTR_ERR_INVALID_DEVID			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_INVALID_DEVID)//��Ч�豸ID
#define INTMODULE_CTR_ERR_INVALID_CHNID			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_INVALID_CHNID)//��Чͨ��ID
#define INTMODULE_CTR_ERR_ILLEGAL_PARAM			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_ILLEGAL_PARAM)//�Ƿ�����
#define INTMODULE_CTR_ERR_EXIST			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_EXIST)//Դ�Ѿ�����
#define INTMODULE_CTR_ERR_UNEXIST			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_UNEXIST)//Դ�Ѳ�����
#define INTMODULE_CTR_ERR_NULL_PTR			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_NULL_PTR)//��ָ��
#define INTMODULE_CTR_ERR_NOT_CONFIG			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_NOT_CONFIG)//δ��ʼ����������
#define INTMODULE_CTR_ERR_NOT_SUPPORT			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_NOT_SUPPORT)//���������Ͳ�֧��
#define INTMODULE_CTR_ERR_NOT_PERM			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_NOT_PERM)//����������
#define INTMODULE_CTR_ERR_NOT_NOMEM			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_NOMEM)//�����ڴ�ʧ��
#define INTMODULE_CTR_ERR_NOT_NOBUF			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_NOBUF)//����bufferʧ��
#define INTMODULE_CTR_ERR_BUF_EMPTY			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_BUF_EMPTY)//bufferû������
#define INTMODULE_CTR_ERR_BUF_FULL			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_BUF_FULL)//buffer����
#define INTMODULE_CTR_ERR_SYS_NOTREADY			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_SYS_NOTREADY)//ϵͳδ׼��
#define INTMODULE_CTR_ERR_BADADDR			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_BADADDR)//�����ַ
#define INTMODULE_CTR_ERR_BUSY			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_BUSY)//��Դ��ռ��
#define INTMODULE_CTR_ERR_MODULE_ID			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, INT_MOD_CTR_ERR_MODULE_ID)//�Ƿ�ģ��ID
#define INTMODULE_CTR_ERR_PARSE_JSON			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, INT_MOD_CTR_ERR_PARSE_JSON)//����json�쳣
#define INTMODULE_CTR_ERR_JSON_OBJ_EMPTY			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, INT_MOD_CTR_ERR_JSON_OBJ_EMPTY)//json����Ϊ��
#define INTMODULE_CTR_ERR_SET_EMPTY			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, INT_MOD_CTR_ERR_SET_EMPTY)//ģ�鼯��Ϊ��
#define INTMODULE_CTR_ERR_MATCH			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_CTR, GAVIN_ERR_LEVEL_ERROR, INT_MOD_CTR_ERR_MATCH)//ģ��ƥ��ʧ��

#ifdef __cplusplus
extern "C"{
#endif

/************************************************************************/
/* 
����intmodule�������ⲿ������ɸ���ģ�������
*/
/************************************************************************/
int32_t intmodule_ctrl_startup();
/************************************************************************/
/* 
�ر�intmodule���رո���ģ�������
*/
/************************************************************************/
int32_t intmodule_ctrl_shutdown();
/************************************************************************/
/* 
���ݲ�������ģ���ָ���ӿڣ����ָ���Ĳ���
*/
/************************************************************************/
int32_t intmodule_ctrl_process_cmd(module_pub_data_t *module_pub_data);
/************************************************************************/
/* 
���ݲ�������ģ���ָ���ӿڣ���ȡ��Ӧģ������ò���
*/
/************************************************************************/
int32_t intmodule_ctrl_get_config(module_pub_data_t *module_pub_data, char *buf, uint32_t buf_size);
/************************************************************************/
/* 
���ݲ�������ģ���ָ���ӿڣ����ö�Ӧģ������ò���
*/
/************************************************************************/
int32_t intmodule_ctrl_set_config(module_pub_data_t *module_pub_data);
/************************************************************************/
/* 
���ݲ�������ģ���ָ���ӿڣ����ö�Ӧģ������ò���
*/
/************************************************************************/
int32_t intmodule_ctrl_register_callback(int32_t (*callback)(module_pub_data_t *module_pub_data));
#ifdef __cplusplus
}
#endif

#endif