/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-13     mutou       the first version
 */
#ifndef APPLICATIONS_CFG_CTU_CFG_H_
#define APPLICATIONS_CFG_CTU_CFG_H_

#include <stdint.h>

struct CTU_CFG_Str
{
    /* 通信参数 */
    int32_t  uart_protocol[3];           //通信协议  0=ModBus协议，1=DLT645协议
    int32_t  uart_baud[3];               //串口波特率
    int32_t  uart_check[3];              //串口校验位格式
    int32_t  modbus_slave_addr;                     //modbus从机地址
    int32_t  dlt645_bcd_addr[6];                     //dlt645通信地址
    /* 基本参数 */
    int32_t  show_ctrl;                             //显示配置 0：显示二次值，1：显示一次值
    /* IO参数 */
    int32_t  DI_delay[2];                      //DI防抖时间
    int32_t  DO_delay[4];                      //DO保持时间
    /* 显示参数 */
    int32_t  backlight_time;                        //背光时间
    int32_t  backlight_Rate;                        //背光亮度
    int32_t  constrast;                             //对比度
    /* 装置维护 */
    int32_t  user_password;                         //用户密码
    int32_t  admin_password;                        //厂商密码

    /* 无线配置 */
    int32_t  wl_channel;                            //无线信道
    int32_t  wl_addr;                               //无线地址

    int32_t  yk_do_delay[4];                   // 手动开出保持时间
};


void ctu_cfg_init(void);

#endif /* APPLICATIONS_CFG_CTU_CFG_H_ */
