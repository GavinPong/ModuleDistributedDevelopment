#include "muxer_neuter.h"
#include "muxer_avi.h"

int muxer_open_avi(muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}

int muxer_close_avi(muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}

int muxer_write_avi(const char *in_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}

int muxer_read_avi(char *out_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	return INTMODULE_REC_MUXER_OK;
}