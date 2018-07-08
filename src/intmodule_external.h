/******************************
module_external.h is a file that storing the data structure used for common external use
*******************************/
#ifndef __MODULE_EXTERNAL_H__
#define __MODULE_EXTERNAL_H__
#include "cross_platform.h"

//Module common data structure
//定义式应该注意字节对齐
typedef struct module_pub_data{
	int32_t m_length;					//数据长度
	int16_t m_check_code;				//校验码
	int16_t m_type_id;				//命令父类型
	uint32_t m_param;					//参数1，可以是命令子类型，也可以是其他参数
	uint32_t m_param1;					//参数2，可以是子类型，也可以是其他参数
	uint32_t m_param2;					//参数3，可以是子类型，也可以是其他参数
	int16_t m_stream_id;				//流类型
	int16_t m_reserved;				//保留字段
	uint32_t m_channel_id;		//通道ID
	char m_data_ptr[];				//
}module_pub_data_t;



#endif