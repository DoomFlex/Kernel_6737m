/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/*****************************************************************************
 *  Copyright Statement:
 *  --------------------
 *  This software is protected by Copyright and the information contained
 *  herein is confidential. The software may not be copied and the information
 *  contained herein may not be used or disclosed except with the written
 *  permission of MediaTek Inc. (C) 2008
 *
 *  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 *  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
 *  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 *  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 *  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 *  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
 *  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
 *  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
 *  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 *  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 *  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
 *  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
 *  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
 *  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
 *  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
 *  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
 *
 *****************************************************************************/

#ifdef BUILD_LK
#include <platform/mt_gpio.h>
#include <platform/mt_pmic.h>
#else
#include <mt-plat/mt_gpio.h>
//#include <mt-plat/upmu_common.h>
#include <linux/string.h>
#include <linux/kernel.h>
#endif
#include "lcm_drv.h"

#if defined(BUILD_LK)
#define LCM_DEBUG  printf
#define LCM_FUNC_TRACE() printf("huyl [uboot] %s\n",__func__)
#else
#define LCM_DEBUG  printk
#define LCM_FUNC_TRACE() printk("huyl [kernel] %s\n",__func__)
#endif
// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  (720)
#define FRAME_HEIGHT (1280)

#define LCM_OTM1285_ID			(0x1285)

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

static unsigned int lcm_esd_test = FALSE;      ///only for ESD test

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))

#define REGFLAG_DELAY             							0XFE
#define REGFLAG_END_OF_TABLE      							0x100   // END OF REGISTERS MARKER

// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	        lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)											lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)   				lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)


struct LCM_setting_table {
	unsigned cmd;
	unsigned char count;
	unsigned char para_list[64];
};

static void lcm_init_power(void)
{

}

static void lcm_suspend_power(void)
{

}

static void lcm_resume_power(void)
{

}

static struct LCM_setting_table lcm_initialization_setting[] = {

	{0x00,1,{0x00}},
	{0xff,3,{0x12,0x85,0x01}},
	{0x00,1,{0x80}},
	{0xff,2,{0x12,0x85}},

	{0x00,1,{0x91}},                
	{0xB3,2,{0x0C,0x10}},//0C 4Lane,08 3Lane 

	{0x00,1,{0x80}},
	{0xc0,2,{0x00,0x7F}},

	{0x00,1,{0x82}},
	{0xc0,3,{0x00,0x0c,0x08}},

	{0x00,1,{0x90}},
	{0xc1,1,{0x55}},

	{0x00,1,{0xB3}},    
	{0xc0,1,{0x33}}, 

	{0x00,1,{0x80}},
	{0xc1,4,{0x1D,0x1D,0x1D,0x1D}},

	{0x00,1,{0x90}},
	{0xc2,10,{0x86,0x20,0x00,0x0F,0x00,0x87,0x20,0x00,0x0F,0x00}},

	{0x00,1,{0xec}},
	{0xc2,1,{0x00}},

	{0x00,1,{0x80}},
	{0xc2,4,{0x82,0x01,0x08,0x08}},

	{0x00,1,{0xa0}},
	{0xc0,7,{0x00,0x0f,0x00,0x00,0x0a,0x1A,0x00}},

	{0x00,1,{0xfb}},
	{0xc2,1,{0x80}},

	{0x00,1,{0x80}},
	{0xcc,12,{0x03,0x04,0x01,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b}},

	{0x00,1,{0xb0}},
	{0xcc,12,{0x04,0x03,0x01,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b}},

	{0x00,1,{0x80}},
	{0xcd,15,{0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x15,0x0B,0x0b,0x12,0x13,0x14,0x0b,0x0b,0x0b}},

	{0x00,1,{0xc0}},
	{0xcb,15,{0x05,0x05,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},

	{0x00,1,{0xd0}},
	{0xcb,15,{0x00,0x00,0x00,0x0A,0x05,0x00,0x05,0x05,0x05,0x00,0x00,0x00,0x00,0x00,0x00}},

	{0x00,1,{0xe0}},
	{0xcc,4,{0x00,0x00,0x00,0x00}},

	{0x00,1,{0xd0}},
	{0xcd,15,{0x01,0x02,0x04,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f}},

	{0x00,1,{0xe0}},
	{0xcd,12,{0x10,0x11,0x12,0x13,0x03,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b}},

	{0x00,1,{0xa0}},
	{0xcd,15,{0x01,0x02,0x04,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f}},

	{0x00,1,{0xb0}},
	{0xcd,12,{0x10,0x11,0x12,0x13,0x03,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b}},

	//-------------power,setting--------------------------------------------------------------------
	{0x00,1,{0x00}},
	{0xD8,2,{0x26,0x26}},

	{0x00,1,{0x00}},
	{0xD9,1,{0x80}},

	{0x00,1,{0x90}},
	{0xC5,6,{0xB2,0xD6,0xA0,0x0F,0xA0,0x14}},

	{0x00,1,{0x96}},
	{0xc5,4,{0xa0,0x0d,0xaa,0x0c}},
	//----------------------------------------------------------------------------------------------------------------------

	////////////////power IC///////////////////
	{0x00,1,{0xC2}},
	{0xc5,1,{0x08}},

	{0x00,1,{0xA8}},
	{0xc4,1,{0x11}},

	/////////////////////////////////////////

	//-------------------------------,tunig,default,---------------------------------------------------
	{0x00,1,{0xc1}},
	{0xc5,1,{0x66}},//33  //VDD_18/LVDSVD

	{0x00,1,{0xa3}},
	{0xc5,1,{0x0f}},

	{0x00,1,{0xa5}},
	{0xc5,5,{0x0f,0xa0,0x0d,0xaa,0x0c}},

	{0x00,1,{0x93}},
	{0xc5,1,{0x0f}},
	{0x00,1,{0x95}},
	{0xc5,5,{0x0f,0xa0,0x0d,0xaa,0x0c}},


	{0x00,1,{0x90}},
	{0xf5,14,{0x03,0x15,0x09,0x15,0x07,0x15,0x0c,0x15,0x0a,0x15,0x09,0x15,0x0a,0x15}},

	{0x00,1,{0xa0}},
	{0xf5,14,{0x12,0x11,0x03,0x15,0x09,0x15,0x11,0x15,0x08,0x15,0x07,0x15,0x09,0x15}},

	{0x00,1,{0xc0}},
	{0xf5,14,{0x0e,0x15,0x0e,0x15,0x00,0x15,0x00,0x15,0x0e,0x15,0x14,0x11,0x00,0x15}},

	{0x00,1,{0xd0}},
	{0xf5,15,{0x07,0x15,0x0a,0x15,0x10,0x11,0x00,0x10,0x90,0x90,0x90,0x02,0x90,0x00,0x00}},

	{0x00,1,{0x81}},
	{0xc4,1,{0x24}},

	{0x00,1,{0x92}},
	{0xE9,1,{0x10}},

	{0x00,1,{0x9D}},
	{0xc5,1,{0xAA}},

	{0x00,1,{0xC8}},
	{0xF5,1,{0x2E}},

	{0x00,1,{0xB4}},
	{0xC0,1,{0x40}},

	//White,gamma

	{0x00,1,{0x00}},
	{0xe1,24,{0x00,0x1e,0x27,0x32,0x3b,0x43,0x4e,0x5f,0x68,0x7a,0x86,0x90,0x68,0x62,0x5d,0x4e,0x3d,0x2c,0x21,0x1a,0x11,0x07,0x02,0x00}},
	{0x00,1,{0x00}},
	{0xe2,24,{0x00,0x1e,0x27,0x32,0x3b,0x43,0x4e,0x5f,0x68,0x7a,0x86,0x90,0x68,0x62,0x5d,0x4e,0x3d,0x2c,0x21,0x1a,0x11,0x07,0x02,0x00}},
	{0x00,1,{0x00}},
	{0xe3,24,{0x00,0x1e,0x27,0x32,0x3b,0x43,0x4e,0x5f,0x68,0x7a,0x86,0x90,0x68,0x62,0x5d,0x4e,0x3d,0x2c,0x21,0x1a,0x11,0x07,0x02,0x00}},
	{0x00,1,{0x00}},
	{0xe4,24,{0x00,0x1e,0x27,0x32,0x3b,0x43,0x4e,0x5f,0x68,0x7a,0x86,0x90,0x68,0x62,0x5d,0x4e,0x3d,0x2c,0x21,0x1a,0x11,0x07,0x02,0x00}},
	{0x00,1,{0x00}},
	{0xe5,24,{0x00,0x1e,0x27,0x32,0x3b,0x43,0x4e,0x5f,0x68,0x7a,0x86,0x90,0x68,0x62,0x5d,0x4e,0x3d,0x2c,0x21,0x1a,0x11,0x07,0x02,0x00}},
	{0x00,1,{0x00}},
	{0xe6,24,{0x00,0x1e,0x27,0x32,0x3b,0x43,0x4e,0x5f,0x68,0x7a,0x86,0x90,0x68,0x62,0x5d,0x4e,0x3d,0x2c,0x21,0x1a,0x11,0x07,0x02,0x00}},

	//---------------------------------------------------------------------------------------------------------------------------

	//{0x00,1,{0x00}},
	//{0xff,3,{0x00,0x00,0x00}},

	{0x35,1,{0x00}},//TE on  
	{0x11,0,{0x00}},
	{REGFLAG_DELAY, 120, {}}, 
	{0x29,0,{0x00}},
	{REGFLAG_DELAY, 10, {}},

	{REGFLAG_END_OF_TABLE, 0x00, {}}
};
static struct LCM_setting_table lcm_sleep_out_setting[] = {
	// Sleep Out
	{0x11, 0, {0x00}},
	{REGFLAG_DELAY, 120, {}},

	// Display ON
	{0x29, 0, {0x00}},
	{REGFLAG_DELAY, 10, {}},

	{REGFLAG_END_OF_TABLE, 0x00, {}}
};


static struct LCM_setting_table lcm_sleep_mode_in_setting[] = {
	// Display off sequence
	{0x22, 0, {0x00}},
	{0x28, 0, {0x00}},
	{REGFLAG_DELAY, 20, {}},

	// Sleep Mode On
	{0x10, 0, {0x00}},
	{REGFLAG_DELAY, 120, {}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};
static struct LCM_setting_table lcm_compare_id_setting[] = {
	// Display off sequence
	{0xF0,	5,	{0x55, 0xaa, 0x52,0x08,0x00}},
	{REGFLAG_DELAY, 10, {}},

	{REGFLAG_END_OF_TABLE, 0x00, {}}
};


static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
	unsigned int i;

	for(i = 0; i < count; i++) {

		unsigned cmd;
		cmd = table[i].cmd;

		switch (cmd) {

		case REGFLAG_DELAY :
			MDELAY(table[i].count);
			break;

		case REGFLAG_END_OF_TABLE :
			break;

		default:
			dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
			//MDELAY(2);
		}
	}

}

// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
	memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}

static void lcm_get_params(LCM_PARAMS *params)
{

	memset(params, 0, sizeof(LCM_PARAMS));

	params->type = LCM_TYPE_DSI;

	params->width = FRAME_WIDTH;
	params->height = FRAME_HEIGHT;

	// enable tearing-free
	params->dbi.te_mode = LCM_DBI_TE_MODE_VSYNC_ONLY;
	params->dbi.te_edge_polarity = LCM_POLARITY_RISING;

	params->dsi.mode   = SYNC_PULSE_VDO_MODE; //SYNC_PULSE_VDO_MODE;//BURST_VDO_MODE;

	// DSI
	/* Command mode setting */
	params->dsi.LANE_NUM = LCM_FOUR_LANE;
	//The following defined the fomat for data coming from LCD engine.
	params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
	params->dsi.data_format.trans_seq = LCM_DSI_TRANS_SEQ_MSB_FIRST;
	params->dsi.data_format.padding = LCM_DSI_PADDING_ON_LSB;
	params->dsi.data_format.format = LCM_DSI_FORMAT_RGB888;

	params->dsi.intermediat_buffer_num = 0;	//because DSI/DPI HW design change, this parameters should be 0 when video mode in MT658X; or memory leakage

	params->dsi.PS = LCM_PACKED_PS_24BIT_RGB888;
	params->dsi.word_count = 720 * 3;

	params->dsi.vertical_sync_active				= 4;// 3    2
	params->dsi.vertical_backporch					= 20;// 20   1
	params->dsi.vertical_frontporch					= 20; // 1  12
	params->dsi.vertical_active_line				= FRAME_HEIGHT;

	params->dsi.horizontal_sync_active				= 50;// 50  2
	params->dsi.horizontal_backporch				= 50 ;
	params->dsi.horizontal_frontporch				= 50 ;
	params->dsi.horizontal_active_pixel				= FRAME_WIDTH;

	// Bit rate calculation
	//1 Every lane speed
	//	params->dsi.pll_div1 = 0;	// div1=0,1,2,3;div1_real=1,2,4,4 ----0: 546Mbps  1:273Mbps
	//	params->dsi.pll_div2 = 1;	// div2=0,1,2,3;div1_real=1,2,4,4
	//	params->dsi.fbk_div = 14;	//12;    // fref=26MHz, fvco=fref*(fbk_div+1)*2/(div1_real*div2_real)
	params->dsi.PLL_CLOCK =260;
	params->dsi.ssc_disable = 1;  // ssc disable control (1: disable, 0: enable, default: 0)
	params->dsi.esd_check_enable            = 1;
	params->dsi.customization_esd_check_enable  = 0;
	params->dsi.lcm_esd_check_table[0].cmd          = 0x0a;
	params->dsi.lcm_esd_check_table[0].count        = 1;
	params->dsi.lcm_esd_check_table[0].para_list[0] = 0x9c;





}

static void lcm_init(void)
{

	SET_RESET_PIN(1);
	MDELAY(10);
	SET_RESET_PIN(0);
	MDELAY(10);
	SET_RESET_PIN(1);
	MDELAY(50);

	push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
}

static void lcm_suspend(void)
{
	push_table(lcm_sleep_mode_in_setting, sizeof(lcm_sleep_mode_in_setting) / sizeof(struct LCM_setting_table), 1);
	SET_RESET_PIN(0);
	MDELAY(10);
	SET_RESET_PIN(1);
	MDELAY(10);
}

//static unsigned int VcomH = 0x40;
static unsigned int lcm_compare_id(void);
static void lcm_resume(void)
{
	// unsigned int data_array[16];
	lcm_init();
	//lcm_compare_id();
	//	push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
}

static unsigned int lcm_compare_id(void)
{
	unsigned int id0, id1, id2, id3, id4;
	unsigned char buffer[5];
	unsigned int array[5];

	SET_RESET_PIN(1);
	MDELAY(10);
	SET_RESET_PIN(0);
	MDELAY(10);
	SET_RESET_PIN(1);
	MDELAY(50);

	// Set Maximum return byte = 1
	array[0] = 0x00053700;
	dsi_set_cmdq(array, 1, 1);

	read_reg_v2(0xA1, buffer, 5);
	id0 = buffer[0];
	id1 = buffer[1];
	id2 = buffer[2];
	id3 = buffer[3];
	id4 = buffer[4];

#if defined(BUILD_LK)
	printf("%s, Module ID = {%x, %x, %x, %x, %x} \n", __func__, id0,
			id1, id2, id3, id4);
#else
	printk("%s, Module ID = {%x, %x, %x, %x,%x} \n", __func__, id0,
			id1, id2, id3, id4);
#endif

	return (LCM_OTM1285_ID == ((id2 << 8) | id3)) ? 1 : 0;
}


static unsigned int lcm_esd_check(void)
{
#ifndef BUILD_LK
	char  buffer[3];
	int   array[4];

	if(lcm_esd_test)
	{
		lcm_esd_test = FALSE;
		return TRUE;
	}

	array[0] = 0x00013700;
	dsi_set_cmdq(array, 1, 1);

	read_reg_v2(0x36, buffer, 1);
	if(buffer[0]==0x90)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
#endif

}

static unsigned int lcm_esd_recover(void)
{
	lcm_init();
	lcm_resume();

	return TRUE;
}

LCM_DRIVER otm1285a_boe55_ykl_hd_lcm_drv =
{
	.name			= "otm1285a_boe55_ykl_hd",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
	.compare_id     = lcm_compare_id,
	.init_power     = lcm_init_power,
	.resume_power   = lcm_resume_power,
	.suspend_power  = lcm_suspend_power,
	//.esd_check = lcm_esd_check,
	//.esd_recover = lcm_esd_recover,
};
