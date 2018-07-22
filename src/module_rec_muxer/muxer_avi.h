#ifndef __MUXER_AVI_H__
#define __MUXER_AVI_H__

#include "muxer_neuter.h"

#ifdef __cplusplus
extern "C"{
#endif

int muxer_open_avi(muxer_neuter_module_param_t *muxer_neuter_module_param);
int muxer_close_avi(muxer_neuter_module_param_t *muxer_neuter_module_param);
int muxer_write_avi(const char *in_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param);
int muxer_read_avi(char *out_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param);

#ifdef __cplusplus
};
#endif

#endif