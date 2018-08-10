#include <stdio.h>
#include <string.h>
#include "log.h"
#include "cross_platform.h"
#include "hi_ui_manager.h"
#include "module_hi3531a.h"
#include "hi3531a_platform.h"
#include "hi_ui_osdpic_test.h"

#define OSDPIC_PATHNAME "./res/osd.bmp"


typedef struct _hi_ui_ctx_s{
	int32_t m_gra_layer_cnt;	//Í¼ÐÎ²ãÊý
}hi_ui_ctx_t;

int32_t hi_ui_manager_init()
{
	log_output(LOG_LEVEL_FILE_SCREEN,"%s->%d:into %s",__FUNCTION__, __LINE__, __FUNCTION__);
	hi_ui_osdpic_test_open(OSDPIC_PATHNAME);

	return INTMODULE_HISI_OK;
}

int32_t hi_ui_manager_uninit()
{
	hi_ui_osdpic_test_close();

	return INTMODULE_HISI_OK;
}