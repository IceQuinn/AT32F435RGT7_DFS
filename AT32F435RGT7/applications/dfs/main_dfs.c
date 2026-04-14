/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-14     mutou       the first version
 */
#include "main_dfs.h"

#include "spi_ex_flash_sfud.h"
#include <fal.h>

#include <dfs_posix.h> /* 当需要使用文件操作时，需要包含这个头文件 */

#include "file_cfg.h"

#define DBG_TAG "main_dfs"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>


void user_dfs_init(void)
{
    // 将所有分区配置成块设备
    size_t part_num;
    const struct fal_partition *part_table = fal_get_partition_table(&part_num);

    if (part_table != NULL) {
        for (size_t i = 0; i < part_num; i++) {
            // 创建块设备
            fal_blk_device_create(part_table[i].name);
        }
    }

    char cwd[128] = {0};
    for (size_t i = 0; i < part_num; i++) {
        rt_memset(cwd, 0, sizeof(cwd));
        if(0 == i){
            cwd[0] = '/';
        }
        else{
            rt_sprintf(cwd, "/%s", part_table[i].name);
            mkdir(cwd, 0x777);
        }
        // 尝试挂载文件系统
        if(RT_EOK != dfs_mount(part_table[i].name, cwd, "elm", 0, 0)){
            // 格式化文件系统
            if(RT_EOK == dfs_mkfs("elm", part_table[i].name)){
                // 重试，挂载文件系统
                if(RT_EOK != dfs_mount(part_table[i].name, cwd, "elm", 0, 0)){
                    LOG_W("%s dfs_mount to %s failed! No DFS Working!!!", part_table[i].name, cwd);
                }
                else {
                    LOG_I("%s dfs_mount to %s again success", part_table[i].name, cwd);
                }
            }
            else{
                LOG_W("%s dfs_mkfs to %s failed!", part_table[i].name);
            }
        }
        else{
            LOG_I("%s dfs_mount to %s success", part_table[i].name, cwd);
        }
    }
}

void dfs_file_init(void)
{
    // 初始化文件夹，文件
    for(int32_t i=0; i<file_path_table; i++) {
        if(opendir(file_cfg[i].path) == NULL) {
            LOG_W("%s opendir() failed!", file_cfg[i].path);
            if(0 != mkdir(file_cfg[i].path, 0x777)){
                LOG_W("%s mkdir() failed!", file_cfg[i].path);
                continue;
            }
            LOG_I("%s mkdir() success!", file_cfg[i].path);
        }
        else{
            LOG_I("%s opendir() success!", file_cfg[i].path);
        }
    }
}


void main_dfs_init(void)
{
    // SPI 初始化及SFUD初始化
    ex_flash_spi_init();
    // FAL FLash抽象层初始化
    fal_init();

    // DSF 虚拟文件系统初始化
    user_dfs_init();

    // 文件夹及文件初始化
    dfs_file_init();

}

