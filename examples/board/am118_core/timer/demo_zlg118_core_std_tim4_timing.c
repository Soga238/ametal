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
 * \brief ADTIM4 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 5Hz ��Ƶ����˸��(����������10Hz��led��ת����Ϊ10/2=5Hz)
 *
 *
 * \par Դ����
 * \snippet demo_zlg118_std_tim4_timing.c src_zlg118_std_tim4_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-09  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg118_std_tim4_timing
 * \copydoc demo_zlg118_std_tim4_timing.c
 */

/** [src_zlg118_std_tim4_timing] */

#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "am_zlg118_inst_init.h"
#include "demo_am118_core_entries.h"

/**
 * \brief �������
 */
void demo_zlg118_core_std_tim4_timing_entry (void)
{
    AM_DBG_INFO("demo am118_core std tim4 timing!\r\n");

    demo_std_timer_timing_entry(am_zlg118_tim4_timing_inst_init(), 0);
}
/** [src_zlg118_std_tim4_timing] */

/* end of file */