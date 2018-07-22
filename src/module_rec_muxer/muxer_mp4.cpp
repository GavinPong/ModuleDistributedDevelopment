#include "muxer_neuter.h"
#include "muxer_mp4.h"

int muxer_open_mp4(muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}

int muxer_close_mp4(muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}

int muxer_write_mp4(const char *in_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}

int muxer_read_mp4(char *out_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}