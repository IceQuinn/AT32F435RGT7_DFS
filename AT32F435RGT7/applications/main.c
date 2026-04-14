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

//#include "spi_ex_flash_sfud.h"
//#include <fal.h>
//
//#include <dfs_posix.h> /* 当需要使用文件操作时，需要包含这个头文件 */

#include "ctu_cfg.h"

#include "main_dfs.h"




int main(void)
{
    main_dfs_init();

    ctu_cfg_init();

    return RT_EOK;
}
