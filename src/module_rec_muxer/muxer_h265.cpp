#include "muxer_neuter.h"
#include "muxer_h265.h"

int muxer_open_h265(muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}

int muxer_close_h265(muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}

int muxer_write_h265(const char *in_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}

int muxer_read_h265(char *out_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}