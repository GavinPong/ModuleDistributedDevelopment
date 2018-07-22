#ifndef __MUXER_NEUTER_H__
#define __MUXER_NEUTER_H__

#include "module_rec_muxer.h"

typedef enum __muxer_type_e{
	MUXER_TYPE_MIN,

	MUXER_TYPE_MP4,
	MUXER_TYPE_AVI4,
	MUXER_TYPE_FLV,
	MUXER_TYPE_H264,
	MUXER_TYPE_H265,

	MUXER_TYPE_MAX,
}muxer_type_e;

typedef struct __muxer_mp4_param_s{

}muxer_mp4_param_t;

typedef struct __muxer_avi_param_s{

}muxer_avi_param_t;

typedef struct __muxer_flv_param_s{

}muxer_flv_param_t;

typedef struct __muxer_h264_param_s{

}muxer_h264_param_t;

typedef struct __muxer_h265_param_s{

}muxer_h265_param_t;

typedef int (*muxer_open_func_t)(struct _muxer_neuter_module_param_s *muxer_neuter_module_param);
typedef int (*muxer_close_func_t)(struct _muxer_neuter_module_param_s *muxer_neuter_module_param);
typedef int (*muxer_write_func_t)(const char *in_data_buf, int buf_size, struct _muxer_neuter_module_param_s *muxer_neuter_module_param);
typedef int (*muxer_read_func_t)(char *out_data_buf, int buf_size, struct _muxer_neuter_module_param_s *muxer_neuter_module_param);

typedef struct _muxer_neuter_module_param_s{
	muxer_type_e m_muxer_type;
	void *m_muxer_data;
	void *m_priv_data;
	muxer_open_func_t m_muxer_open_func;
	muxer_close_func_t m_muxer_close_func;
	muxer_write_func_t m_muxer_write_func;
	muxer_read_func_t m_muxer_read_func;
}muxer_neuter_module_param_t;

#ifdef __cplusplus
extern "C"{
#endif

int muxer_neuter_open(muxer_type_e muxer_type, void *muxer_xxx_param, int param_size, muxer_neuter_module_param_t *muxer_neuter_module_param);
int muxer_neuter_close(muxer_neuter_module_param_t *muxer_neuter_module_param);
int muxer_neuter_write(const char *in_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param);
int muxer_neuter_read(char *out_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param);

#ifdef __cplusplus
};
#endif

#endif