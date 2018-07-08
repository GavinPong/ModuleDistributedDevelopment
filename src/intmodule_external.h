/******************************
module_external.h is a file that storing the data structure used for common external use
*******************************/
#ifndef __MODULE_EXTERNAL_H__
#define __MODULE_EXTERNAL_H__
#include "cross_platform.h"

//Module common data structure
//����ʽӦ��ע���ֽڶ���
typedef struct module_pub_data{
	int32_t m_length;					//���ݳ���
	int16_t m_check_code;				//У����
	int16_t m_type_id;				//�������
	uint32_t m_param;					//����1�����������������ͣ�Ҳ��������������
	uint32_t m_param1;					//����2�������������ͣ�Ҳ��������������
	uint32_t m_param2;					//����3�������������ͣ�Ҳ��������������
	int16_t m_stream_id;				//������
	int16_t m_reserved;				//�����ֶ�
	uint32_t m_channel_id;		//ͨ��ID
	char m_data_ptr[];				//
}module_pub_data_t;



#endif