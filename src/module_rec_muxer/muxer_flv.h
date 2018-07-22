#ifndef __MUXER_FLV_H__
#define __MUXER_FLV_H__

#include "muxer_neuter.h"

#ifdef __cplusplus
extern "C"{
#endif

int muxer_open_flv(muxer_neuter_module_param_t *muxer_neuter_module_param);
int muxer_close_flv(muxer_neuter_module_param_t *muxer_neuter_module_param);
int muxer_write_flv(const char *in_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param);
int muxer_read_flv(char *out_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param);

#ifdef __cplusplus
};
#endif

#endif