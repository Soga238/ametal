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
 * \brief ���״����� AS7262 (UARTģʽ) ���̣�ͨ����׼�ӿ�ʵ��(ͨ����ѯ��ʽ��ȡ����)
 *
 * - ʵ������
 *   1. ÿ��һ�룬ͨ�����ڴ�ӡ����ͨ�� (V��B��G��Y��O��R) ADֵ
 *
 * \par Դ����
 * \snippet demo_zlg237_core_sensor_as7262_uart.c src_zlg237_core_sensor_as7262_uart
 *
 * \internal
 * \par Modification history
 * - 1.00 20-04-26  fzb, first implementation
 * \endinternal
 */

#include "am_sensor.h"
#include "am_hwconf_sensor_as7262_uart.h"
#include "demo_std_entries.h"
#include "demo_am237_core_entries.h"

/**
 * \brief �������������
 */
void demo_zlg237_core_sensor_as7262_uart_entry (void)
{
    am_sensor_handle_t handle = am_sensor_as7262_uart_inst_init();

    demo_std_as7262_entry(handle);
}


/* end of file */