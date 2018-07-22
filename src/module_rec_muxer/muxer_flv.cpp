#include "muxer_neuter.h"
#include "muxer_flv.h"

int muxer_open_flv(muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}

int muxer_close_flv(muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}

int muxer_write_flv(const char *in_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}

int muxer_read_flv(char *out_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}