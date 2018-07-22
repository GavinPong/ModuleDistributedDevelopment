#ifndef __MUXER_H265_H__
#define __MUXER_H265_H__

#include "muxer_neuter.h"

#ifdef __cplusplus
extern "C"{
#endif

int muxer_open_h265(muxer_neuter_module_param_t *muxer_neuter_module_param);
int muxer_close_h265(muxer_neuter_module_param_t *muxer_neuter_module_param);
int muxer_write_h265(const char *in_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param);
int muxer_read_h265(char *out_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param);

#ifdef __cplusplus
};
#endif

#endif