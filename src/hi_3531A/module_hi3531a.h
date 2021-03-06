#ifndef __MODULE_HI3531A_H__
#define __MODULE_HI3531A_H__

#include "gavin_error.h"
#include "cross_platform.h"

//自定义错误ID，必须大于64，否则会与通用ID冲突
typedef enum _int_mod_rec_muxer_err_code_e{
	INT_MOD_HISI_ERR_OPEN_DEV = 64,			//打开设备失败
	INT_MOD_HISI_ERR_FRAME_RATE = 65,			//帧率异常
	INT_MOD_HISI_ERR_PARSE_JSON,			//解析json异常
}int_mod_rec_muxer_err_code_e;

#define INTMODULE_HISI_OK 1
#define INTMODULE_HISI_FALSE 0
#define INTMODULE_HISI_ERR_INVALID_DEVID			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_HISI, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_INVALID_DEVID)//无效设备ID
#define INTMODULE_HISI_ERR_INVALID_CHNID			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_HISI, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_INVALID_CHNID)//无效通道ID
#define INTMODULE_HISI_ERR_ILLEGAL_PARAM			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_HISI, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_ILLEGAL_PARAM)//非法参数
#define INTMODULE_HISI_ERR_EXIST			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_HISI, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_EXIST)//源已经存在
#define INTMODULE_HISI_ERR_UNEXIST			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_HISI, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_UNEXIST)//源已不存在
#define INTMODULE_HISI_ERR_NULL_PTR			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_HISI, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_NULL_PTR)//空指针
#define INTMODULE_HISI_ERR_NOT_CONFIG			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_HISI, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_NOT_CONFIG)//未初始化配置属性
#define INTMODULE_HISI_ERR_NOT_SUPPORT			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_HISI, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_NOT_SUPPORT)//操作或类型不支持
#define INTMODULE_HISI_ERR_NOT_PERM			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_HISI, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_NOT_PERM)//操作不允许
#define INTMODULE_HISI_ERR_NOT_NOMEM			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_HISI, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_NOMEM)//申请内存失败
#define INTMODULE_HISI_ERR_NOT_NOBUF			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_HISI, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_NOBUF)//申请buffer失败
#define INTMODULE_HISI_ERR_BUF_EMPTY			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_HISI, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_BUF_EMPTY)//buffer没有数据
#define INTMODULE_HISI_ERR_BUF_FULL			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_HISI, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_BUF_FULL)//buffer满了
#define INTMODULE_HISI_ERR_SYS_NOTREADY			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_HISI, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_SYS_NOTREADY)//系统未准备
#define INTMODULE_HISI_ERR_BADADDR			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_HISI, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_BADADDR)//错误地址
#define INTMODULE_HISI_ERR_BUSY			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_HISI, GAVIN_ERR_LEVEL_ERROR, GAVIN_ERR_BUSY)//资源被占用
#define INTMODULE_HISI_ERR_OPEN_DEV			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_HISI, GAVIN_ERR_LEVEL_ERROR, INT_MOD_HISI_ERR_OPEN_DEV)//打开设备失败
#define INTMODULE_HISI_ERR_FRAME_RATE			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_HISI, GAVIN_ERR_LEVEL_ERROR, INT_MOD_HISI_ERR_FRAME_RATE)//帧率异常
#define INTMODULE_HISI_ERR_PARSE_JSON			GAVIN_DEF_ERR(GAVIN_MODE_ID_INT_MOD_HISI, GAVIN_ERR_LEVEL_ERROR, INT_MOD_HISI_ERR_PARSE_JSON)//帧率异常

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
};
#endif

#endif