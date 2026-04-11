/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-10     RT-Thread    first version
 */

#include <rtthread.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include "spi_ex_flash_sfud.h"
#include <fal.h>

#include <dfs_posix.h> /* 当需要使用文件操作时，需要包含这个头文件 */


int main(void)
{
    ex_flash_spi_init();

    fal_init();

    // 将所有分区配置成块设备
    size_t part_num;
    const struct fal_partition *part_table = fal_get_partition_table(&part_num);

    if (part_table != NULL) {
        for (size_t i = 0; i < part_num; i++) {
            fal_blk_device_create(part_table[i].name);
        }
    }

    // 尝试挂载文件系统
    if(RT_EOK != dfs_mount("systemfile", "/", "elm", 0, 0)){
        // 格式化文件系统
        if(RT_EOK == dfs_mkfs("elm", "systemfile")){
            // 重试，挂载文件系统
            if(RT_EOK != dfs_mount("systemfile", "/", "elm", 0, 0)){
                LOG_W("EX_Flash mount to FlashPath failed! No DFS Working!!!");
            }
            else {
                LOG_I("do dfs_mount() again success");
            }
        }
        else{
            LOG_W("EX_Flash dfs_mkfs() failed!");
        }
    }
    else {
        LOG_I("do dfs_mount() success");
    }

    mkdir("/cfg", 0x777);

    if(RT_EOK != dfs_mount("cfg", "/cfg", "elm", 0, 0)){
        // 格式化文件系统
        if(RT_EOK == dfs_mkfs("elm", "cfg")){
            // 重试，挂载文件系统
            if(RT_EOK != dfs_mount("cfg", "/cfg", "elm", 0, 0)){
                LOG_W("cfg mount to /cfg failed! No DFS Working!!!");
            }
            else {
                LOG_I("do dfs_mount() again success");
            }
        }
        else{
            LOG_W("cfg dfs_mkfs() failed!");
        }
    }
    else {
        LOG_I("do dfs_mount() success");
    }

    return RT_EOK;
}
