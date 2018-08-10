#include "hi3531a_platform.h"
#include "module_hi3531a.h"
#include "cJSON.h"
#include <stdio.h>
#include <string.h>
#include "filefunc.h"
#include "hi_mpp_vo.h"
#include "log.h"


#define HISI_PLATFORM_FILE "/mnt/mtd/hi_platform.json"

typedef struct _hi3531a_platform_ctx_s{
	int32_t m_inited;
}hi3531a_platform_ctx_t;

hi_platform_param_t hi_platform_param;
static hi3531a_platform_ctx_t hi3531a_platform_ctx = {0};

static void hi3531a_platform_init_vb_info()
{
	hi_platform_param.m_u8vb_16m_cnt = 0;
	hi_platform_param.m_u8vb_4m_cnt = 50;
	hi_platform_param.m_u8vb_1m_cnt = 50;
}

static void hi3531a_platform_init_vo_dev_info()
{
	hi_platform_param.m_mpp_vo_dev_params[0].m_devid = HI_3531A_DHD0;
	hi_platform_param.m_mpp_vo_dev_params[0].m_dis_frame_rate = 60;
	hi_platform_param.m_mpp_vo_dev_params[0].m_dis_width = 1920;
	hi_platform_param.m_mpp_vo_dev_params[0].m_dis_height = 1080;
	hi_platform_param.m_mpp_vo_dev_params[0].m_dis_xpos = 0;
	hi_platform_param.m_mpp_vo_dev_params[0].m_dis_ypos = 0;
	hi_platform_param.m_mpp_vo_dev_params[0].m_enintf_sync = HI_MPP_VO_OUTPUT_1080P60;
	hi_platform_param.m_mpp_vo_dev_params[0].m_s32intf_type = HI_MPP_VO_INTF_BT1120;
	hi_platform_param.m_mpp_vo_dev_params[0].m_pixel_format = HI_MPP_VO_PIXEL_FORMAT_YUV_SEMIPLANAR_420;
	hi_platform_param.m_mpp_vo_dev_params[0].m_u32bg_color = 0x000000;

	hi_platform_param.m_mpp_vo_dev_params[1].m_devid = HI_3531A_DHD1;
	hi_platform_param.m_mpp_vo_dev_params[1].m_dis_frame_rate = 60;
	hi_platform_param.m_mpp_vo_dev_params[1].m_dis_width = 1920;
	hi_platform_param.m_mpp_vo_dev_params[1].m_dis_height = 1080;
	hi_platform_param.m_mpp_vo_dev_params[1].m_dis_xpos = 0;
	hi_platform_param.m_mpp_vo_dev_params[1].m_dis_ypos = 0;
	hi_platform_param.m_mpp_vo_dev_params[1].m_enintf_sync = HI_MPP_VO_OUTPUT_1080P60;
	hi_platform_param.m_mpp_vo_dev_params[1].m_s32intf_type = HI_MPP_VO_INTF_VGA | HI_MPP_VO_INTF_HDMI;/* | HI_MPP_VO_INTF_CVBS*/;
	hi_platform_param.m_mpp_vo_dev_params[1].m_pixel_format = HI_MPP_VO_PIXEL_FORMAT_YUV_SEMIPLANAR_420;
	hi_platform_param.m_mpp_vo_dev_params[1].m_u32bg_color = 0x0000FF;

	hi_platform_param.m_mpp_vo_dev_params[2].m_devid = HI_3531A_DSD0;
	hi_platform_param.m_mpp_vo_dev_params[2].m_dis_frame_rate = 30;
	hi_platform_param.m_mpp_vo_dev_params[2].m_dis_width = 720;
	hi_platform_param.m_mpp_vo_dev_params[2].m_dis_height = 480;
	hi_platform_param.m_mpp_vo_dev_params[2].m_dis_xpos = 0;
	hi_platform_param.m_mpp_vo_dev_params[2].m_dis_ypos = 0;
	hi_platform_param.m_mpp_vo_dev_params[2].m_enintf_sync = HI_MPP_VO_OUTPUT_NTSC;
	hi_platform_param.m_mpp_vo_dev_params[2].m_s32intf_type = HI_MPP_VO_INTF_CVBS;
	hi_platform_param.m_mpp_vo_dev_params[2].m_pixel_format = HI_MPP_VO_PIXEL_FORMAT_YUV_SEMIPLANAR_420;
	hi_platform_param.m_mpp_vo_dev_params[2].m_u32bg_color = 0x0000ff;
}

static void hi3531a_platform_init_ui_info()
{
	hi_platform_param.m_ui_params[0].m_enable = 0;
	hi_platform_param.m_ui_params[0].m_has_mouse = 0;
	plat_sprintf(hi_platform_param.m_ui_params[0].m_fb_name, sizeof(hi_platform_param.m_ui_params[0].m_fb_name), "/dev/fb0");
	plat_sprintf(hi_platform_param.m_ui_params[0].m_ui_name, sizeof(hi_platform_param.m_ui_params[0].m_ui_name), "direct");
	hi_platform_param.m_ui_params[0].m_vo_dev_id = 0;

	hi_platform_param.m_ui_params[1].m_enable = 1;
	hi_platform_param.m_ui_params[1].m_has_mouse = 1;
	plat_sprintf(hi_platform_param.m_ui_params[1].m_fb_name, sizeof(hi_platform_param.m_ui_params[0].m_fb_name), "/dev/fb1");
	plat_sprintf(hi_platform_param.m_ui_params[1].m_ui_name, sizeof(hi_platform_param.m_ui_params[0].m_ui_name), "touch");
	hi_platform_param.m_ui_params[1].m_vo_dev_id = 1;

	hi_platform_param.m_ui_params[2].m_enable = 1;
	hi_platform_param.m_ui_params[2].m_has_mouse = 0;
	plat_sprintf(hi_platform_param.m_ui_params[2].m_fb_name, sizeof(hi_platform_param.m_ui_params[0].m_fb_name), "/dev/fb2");
	plat_sprintf(hi_platform_param.m_ui_params[2].m_ui_name, sizeof(hi_platform_param.m_ui_params[0].m_ui_name), "panel");
	hi_platform_param.m_ui_params[2].m_vo_dev_id = 2;
}

//流程:代码初始化-->从文件中加载参数，成功加载了的参数直接覆盖掉代码初始化的参数-->反初始化（一般用不着）
//代码直接初始化（指定）平台参数的接口
int32_t hi3531a_platform_init()
{
	if (1 == hi3531a_platform_ctx.m_inited)
	{
		return INTMODULE_HISI_ERR_BUSY;
	}
	hi3531a_platform_ctx.m_inited = 1;
	memset(&hi_platform_param, 0, sizeof(hi_platform_param));
	plat_sprintf(hi_platform_param.m_strpixel_format, sizeof(hi_platform_param.m_strpixel_format),"sp420");
	hi3531a_platform_init_vb_info();
	hi3531a_platform_init_vo_dev_info();
	hi3531a_platform_init_ui_info();

	hi_platform_param.m_u8inited = 1;//放在尾部
	return INTMODULE_HISI_OK;
}

//代码反初始化（指定）平台参数的接口
int32_t hi3531a_platform_uninit()
{
	if (0 == hi3531a_platform_ctx.m_inited)
	{
		return INTMODULE_HISI_ERR_SYS_NOTREADY;
	}
	hi3531a_platform_ctx.m_inited = 0;
	return INTMODULE_HISI_OK;
}

/*  json format
{
	"vb_info":{
		"vb_blksize_16m":0,
		"vb_blksize_4m":50,
		"vb_blksize_1m":50,
	},
	"vo_dev_info":[
		{"vodev":0, "intfsync":"1080p60", "intftype1":"vga","intftype2":"bt1120", "audio":0,"xpos":0,"ypos":0,"width":1920,"height":1080},
		{"vodev":1, "intfsync":"1080p60","intftype1":"hdmi","audio":0,"xpos":0,"ypos":0,"width":1920,"height":1080},
		{"vodev":2,"intfsync":"ntsc","intftype1":"cvbs","audio":0,"xpos":0,"ypos":0,"width":720,"height":480}
	],
	"ui_info":[
		{"vodev":0,"ui_dev":"fb0","mouse":1,"ui_name":"direct","enable":1},
		{"vodev":1,"ui_dev":"fb1","mouse":0,"ui_name":"touch","enable":0},
		{"vodev":2,"ui_dev":"fb2","mouse":0,"ui_name":"panel","enable":0}
	]
}
*/

static int32_t hi3531a_platform_load_vb_info(cJSON *in_json)
{
	if (!in_json)
	{
		return INTMODULE_HISI_ERR_NULL_PTR;
	}
	cJSON *tmp_json = NULL;

	tmp_json = cJSON_GetObjectItem(in_json, "vb_blksize_16m");
	if (tmp_json)
	{
		hi_platform_param.m_u8vb_16m_cnt = tmp_json->valueint;
	}
	tmp_json = cJSON_GetObjectItem(in_json, "vb_blksize_4m");
	if (tmp_json)
	{
		hi_platform_param.m_u8vb_4m_cnt = tmp_json->valueint;
	}
	tmp_json = cJSON_GetObjectItem(in_json, "vb_blksize_1m");
	if (tmp_json)
	{
		hi_platform_param.m_u8vb_1m_cnt = tmp_json->valueint;
	}
	return INTMODULE_HISI_OK;
}

static int32_t hi3531a_platform_load_vo_dev_info(cJSON *arry_json)
{
	if (!arry_json)
	{
		return INTMODULE_HISI_ERR_NULL_PTR;
	}
	cJSON  *sub_json =NULL, *tmp_json = NULL;
	int32_t arry_size = 0, cycle = 0;
	int vodev_cnt = sizeof(hi_platform_param.m_mpp_vo_dev_params) / sizeof(hi_platform_param.m_mpp_vo_dev_params[0]); 

	if (arry_json)
	{
		arry_size = cJSON_GetArraySize(arry_json);
	}
	if (arry_size > 0)
	{
		for (cycle = 0;cycle < arry_size && cycle < vodev_cnt; cycle++)
		{
			sub_json = cJSON_GetArrayItem(arry_json, cycle);
			if (sub_json)
			{
				tmp_json = cJSON_GetObjectItem(sub_json, "vodev");
				if (tmp_json)
				{
					hi_platform_param.m_mpp_vo_dev_params[cycle].m_devid = tmp_json->valueint;
				}
				tmp_json = cJSON_GetObjectItem(sub_json, "intfsync");
				if (tmp_json)
				{
					if (!strcmp(tmp_json->valuestring, "1080p60"))
					{
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_enintf_sync = HI_MPP_VO_OUTPUT_1080P60;
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_dis_frame_rate = 60;
					}
					else if (!strcmp(tmp_json->valuestring, "1080p50"))
					{
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_enintf_sync = HI_MPP_VO_OUTPUT_1080P50;
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_dis_frame_rate = 50;
					}
					else if (!strcmp(tmp_json->valuestring, "1080p30"))
					{
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_enintf_sync = HI_MPP_VO_OUTPUT_1080P30;
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_dis_frame_rate = 30;
					}
					else if (!strcmp(tmp_json->valuestring, "1080p25"))
					{
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_enintf_sync = HI_MPP_VO_OUTPUT_1080P25;
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_dis_frame_rate = 30;
					}
					else if (!strcmp(tmp_json->valuestring, "1080p24"))
					{
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_enintf_sync = HI_MPP_VO_OUTPUT_1080P24;
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_dis_frame_rate = 30;
					}
					else if (!strcmp(tmp_json->valuestring, "ntsc_960"))
					{
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_enintf_sync = HI_MPP_VO_OUTPUT_960H_NTSC;
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_dis_frame_rate = 25;
					}
					else if (!strcmp(tmp_json->valuestring, "pal_960"))
					{
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_enintf_sync = HI_MPP_VO_OUTPUT_960H_PAL;
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_dis_frame_rate = 25;
					}
					else if (!strcmp(tmp_json->valuestring, "ntsc"))
					{
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_enintf_sync = HI_MPP_VO_OUTPUT_NTSC;
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_dis_frame_rate = 25;
					}
					else if (!strcmp(tmp_json->valuestring, "pal"))
					{
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_enintf_sync = HI_MPP_VO_OUTPUT_PAL;
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_dis_frame_rate = 25;
					}
					else if (!strcmp(tmp_json->valuestring, "4kp30"))
					{
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_enintf_sync = HI_MPP_VO_OUTPUT_3840x2160_30;
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_dis_frame_rate = 30;
					}
					else if (!strcmp(tmp_json->valuestring, "4kp60"))
					{
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_enintf_sync = HI_MPP_VO_OUTPUT_3840x2160_60;
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_dis_frame_rate = 60;
					}
				}
				tmp_json = cJSON_GetObjectItem(sub_json, "intftype1");
				if (tmp_json)
				{
					if (!strcmp(tmp_json->valuestring, "vga"))
					{
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_s32intf_type = HI_MPP_VO_INTF_VGA;
					}
					else if (!strcmp(tmp_json->valuestring, "hdmi"))
					{
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_s32intf_type = HI_MPP_VO_INTF_VGA;
					}
					else if (!strcmp(tmp_json->valuestring, "bt1120"))
					{
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_s32intf_type = HI_MPP_VO_INTF_BT1120;
					}
					else if (!strcmp(tmp_json->valuestring, "cvbs"))
					{
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_s32intf_type = HI_MPP_VO_INTF_CVBS;
					}
				}
				tmp_json = cJSON_GetObjectItem(sub_json, "intftype2");
				if (tmp_json)
				{
					if (!strcmp(tmp_json->valuestring, "vga"))
					{
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_s32intf_type |= HI_MPP_VO_INTF_VGA;
					}
					else if (!strcmp(tmp_json->valuestring, "hdmi"))
					{
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_s32intf_type |= HI_MPP_VO_INTF_VGA;
					}
					else if (!strcmp(tmp_json->valuestring, "bt1120"))
					{
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_s32intf_type |= HI_MPP_VO_INTF_BT1120;
					}
					else if (!strcmp(tmp_json->valuestring, "cvbs"))
					{
						hi_platform_param.m_mpp_vo_dev_params[cycle].m_s32intf_type |= HI_MPP_VO_INTF_CVBS;
					}
				}
				tmp_json = cJSON_GetObjectItem(sub_json, "audio");
				if (tmp_json)
				{
					hi_platform_param.m_mpp_vo_dev_params[cycle].m_audio = tmp_json->valueint;
				}
				tmp_json = cJSON_GetObjectItem(sub_json, "xpos");
				if (tmp_json)
				{
					hi_platform_param.m_mpp_vo_dev_params[cycle].m_dis_xpos = tmp_json->valueint;
				}
				tmp_json = cJSON_GetObjectItem(sub_json, "ypos");
				if (tmp_json)
				{
					hi_platform_param.m_mpp_vo_dev_params[cycle].m_dis_ypos = tmp_json->valueint;
				}
				tmp_json = cJSON_GetObjectItem(sub_json, "width");
				if (tmp_json)
				{
					hi_platform_param.m_mpp_vo_dev_params[cycle].m_dis_width = tmp_json->valueint;
				}
				tmp_json = cJSON_GetObjectItem(sub_json, "height");
				if (tmp_json)
				{
					hi_platform_param.m_mpp_vo_dev_params[cycle].m_dis_height = tmp_json->valueint;
				}
			}
		}
	}
	return INTMODULE_HISI_OK;
}

static int32_t hi3531a_platform_load_ui_info(cJSON *arry_json)
{
	if (!arry_json)
	{
		return INTMODULE_HISI_ERR_NULL_PTR;
	}
	cJSON *sub_json = NULL, *tmp_json = NULL;
	int cycle = 0, arry_size = 0;
	int ui_cnt = sizeof(hi_platform_param.m_ui_params) / sizeof(hi_platform_param.m_ui_params[0]);

	arry_size = cJSON_GetArraySize(arry_json);
	if (!arry_size)
	{
		return INTMODULE_HISI_FALSE;
	}
	for (cycle = 0; cycle < arry_size && cycle < ui_cnt;cycle++)
	{
		sub_json = cJSON_GetArrayItem(arry_json, cycle);
		if (sub_json)
		{
			tmp_json = cJSON_GetObjectItem(sub_json,"vodev");
			if (tmp_json)
			{
				hi_platform_param.m_ui_params[cycle].m_vo_dev_id = tmp_json->valueint;
			}
			tmp_json = cJSON_GetObjectItem(sub_json,"ui_dev");
			if (tmp_json)
			{
				plat_sprintf(hi_platform_param.m_ui_params[cycle].m_fb_name, sizeof(hi_platform_param.m_ui_params[cycle].m_fb_name),"/dev/%s",tmp_json->valuestring);
			}
			tmp_json = cJSON_GetObjectItem(sub_json,"mouse");
			if (tmp_json)
			{
				hi_platform_param.m_ui_params[cycle].m_has_mouse = tmp_json->valueint;
			}
			tmp_json = cJSON_GetObjectItem(sub_json,"ui_name");
			if (tmp_json)
			{
				plat_sprintf(hi_platform_param.m_ui_params[cycle].m_ui_name, sizeof(hi_platform_param.m_ui_params[cycle].m_fb_name),"%s",tmp_json->valuestring);
			}
			tmp_json = cJSON_GetObjectItem(sub_json,"enable");
			if (tmp_json)
			{
				hi_platform_param.m_ui_params[cycle].m_enable = tmp_json->valueint;
			}
		}
	}
	return INTMODULE_HISI_OK;
}

//从配置文件中加载平台参数的接口
int32_t hi3531a_platform_load()
{
	if (0 == hi3531a_platform_ctx.m_inited)
	{
		return INTMODULE_HISI_ERR_SYS_NOTREADY;
	}
	cJSON *root_json = NULL, *arry_json = NULL, *sub_json =NULL;
	int32_t ret_value = INTMODULE_HISI_FALSE;
	char err_info[256] = "";

	if(FILE_FUNC_OK != FILE_FUNC_Get_Json_Form_File(HISI_PLATFORM_FILE, &root_json))
	{
		return INTMODULE_HISI_ERR_PARSE_JSON;
	}
	sub_json = cJSON_GetObjectItem(root_json, "vb_info");
	if (sub_json)
	{
		if(INTMODULE_HISI_OK != (ret_value = hi3531a_platform_load_vb_info(sub_json)))
		{
			gavin_err_get_err_reason(ret_value, err_info, sizeof(err_info));
			log_output(LOG_LEVEL_FILE_SCREEN,"%s->%d:hi3531a_platform_load_vb_info:%s",__FUNCTION__, __LINE__, err_info);
		}
	}

	arry_json = cJSON_GetObjectItem(root_json, "vo_dev_info");
	if (arry_json)
	{
		if(INTMODULE_HISI_OK != (ret_value = hi3531a_platform_load_vo_dev_info(arry_json)))
		{
			gavin_err_get_err_reason(ret_value, err_info, sizeof(err_info));
			log_output(LOG_LEVEL_FILE_SCREEN,"%s->%d:hi3531a_platform_load_vo_dev_info:%s",__FUNCTION__, __LINE__,err_info);
		}
	}
	arry_json = cJSON_GetObjectItem(root_json,"ui_info");
	if (arry_json)
	{
		if(INTMODULE_HISI_OK != (ret_value = hi3531a_platform_load_ui_info(arry_json)))
		{
			gavin_err_get_err_reason(ret_value, err_info, sizeof(err_info));
			log_output(LOG_LEVEL_FILE_SCREEN,"%s->%d:hi3531a_platform_load_ui_info:%s",__FUNCTION__, __LINE__,err_info);
		}
	}
	cJSON_Delete(root_json);
	return INTMODULE_HISI_OK;
}