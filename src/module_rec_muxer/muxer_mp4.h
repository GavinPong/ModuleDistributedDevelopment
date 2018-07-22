#ifndef __MUXER_MP4_H__
#define __MUXER_MP4_H__

#include "muxer_neuter.h"

#ifdef __cplusplus
extern "C"{
#endif

int muxer_open_mp4(muxer_neuter_module_param_t *muxer_neuter_module_param);
int muxer_close_mp4(muxer_neuter_module_param_t *muxer_neuter_module_param);
int muxer_write_mp4(const char *in_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param);
int muxer_read_mp4(char *out_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param);

#ifdef __cplusplus
};
#endif

#endif