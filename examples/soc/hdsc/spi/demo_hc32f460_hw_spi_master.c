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
 * \brief SPI 主机例程，通过 HW 层接口实现
 *
 * - 操作步骤：
 *   1. 将 SPI 的 MOSI 引脚和 MISO 引脚用线相连，模拟从机设备，回环测试。
 *
 * - 实验现象：
 *   1. 主机通过 MISO 发送数据，发出的数据从 MOSI 读回；
 *   2. 调试串口打印测试结果。
 *
 * \par 源代码
 * \snippet demo_hc32f460_hw_spi_master.c src_hc32f460_hw_spi_master
 *
 * \internal
 * \par History
 * - 1.00 20-03-27  cds, first implementation
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hc32f460_hw_spi_master
 * \copydoc demo_hc32f460_hw_spi_master.c
 */
 
/** [src_hc32f460_hw_spi_master] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "hw/amhw_hc32f460_spi.h"


#define SPI_CFG_MODE_0      0           /**< \brief 模式0 */
#define SPI_CFG_MODE_1      1           /**< \brief 模式1 */
#define SPI_CFG_MODE_2      2           /**< \brief 模式2 */
#define SPI_CFG_MODE_3      3           /**< \brief 模式3 */

/** @} */

/** 
 * \brief SPI传输结构体
 */
typedef struct spi_transfer {
    const void  *p_txbuf;           /**< \brief 指向发送数据缓存的指针 */
    void        *p_rxbuf;           /**< \brief 指向接收数据缓存的指针 */
    uint32_t     nbytes;            /**< \brief 数据长度 */
    uint32_t     flags;             /**< \brief SPI传输控制标志位 */
} spi_transfer_t;

spi_transfer_t g_spi_transfer;      /* 定义一个SPI传输结构体实例 */



/**
 * \brief SPI回环传输测试
 */
void spi_loop_trans (amhw_hc32f460_spi_t *p_hw_spi,
                     spi_transfer_t      *p_trans,
                     int32_t              cs_pin,
                     uint32_t             cs_mdelay)
{
    uint32_t pos = 0;

    /* 片选引脚输出低电平 */
    am_gpio_set(cs_pin, AM_GPIO_LEVEL_LOW);

    /* CS选通后，至少需要等待100ms，等待从机(单片机)完成相关配置才能正确传输数据，否则部分数据会丢失、错乱*/
    /* 假如是其他从机单位，响应较快，可考虑取消此处延时*/
    if (cs_mdelay != 0) {
        am_mdelay(cs_mdelay);
    }

    while (pos < p_trans->nbytes) {

        /* 等待可以发送 */
        while(amhw_hc32f460_spi_flag_check (p_hw_spi,
                                            AMHW_HC32F460_SPI_STATUS_TXBUFFER_EMPTY) ==
                                            AM_FALSE);

            amhw_hc32f460_spi_tx_data8_put(p_hw_spi,
                                           *((uint8_t*)(p_trans->p_txbuf) + pos));

        /* 等待可以接收 */
        while (amhw_hc32f460_spi_flag_check (p_hw_spi,
                                             AMHW_HC32F460_SPI_STATUS_RXBUFFER_FULL) ==
                                             AM_FALSE);

        *(uint8_t*)((uint8_t*)p_trans->p_rxbuf + pos) =
             amhw_hc32f460_spi_rx_data8_get(p_hw_spi);
        pos += 1;
    }

    /* 片选引脚输出高电平 */
    am_gpio_set(cs_pin, AM_GPIO_LEVEL_HIGH);
}

/**
 * \brief 例程入口
 */
void demo_hc32f460_hw_spi_master_entry (void    *p_hw_spi,
                                        int32_t  cs_pin)
{
    uint8_t              i;
    uint8_t              spi_send_buf[40];
    uint8_t              spi_recv_buf[40];
    const uint32_t       length     = 40;
    am_bool_t            error_ocur = AM_FALSE;
    spi_transfer_t      *p_trans    = &g_spi_transfer;
    amhw_hc32f460_spi_t *p_spi   = (amhw_hc32f460_spi_t *)p_hw_spi;

    p_trans->p_txbuf = spi_send_buf;
    p_trans->p_rxbuf = spi_recv_buf;
    p_trans->nbytes  = length;

    /* 配置为主机模式 */
    amhw_hc32f460_spi_mode_sel(p_spi, AMHW_HC32F460_SPI_MODE_MASTER);

    /* 配置SPI通信模式 */
    amhw_hc32f460_spi_trans_mode_sel(p_hw_spi, AMHW_HC32F460_SPI_TRANS_MODE_FULL_DUPLEX);

    /* 配置SPI工作模式（三线/四线） */
    amhw_hc32f460_spi_work_mode_sel(p_hw_spi, AMHW_HC32F460_SPI_WORK_MODE_4LINE);

    /* 配置SPI模式（时钟相位和极性） */
    amhw_hc32f460_spi_clk_mode_set(p_spi, 0x3 & SPI_CFG_MODE_1);

    /* 帧格式设置，先发送MSB */
    amhw_hc32f460_spi_first_bit_position_set(p_hw_spi, AMHW_HC32F460_SPI_MSB_FIRST);

    /* 设置SPI速率 */
    amhw_hc32f460_spi_clk_div_set(p_spi, AMHW_HC32F460_SPI_CLK_DIV_16);

    /* 数据长度为8 */
    amhw_hc32f460_spi_data_length_set(p_hw_spi,
                                      AMHW_HC32F460_SPI_DATA_LENGTH_BIT8);

    /* SPI使能 */
    amhw_hc32f460_spi_enable(p_spi, AM_TRUE);

    /* 构造数据 */
    for (i = 0; i < length; i++) {
        spi_send_buf[i] = i;
    }

    /* 数据传输 */
    spi_loop_trans(p_spi, p_trans, cs_pin, 100);

    /* 数据检验 */
    for (i = 0; i < length; i++) {
        if (spi_recv_buf[i] != spi_send_buf[i]) {
            error_ocur = AM_TRUE;
            break;
        }
    }

    if (!error_ocur) {
        am_kprintf("trans done!\n");
    } else {
        am_kprintf("trans error!\n");
    }

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_hc32f460_hw_spi_master] */

/* end of file */
