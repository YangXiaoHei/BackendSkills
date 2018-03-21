//
//  truncate.c
//  dir_op
//
//  Created by YangHan on 2018/3/11.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    
    if (argc < 3) {
        printf("至少需要 3 个命令行参数\n");
        exit(1);
    }
    
    /**
     *  如果 length 大于 原文件尺寸，那么就相当于扩充文件尺寸到指定的 length
        如果 length 小于 原文件尺寸，那么就相当于裁剪文件尺寸到指定的 length (原有内容会被删减)
     */
    if (truncate(argv[1], atoi(argv[2])) < 0) {
        perror("truncate fail ");
        exit(1);
    }
    return 0;
}
