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
 * \brief MM32L373 CRC 用户配置文件
 * \sa am_hwconf_mm32l373_crc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-30  fra, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_mm32l373.h"
#include "am_clk.h"
#include "am_mm32_crc.h"

/**
 * \addtogroup am_if_src_hwconf_mm32l373_crc
 * \copydoc am_hwconf_mm32l373_crc.c
 * @{
 */

/** \brief CRC平台初始化 */
void __mm32l373_crc_plfm_init (void)
{

    /* 使能CRC时钟 */
    am_clk_enable(CLK_CRC);
}

/** \brief 解除CRC平台初始化 */
void __mm32l373_crc_plfm_deinit (void)
{
    am_clk_disable(CLK_CRC);
}

/** \brief CRC 设备信息 */
static const am_mm32_crc_devinfo_t __g_crc_devinfo = {
     MM32L373_CRC_BASE,               /**< \brief CRC寄存器块基址 */
    __mm32l373_crc_plfm_init,         /**< \brief 平台初始化 */
    __mm32l373_crc_plfm_deinit        /**< \brief 平台去初始化 */
};

/** \brief CRC设备定义 */
static am_mm32_crc_dev_t __g_crc_dev;

/** \brief CRC 实例初始化，获得CRC标准服务句柄 */
am_crc_handle_t am_mm32l373_crc_inst_init (void)
{
    return am_mm32_crc_init(&__g_crc_dev, &__g_crc_devinfo);
}

/** \brief CRC 实例解初始化 */
void am_mm32l373_crc_inst_deinit (am_crc_handle_t handle)
{
    am_mm32_crc_deinit(handle);
}

/**
 * @}
 */

/* end of file */
