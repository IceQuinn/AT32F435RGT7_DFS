/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-13     mutou       the first version
 */
#include "json_rw.h"

//#include <dfs_posix.h>
//
//#include "cJSON.h"
//
//
//void Json_Read(const char* file, void *data, int len)
//{
//    int fd = open(file, O_RDWR | O_CREAT, 0);
//
//    if (fd >= 0)
//    {
//        rt_kprintf("read json ctu cfg\n");
//        if(0 == read(fd, &data, len))
//        {
//            rt_kprintf("ctu cfg reset\n");
//            set_default_para();
//            write(fd, &data, len);
//        }
//        else
//        {
//            rt_kprintf("ctu cfg read ok\n");
//        }
//    }
//}
