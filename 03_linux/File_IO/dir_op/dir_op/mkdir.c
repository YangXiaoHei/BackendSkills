//
//  mkdir.c
//  dir_op
//
//  Created by YangHan on 2018/3/11.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("命令行至少需要 1 个参数\n");
        exit(1);
    }
    
    umask(0);
    
    if (mkdir(argv[1], 0777) < 0) {
        perror(argv[1]);
        exit(1);
    }
    
    return 0;
}
