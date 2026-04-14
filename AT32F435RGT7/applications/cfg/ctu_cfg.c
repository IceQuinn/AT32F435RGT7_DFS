/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-13     mutou       the first version
 */
#include "ctu_cfg.h"
#include <dfs_posix.h>

#include "cJSON.h"

struct CTU_CFG_Str ctu_cfg;

void set_default_para(void)
{
    /* 通讯参数 */
    ctu_cfg.uart_protocol[0]     = 0;        //协议,0=modbus协议,1=dlt645协议
    ctu_cfg.uart_baud[0]         = 9600;     //波特率
    ctu_cfg.uart_check[0]        = 0;        //校验位

    ctu_cfg.uart_protocol[1]     = 0;        //协议,0=modbus协议,1=dlt645协议
    ctu_cfg.uart_baud[1]         = 9600;     //波特率
    ctu_cfg.uart_check[1]        = 0;        //校验位

    ctu_cfg.uart_protocol[2]     = 0;        //协议,0=modbus协议,1=dlt645协议
    ctu_cfg.uart_baud[2]         = 9600;     //波特率
    ctu_cfg.uart_check[2]        = 0;        //校验位

    ctu_cfg.modbus_slave_addr           = 1;        //从机地址
    for(uint8_t i=0; i<6; i++)
    {
        ctu_cfg.dlt645_bcd_addr[i]      = i;        //dlt645通信地址
    }
    /* 基本参数 */
    ctu_cfg.show_ctrl                   = 1;        //显示配置 0：显示二次值，1：显示一次值
    /* IO参数 */
    for(uint8_t i=0; i<2; i++)
    {
        ctu_cfg.DI_delay[i]             = 20;       //DI去抖时间    20ms
    }
    for(uint8_t i=0; i<4; i++)
    {
        ctu_cfg.DO_delay[i]             = 500;       //KO脉冲延时    500ms
    }
    /* 显示参数 */
    ctu_cfg.backlight_time              = 1;        //背光时间分钟
    ctu_cfg.backlight_Rate              = 50;       //背光亮度
    //GSE8625-QR/GSE8625-DG-B
    ctu_cfg.constrast                   = 90;       //对比度
    /* 装置维护 */
    ctu_cfg.user_password               = 1111;     //用户密码
    ctu_cfg.admin_password              = 8000;     //厂商密码

    /* 无线配置 */
    ctu_cfg.wl_channel                  = 60;       //默认470MHz
    ctu_cfg.wl_addr                     = 0x0001;   //无线地址

    for(uint8_t i=0; i<4; i++)
    {
        ctu_cfg.yk_do_delay[i] = 10000; // 手动开出保持时间
    }
}





struct Json_map_Str{
    const char *key;
    void *ptr;
    // int type;
    int default_val;
};

#define JSON_STR(str, mem, val) {#mem, &str.mem, val}

struct Json_map_Str Json_map[] = {
    JSON_STR(ctu_cfg, uart_protocol[0],     0),
    JSON_STR(ctu_cfg, uart_baud[0],         9600),
    JSON_STR(ctu_cfg, uart_check[0],        0),

    JSON_STR(ctu_cfg, uart_protocol[1],     0),
    JSON_STR(ctu_cfg, uart_baud[1],         9600),
    JSON_STR(ctu_cfg, uart_check[1],        0),

    JSON_STR(ctu_cfg, uart_protocol[2],     0),
    JSON_STR(ctu_cfg, uart_baud[2],         9600),
    JSON_STR(ctu_cfg, uart_check[2],        0),

    JSON_STR(ctu_cfg, modbus_slave_addr,    1),
    JSON_STR(ctu_cfg, dlt645_bcd_addr[0],   0),
    JSON_STR(ctu_cfg, dlt645_bcd_addr[1],   1),
    JSON_STR(ctu_cfg, dlt645_bcd_addr[2],   2),
    JSON_STR(ctu_cfg, dlt645_bcd_addr[3],   3),
    JSON_STR(ctu_cfg, dlt645_bcd_addr[4],   4),
    JSON_STR(ctu_cfg, dlt645_bcd_addr[5],   5),
    JSON_STR(ctu_cfg, show_ctrl,            1),

    JSON_STR(ctu_cfg, DI_delay[0],          20),
    JSON_STR(ctu_cfg, DI_delay[1],          20),
    JSON_STR(ctu_cfg, DO_delay[0],          20),
    JSON_STR(ctu_cfg, DO_delay[1],          20),
    JSON_STR(ctu_cfg, DI_delay[0],          20),
    JSON_STR(ctu_cfg, DI_delay[1],          20),
    JSON_STR(ctu_cfg, DO_delay[0],          20),
    JSON_STR(ctu_cfg, DO_delay[1],          20),
    JSON_STR(ctu_cfg, DO_delay[2],          20),
    JSON_STR(ctu_cfg, DO_delay[3],          20),

    JSON_STR(ctu_cfg, backlight_time,       1),
    JSON_STR(ctu_cfg, backlight_Rate,       50),
    JSON_STR(ctu_cfg, constrast,            90),
    JSON_STR(ctu_cfg, user_password,        1111),
    JSON_STR(ctu_cfg, admin_password,       8000),
    JSON_STR(ctu_cfg, wl_channel,           60),
    JSON_STR(ctu_cfg, wl_addr,              0x0001),
    JSON_STR(ctu_cfg, yk_do_delay[0],       10000),
    JSON_STR(ctu_cfg, yk_do_delay[1],       10000),
    JSON_STR(ctu_cfg, yk_do_delay[2],       10000),
    JSON_STR(ctu_cfg, yk_do_delay[3],       10000),
};

void ctu_cfg_reset(void)
{
    for(int i = 0; i < sizeof(Json_map)/sizeof(Json_map[0]); i++){
        *(int32_t *)Json_map[i].ptr = Json_map[i].default_val;
    }
}

void show_ctu_cfg(void)
{
    for(int i = 0; i < sizeof(Json_map)/sizeof(Json_map[0]); i++){
        rt_kprintf("%s\t = %d \n", Json_map[i].key, *(int32_t *)Json_map[i].ptr);
    }
}

int ctu_cfg_init(void)
{
   int fd;
   // 打开文件
   fd = open("/cfg/param.txt", O_CREAT | O_RDWR, 0);
   if (fd >= 0)
   {
        struct stat st;
        if (stat("/cfg/param.txt", &st) != 0) {
            rt_kprintf("param.txt file not exist\n");
        }

        cJSON* root = NULL;

        if(0 == st.st_size){
            ctu_cfg_reset();

            root = cJSON_CreateObject();

            for(int i = 0; i < sizeof(Json_map)/sizeof(Json_map[0]); i++){
                cJSON_AddNumberToObject(root, Json_map[i].key, *(int32_t *)Json_map[i].ptr);
            }

            // 生成字符串（带格式，方便人看）
            char *json_str = cJSON_Print(root);

            // 写入文件
            write(fd, json_str, strlen(json_str));
            free(json_str);
        }
        else{
            char* buffer = (char*)rt_malloc(st.st_size + 1);
            rt_memset(buffer, 0, st.st_size + 1);
            if(st.st_size == read(fd, buffer, st.st_size)){
                buffer[st.st_size] = '\0';
            }
    
            root = cJSON_Parse(buffer);
            cJSON* item = NULL;
            int array_size = cJSON_GetArraySize(root);
            for(int i = 0; i < array_size; i++){
                item = cJSON_GetObjectItem(root, Json_map[i].key);
                if (cJSON_IsNumber(item)){
                    *(int32_t *)Json_map[i].ptr = item->valueint;
                }
            }
            rt_free(buffer);
        }
        cJSON_Delete(root);
   }

   close(fd);

   show_ctu_cfg();

}


