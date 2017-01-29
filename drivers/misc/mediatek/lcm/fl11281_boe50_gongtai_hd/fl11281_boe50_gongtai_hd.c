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

#if defined(BUILD_LK)
#include <platform/mt_gpio.h>
#include <platform/mt_pmic.h>
#endif

#if !defined(BUILD_LK)
#include <linux/string.h>
#endif
#include "lcm_drv.h"

#if defined(BUILD_LK)
#else

#include <linux/proc_fs.h> //proc file use
#endif



// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  (720)
#define FRAME_HEIGHT (1280)

#define LCM_ID			(0x18211f)
// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))

#define REGFLAG_DELAY             							0XFFE
#define REGFLAG_END_OF_TABLE      							0xFFFF  //100 END OF REGISTERS MARKER

// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd) lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)   			lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)

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

{0xb9, 3,{0xf1,0x12,0x81}},
{0xba, 27,{0x33,0x81,0x05,0xfd,0x0e,0x0e,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x25,0x00,0x91,0x0a,0x00,0x00,0x02,0x0d,0x11,0x00,0x00,0x37}},
{0xbf, 2,{0x02,0x11}},
{0xb8, 1,{0xa4}},
{0xb3, 17,{0x02,0x00,0x06,0x06,0x07,0x0b,0x1e,0x1e,0x00,0x00,0x00,0x03,0xff,0x00,0x00,0x00,0x00}},
{0xc0, 9,{0x73,0x73,0x50,0x50,0x00,0x00,0x08,0x80,0x00}},
{0xbc, 1,{0x46}},
{0xcc, 1,{0x0b}},
{0xb4, 1,{0x00}},
{0xb2, 3,{0xc8,0x02,0x20}},
{0xe3, 10,{0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x14}},
{0xb1, 10,{0x21,0x53,0xe3,0x1e,0x1e,0x33,0x77,0x01,0x9b,0x0c}},
{0xb5, 2,{0x08,0x08}},
{0xb6, 2,{0xa2,0xa8}},
{0xe9, 63,{0x04,0x00,0x09,0x05,0x0c,0x02,0xa1,0x12,0x31,0x23,0x38,0x0b,0x12,0xb1,0x3b,0x08,0x02,0x03,0x00,0x00,0x00,0x00,0x02,0x03,0x00,0x00,0x00,0x00,0x99,0x02,0x46,0x02,0x46,0x88,0x88,0x88,0x80,0x88,0x88,0x99,0x13,0x57,0x13,0x57,0x88,0x88,0x88,0x81,0x88,0x88,0x00,0x00,0x00,0x00,0x00,0x12,0xb1,0x00,0x00,0x00,0xc0,0x00,0x00}},
{0xea, 48,{0x00,0x00,0x00,0x00,0x99,0x31,0x75,0x31,0x17,0x23,0x88,0x88,0x85,0x88,0x88,0x99,0x20,0x64,0x20,0x06,0x88,0x88,0x88,0x84,0x88,0x88,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x00,0x00,0x00,0x00,0x00,0x05,0x14,0x00,0x00}},
{0xe0, 34,{0x00,0x06,0x0c,0x24,0x3c,0x3f,0x3c,0x32,0x05,0x0a,0x0d,0x11,0x12,0x11,0x12,0x10,0x17,0x00,0x06,0x0c,0x24,0x3c,0x3f,0x3c,0x32,0x05,0x0a,0x0d,0x11,0x12,0x11,0x12,0x10,0x17}},

{0x11, 0,{0x00}},
{REGFLAG_DELAY, 400, {}},
  // Display ON
{0x29, 0,{0x00}},
{REGFLAG_DELAY, 30, {}},

  {REGFLAG_END_OF_TABLE, 0x00, {}},
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
	{0x28, 0, {0x00}},
	{REGFLAG_DELAY, 120, {}},

    // Sleep Mode On
	{0x10, 0, {0x00}},
	{REGFLAG_DELAY, 50, {}},
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
  params->dbi.te_mode = LCM_DBI_TE_MODE_DISABLED;
  params->dbi.te_edge_polarity = LCM_POLARITY_RISING;

#if (LCM_DSI_CMD_MODE)
    params->dsi.mode   = CMD_MODE;
#else
    params->dsi.mode   = BURST_VDO_MODE;
#endif
  //params->dsi.mode = SYNC_EVENT_VDO_MODE;//BURST_VDO_MODE;


  // DSI
  /* Command mode setting */
  params->dsi.LANE_NUM = LCM_FOUR_LANE;
  //The following defined the fomat for data coming from LCD engine.
  params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
  params->dsi.data_format.trans_seq = LCM_DSI_TRANS_SEQ_MSB_FIRST;
  params->dsi.data_format.padding = LCM_DSI_PADDING_ON_LSB;
  params->dsi.data_format.format = LCM_DSI_FORMAT_RGB888;
  // Highly depends on LCD driver capability.
    params->dsi.packet_size=256;

  params->dsi.intermediat_buffer_num = 0;	//because DSI/DPI HW design change, this parameters should be 0 when video mode in MT658X; or memory leakage


  // Video mode setting
  params->dsi.PS = LCM_PACKED_PS_24BIT_RGB888;
  params->dsi.word_count = 720 * 3;

  params->dsi.vertical_sync_active				= 4;
  params->dsi.vertical_backporch					= 10;
    params->dsi.vertical_frontporch					= 10; // 1  12
  params->dsi.vertical_active_line = FRAME_HEIGHT;

  params->dsi.horizontal_sync_active = 4;
    params->dsi.horizontal_backporch				= 30;
    params->dsi.horizontal_frontporch				= 30;
  params->dsi.horizontal_active_pixel				= FRAME_WIDTH;
  /***********************/
    params->dsi.PLL_CLOCK = 245;
#if 0
    params->dsi.ssc_disable = 1;  // ssc disable control (1: disable, 0: enable, default: 0)
	params->dsi.cont_clock=0;
  params->dsi.esd_check_enable = 0;
  params->dsi.customization_esd_check_enable = 0;
  params->dsi.lcm_esd_check_table[0].cmd          = 0x0a;
  params->dsi.lcm_esd_check_table[0].count        = 1;
  params->dsi.lcm_esd_check_table[0].para_list[0] = 0x9c;
  params->dsi.lcm_esd_check_table[1].cmd          = 0x09;
  params->dsi.lcm_esd_check_table[1].count        = 1;
  params->dsi.lcm_esd_check_table[1].para_list[0] = 0x80;
#endif
}

static void lcm_init(void)
{
  SET_RESET_PIN(1);
	MDELAY(10); 
  SET_RESET_PIN(0);
  MDELAY(10);//1
  SET_RESET_PIN(1);
  MDELAY(120);//60

  push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
}

static void lcm_suspend(void)
{
	push_table(lcm_sleep_mode_in_setting, sizeof(lcm_sleep_mode_in_setting) / sizeof(struct LCM_setting_table), 1);
  SET_RESET_PIN(0);
  MDELAY(10);

}

static unsigned int lcm_compare_id(void);
static void lcm_resume(void)
{
  lcm_init();
  //lcm_compare_id();
}

static unsigned int lcm_compare_id(void)
{
    unsigned int id = 0;
    unsigned char buffer[3];
    unsigned int data_array[16];


	SET_RESET_PIN(1);
	MDELAY(10);
	SET_RESET_PIN(0);
	MDELAY(50);
	SET_RESET_PIN(1);
	MDELAY(120);
  
	// Set Maximum return byte = 1
    data_array[0] = 0x00033700;// read id return two byte,version and id
    dsi_set_cmdq(data_array, 1, 1);
    //MDELAY(10);


    read_reg_v2(0x04, buffer, 3);
    id = buffer[0]; //we only need ID
    id<<=8;
    id|= buffer[1]; //we test buffer 1
    id<<=8;
    id|= buffer[2]; //we test buffer 1
#if defined(BUILD_LK)
    printf("[fl10801->lcm_esd_check] %s buffer[0] = %x; buffer[1]= %x; buffer[2]= %x;\n", __func__,buffer[0],buffer[1],buffer[2]);
#elif defined(BUILD_UBOOT)
    printf("[fl10801->lcm_esd_check] %s buffer[0] = %x; buffer[1]= %x; buffer[2]= %x;\n", __func__,buffer[0],buffer[1],buffer[2]);
#else
    printk("[fl10801->lcm_esd_check] %s buffer[0] = %x; buffer[1]= %x; buffer[2]= %x;\n", __func__,buffer[0],buffer[1],buffer[2]);
#endif

#ifdef BUILD_LK
    printf("[lcm_compare_id] fl10801_ic:lcd id 0x%x\n",id);
#else
    printk("[lcm_compare_id] fl10801_ic:lcd id 0x%x\n",id);
#endif

    return (0x18211f == id)? 1:0;
}

// ---------------------------------------------------------------------------
//  Get LCM Driver Hooks
// ---------------------------------------------------------------------------
LCM_DRIVER fl11281_boe50_gongtai_hd_lcm_drv =
{
  .name			= "fl11281_boe50_gongtai_hd",
  .set_util_funcs = lcm_set_util_funcs,
  .get_params     = lcm_get_params,
  .init           = lcm_init,
  .suspend        = lcm_suspend,
  .resume         = lcm_resume,
  .compare_id    = lcm_compare_id,
    .init_power     = lcm_init_power,
    .resume_power   = lcm_resume_power,
    .suspend_power  = lcm_suspend_power,
};
