#include "muxer_neuter.h"
#include "muxer_h264.h"

int muxer_open_h264(muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}

int muxer_close_h264(muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}

int muxer_write_h264(const char *in_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}

int muxer_read_h264(char *out_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}