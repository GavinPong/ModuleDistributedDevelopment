#ifndef __MUXER_H264_H__
#define __MUXER_H264_H__

#include "muxer_neuter.h"

#ifdef __cplusplus
extern "C"{
#endif

int muxer_open_h264(muxer_neuter_module_param_t *muxer_neuter_module_param);
int muxer_close_h264(muxer_neuter_module_param_t *muxer_neuter_module_param);
int muxer_write_h264(const char *in_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param);
int muxer_read_h264(char *out_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param);

#ifdef __cplusplus
};
#endif

#endif