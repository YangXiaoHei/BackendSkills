//
//  chdir.c
//  dir_op
//
//  Created by YangHan on 2018/3/11.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("至少需要 1 个命令行参数\n");
        exit(1);
    }
    
    char buf[1024];
    
    /**
     *  改变当前进程的工作目录
     */
    if (chdir(argv[1]) < 0) {
        perror("chdir fail ");
        exit(1);
    }
    /**
     *  获取当前进程的工作目录
     */
    if (getcwd(buf, sizeof(buf)) == NULL) {
        perror("getcwd fail ");
        exit(1);
    }
    printf("当前进程的工作目录 : %s\n", buf);
    return 0;
}
