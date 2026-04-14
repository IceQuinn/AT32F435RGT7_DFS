/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-14     mutou       the first version
 */
#ifndef APPLICATIONS_DFS_FILE_CFG_H_
#define APPLICATIONS_DFS_FILE_CFG_H_



struct FILE_CFG_Str
{
    char *path;         // 文件路径
//    char *file_name;    // 文件名
};


extern struct FILE_CFG_Str file_cfg[];
extern int file_path_table;

#endif /* APPLICATIONS_DFS_FILE_CFG_H_ */
