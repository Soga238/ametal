/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/
/**
 * \file
 * \brief 停止模式例程，通过驱动层接口实现
 *
 * - 实现现象
 *   1. MCU 进入停止模式时， J-Link 调试断开；
 *   2. 按下 KEY/RES 键唤醒 MCU，串口输出 wake_up，程序继续运行。
 *
 * \par 源代码
 * \snippet demo_hk32f103rbt6_drv_stopmode_wake_up.c src_hk32f103rbt6_drv_stopmode_wake_up
 *
 * \internal
 * \par Modification History
 * - 1.00 19-07-25  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hk32f103rbt6_drv_stopmode_wake_up
 * \copydoc demo_hk32f103rbt6_drv_stopmode_wake_up.c
 */

/** [src_hk32f103rbt6_drv_stopmode_wake_up] */
#include "ametal.h"
#include "am_board.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "hk32f103rbt6_pin.h"
#include "am_hk32f103rbt6_pwr.h"
#include "am_hk32f103rbt6_inst_init.h"
#include "demo_hk32f103rbt6_core_entries.h"

/**
 * \brief 引脚中断服务函数
 */
static void gpio_isr (void *p_arg)
{
    ;
}

/**
 * \brief 例程入口
 */
void demo_hk32f103rbt6_drv_stopmode_wake_up_entry (void)
{
    uint32_t i = 0;

    AM_DBG_INFO("low power test!\r\n");

    am_hk32f103rbt6_pwr_inst_init();

    /* 唤醒配置 */
    am_hk32f103rbt6_wake_up_cfg(AM_HK32F103RBT6_PWR_MODE_STOP, gpio_isr, (void *)0);

    for (i = 0; i < 5; i++) {
        am_mdelay(1000);
    }

    /* 进入停机模式 */
    am_hk32f103rbt6_pwr_mode_into(AM_HK32F103RBT6_PWR_MODE_STOP);

    AM_DBG_INFO("wake_up!\r\n");

    while (1) {

        /* 指示灯指示时钟是否恢复正常 */
        am_led_on(LED0);
        am_mdelay(500);
        am_led_off(LED0);
        am_mdelay(500);

    }
}
/** [src_hk32f103rbt6_drv_stopmode_wake_up] */

/* end of file */
