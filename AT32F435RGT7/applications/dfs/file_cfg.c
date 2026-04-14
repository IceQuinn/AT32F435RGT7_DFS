/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-14     mutou       the first version
 */
#include "file_cfg.h"





struct FILE_CFG_Str file_cfg[] = {
    {"/cfg"},
    {"/log"},

//    {"/cfg", "ctu_cfg.json" },
//    {"/cfg", "relay_cfg.json"},
//    {"/log", "log.txt"},
};

int file_path_table = sizeof(file_cfg) / sizeof(file_cfg[0]);
