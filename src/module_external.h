/******************************
module_external.h is a file that storing the data structure used for common external use
*******************************/
#ifndef __MODULE_EXTERNAL_H__
#define __MODULE_EXTERNAL_H__


//Module common data structure
//����ʽӦ��ע���ֽڶ���
typedef struct module_pub_data{
	int m_length;					//���ݳ���
	short m_check_code;				//У����
	short m_type_id;				//�������
	DWORD m_param;					//����1�����������������ͣ�Ҳ��������������
	DWORD m_param1;					//����2�������������ͣ�Ҳ��������������
	DWORD m_param2;					//����3�������������ͣ�Ҳ��������������
	short m_stream_id;				//������
	short m_reserved;				//�����ֶ�
	unsigned int m_channel_id;		//ͨ��ID
	char m_data_ptr[];				//
}module_pub_data_t;



#endif