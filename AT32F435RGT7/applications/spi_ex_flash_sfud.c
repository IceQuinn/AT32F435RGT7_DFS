/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-11     mutou       the first version
 */
#include "spi_ex_flash_sfud.h"


#include <rtdevice.h>
#include "spi_flash_sfud.h"
#include "drv_spi.h"

#define W25Q64_SPI_NAME             "spi2"
#define SPI_W25Q64_DEVICE_NAME      "spi20"
#define W25Q64_NSS_GPIO_PORT        GPIOB
#define W25Q64_NSS_GPIO_PIN         GPIO_PINS_12

/* 将W25Q64挂载在spi2上并配置 */
int32_t ex_flash_spi_init(void)
{
    /* 把spi20挂到spi2上 */
    if(RT_EOK != rt_hw_spi_device_attach(W25Q64_SPI_NAME, SPI_W25Q64_DEVICE_NAME, W25Q64_NSS_GPIO_PORT, W25Q64_NSS_GPIO_PIN))
    {
        rt_kprintf("spi2 bus attach W25Q64 device Failed !\n");
        return -RT_ERROR;
    }

    /* 在通用串行驱动中查找W25Q64设备 */
    if(RT_NULL == rt_sfud_flash_probe("ZD25Q64", SPI_W25Q64_DEVICE_NAME))
    {
        rt_kprintf("dev W25Q64 find error !\n");
        return -RT_ERROR;
    }
    rt_kprintf("ex_flash spi & sfdp init success !\n");
    return RT_EOK;
}
