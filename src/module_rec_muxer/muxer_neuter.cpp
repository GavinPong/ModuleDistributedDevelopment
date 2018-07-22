#include "muxer_neuter.h"
#include "module_rec_muxer.h"
#include "muxer_avi.h"
#include "muxer_mp4.h"
#include "muxer_flv.h"
#include "muxer_h264.h"
#include "muxer_h265.h"

typedef struct _muxer_neuter_param_s{
	union {
		muxer_mp4_param_t m_mp4_muxer_param;
		muxer_avi_param_t m_avi_muxer_param;
		muxer_flv_param_t m_flv_muxer_param;
		muxer_h264_param_t m_h264_muxer_param;
		muxer_h265_param_t m_h265_muxer_param;
	}m_muxer_param;
}muxer_neuter_param_t;

int muxer_neuter_open(muxer_type_e muxer_type, void *muxer_xxx_param, int param_size, muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	if (muxer_type >= MUXER_TYPE_MAX || muxer_type < MUXER_TYPE_MIN)
	{
		return INTMODULE_REC_MUXER_ERR_INVALID_MUXTYPE;
	}
	if (!muxer_neuter_module_param)
	{
		return INTMODULE_REC_MUXER_ERR_NULL_PTR;
	}

	switch(muxer_type)
	{
	case MUXER_TYPE_MP4:
		{
			if(sizeof(muxer_mp4_param_t) != param_size)
				return INTMODULE_REC_MUXER_ERR_ILLEGAL_PARAM;
			muxer_neuter_module_param->m_muxer_open_func = muxer_open_mp4;
			muxer_neuter_module_param->m_muxer_close_func = muxer_close_mp4;
			muxer_neuter_module_param->m_muxer_write_func = muxer_write_mp4;
			muxer_neuter_module_param->m_muxer_read_func = muxer_read_mp4;
		}
		break;
	case MUXER_TYPE_AVI4:
		{
			if(sizeof(muxer_avi_param_t) != param_size)
				return INTMODULE_REC_MUXER_ERR_ILLEGAL_PARAM;
			muxer_neuter_module_param->m_muxer_open_func = muxer_open_avi;
			muxer_neuter_module_param->m_muxer_close_func = muxer_close_avi;
			muxer_neuter_module_param->m_muxer_write_func = muxer_write_avi;
			muxer_neuter_module_param->m_muxer_read_func = muxer_read_avi;
		}
		break;
	case MUXER_TYPE_FLV:
		{
			if(sizeof(muxer_flv_param_t) != param_size)
				return INTMODULE_REC_MUXER_ERR_ILLEGAL_PARAM;
			muxer_neuter_module_param->m_muxer_open_func = muxer_open_flv;
			muxer_neuter_module_param->m_muxer_close_func = muxer_close_flv;
			muxer_neuter_module_param->m_muxer_write_func = muxer_write_flv;
			muxer_neuter_module_param->m_muxer_read_func = muxer_read_flv;
		}
		break;
	case MUXER_TYPE_H264:
		{
			if(sizeof(muxer_h264_param_t) != param_size)
				return INTMODULE_REC_MUXER_ERR_ILLEGAL_PARAM;
			muxer_neuter_module_param->m_muxer_open_func = muxer_open_h264;
			muxer_neuter_module_param->m_muxer_close_func = muxer_close_h264;
			muxer_neuter_module_param->m_muxer_write_func = muxer_write_h264;
			muxer_neuter_module_param->m_muxer_read_func = muxer_read_h264;
		}
		break;
	case MUXER_TYPE_H265:
		{
			if(sizeof(muxer_h265_param_t) != param_size)
				return INTMODULE_REC_MUXER_ERR_ILLEGAL_PARAM;
			muxer_neuter_module_param->m_muxer_open_func = muxer_open_h265;
			muxer_neuter_module_param->m_muxer_close_func = muxer_close_h265;
			muxer_neuter_module_param->m_muxer_write_func = muxer_write_h265;
			muxer_neuter_module_param->m_muxer_read_func = muxer_read_h265;
		}
		break;
	}
	if (muxer_neuter_module_param->m_muxer_data)
	{
		free(muxer_neuter_module_param->m_muxer_data);
	}
	muxer_neuter_module_param->m_muxer_data = calloc(1, sizeof(param_size));
	if (!muxer_neuter_module_param->m_muxer_data)
	{
		return INTMODULE_REC_MUXER_ERR_NOT_NOMEM;
	}
	memcpy(muxer_neuter_module_param->m_muxer_data, muxer_xxx_param, sizeof(param_size));
	if (muxer_neuter_module_param->m_muxer_open_func)
	{
		muxer_neuter_module_param->m_muxer_open_func(muxer_neuter_module_param);
	}

	return INTMODULE_REC_MUXER_OK;
}

int muxer_neuter_close(muxer_neuter_module_param_t *muxer_neuter_module_param)
{
	if (!muxer_neuter_module_param)
	{
		return INTMODULE_REC_MUXER_ERR_NULL_PTR;
	}

	if (muxer_neuter_module_param->m_muxer_close_func)
	{
		muxer_neuter_module_param->m_muxer_close_func(muxer_neuter_module_param);
	}
	if (muxer_neuter_module_param->m_muxer_data)
	{
		free(muxer_neuter_module_param->m_muxer_data);
		muxer_neuter_module_param->m_muxer_data = NULL;
	}
	return INTMODULE_REC_MUXER_OK;
}

int muxer_neuter_write(const char *in_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param)
{

	return INTMODULE_REC_MUXER_OK;
}

int muxer_neuter_read(char *out_data_buf, int buf_size, muxer_neuter_module_param_t *muxer_neuter_module_param)
{

	return INTMODULE_REC_MUXER_OK;
}