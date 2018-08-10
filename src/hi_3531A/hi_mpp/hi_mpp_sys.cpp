#include "hi_mpp_sys.h"
#include "hi3531a_platform.h"
#include "module_hi3531a.h"
#include <sys/sem.h>
#include <string.h>
#include <stdio.h>
#include "hi_includes.h"
#include "log.h"

#define HI_MPP_SYS_PRT(fmt...)   \
	do {\
	printf("[%s]-%d: ", __FUNCTION__, __LINE__);\
	printf(fmt);\
	}while(0)

int32_t hi_mpp_sys_init()
{
	if (1 != hi_platform_param.m_u8inited)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:hisi platform param was not ready", __FUNCTION__, __LINE__);
		return INTMODULE_HISI_ERR_SYS_NOTREADY;
	}
	VB_CONF_S       stVbConf;
	int32_t bytes_of_pixel;
	MPP_SYS_CONF_S stSysConf = {0};
	HI_S32 s32Ret = HI_FAILURE;
	HI_U32 i;

    memset(&stVbConf,0,sizeof(VB_CONF_S));
	if (!strcmp(hi_platform_param.m_strpixel_format, "sp420"))
	{
		bytes_of_pixel = 2;
	}
	else if (!strcmp(hi_platform_param.m_strpixel_format, "sp422"))
	{
		bytes_of_pixel = 2;
	}
	else if (!strcmp(hi_platform_param.m_strpixel_format, "sp444"))
	{
		bytes_of_pixel = 3;
	}
	else
		bytes_of_pixel = 2;

	if (hi_platform_param.m_u8vb_16m_cnt > 0)
	{
		stVbConf.astCommPool[0].u32BlkSize = 3840 * 2160 * bytes_of_pixel;
		stVbConf.astCommPool[0].u32BlkCnt =  hi_platform_param.m_u8vb_16m_cnt;
	}
	if (hi_platform_param.m_u8vb_4m_cnt > 0)
	{
		stVbConf.astCommPool[1].u32BlkSize = 1920 * 1088 * bytes_of_pixel;
		stVbConf.astCommPool[1].u32BlkCnt =  hi_platform_param.m_u8vb_4m_cnt;
	}
	if (hi_platform_param.m_u8vb_1m_cnt > 0)
	{
		stVbConf.astCommPool[2].u32BlkSize = 960 * 544 * bytes_of_pixel;
		stVbConf.astCommPool[2].u32BlkCnt =  hi_platform_param.m_u8vb_1m_cnt;
	}

    stVbConf.u32MaxPoolCnt = 128;

	HI_MPI_SYS_Exit();

	for(i=0;i<VB_MAX_USER;i++)
	{
		HI_MPI_VB_ExitModCommPool((VB_UID_E)i);
	}
	for(i=0; i<VB_MAX_POOLS; i++)
	{
		HI_MPI_VB_DestroyPool((VB_POOL)i);
	}
	HI_MPI_VB_Exit();

	s32Ret = HI_MPI_VB_SetConf(&stVbConf);
	if (HI_SUCCESS != s32Ret)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:HI_MPI_VB_SetConf failed width:0x%x", __FUNCTION__, __LINE__, s32Ret);
		return INTMODULE_HISI_FALSE;
	}

	s32Ret = HI_MPI_VB_Init();
	if (HI_SUCCESS != s32Ret)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:HI_MPI_VB_Init failed width:0x%x", __FUNCTION__, __LINE__, s32Ret);
		return INTMODULE_HISI_FALSE;
	}

	stSysConf.u32AlignWidth = HI_MPP_SYS_ALIGN_WIDTH;
	s32Ret = HI_MPI_SYS_SetConf(&stSysConf);
	if (HI_SUCCESS != s32Ret)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:HI_MPI_SYS_SetConf failed width:0x%x", __FUNCTION__, __LINE__, s32Ret);
		return INTMODULE_HISI_FALSE;
	}

	s32Ret = HI_MPI_SYS_Init();
	if (HI_SUCCESS != s32Ret)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:HI_MPI_SYS_Init failed width:0x%x", __FUNCTION__, __LINE__, s32Ret);
		return INTMODULE_HISI_FALSE;
	}
    return INTMODULE_HISI_OK;
}

int32_t hi_mpp_sys_uninit()
{
	HI_S32 i;

	HI_MPI_SYS_Exit();
	for(i=0;i<VB_MAX_USER;i++)
	{
		HI_MPI_VB_ExitModCommPool((VB_UID_E)i);
	}
	for(i=0; i<VB_MAX_POOLS; i++)
	{
		HI_MPI_VB_DestroyPool((VB_POOL)i);
	}	
	HI_MPI_VB_Exit();
	return INTMODULE_HISI_OK;
}