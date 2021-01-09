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
 * \brief 环境光传感器 TSL2540 例程，通过标准接口实现(通过查询方式获取数据)
 *
 * - 实验现象：
 *   1. 每过一秒，通过串口打印可见光和红外光的值
 *
 * \par 源代码
 * \snippet demo_stm32f103rbt6_core_sensor_tsl2540.c src_stm32f103rbt6_core_sensor_tsl2540
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation
 * \endinternal
 */

#include "am_sensor.h"
#include "am_hwconf_sensor_tsl2540.h"
#include "demo_std_entries.h"
#include "demo_stm32f103rbt6_core_entries.h"

/**
 * \brief 传感器例程入口
 */
void demo_stm32f103rbt6_core_sensor_tsl2540_entry (void)
{
    am_sensor_handle_t handle = am_sensor_tsl2540_inst_init();

    demo_std_tsl2540_entry(handle);
}


/* end of file */
