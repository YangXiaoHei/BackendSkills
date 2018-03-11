//
//  rmdir.c
//  dir_op
//
//  Created by YangHan on 2018/3/11.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("至少需要 1 个命令行参数\n");
        exit(1);
    }
    
    if (rmdir(argv[1]) < 0) {
        perror(argv[1]);
        exit(1);
    }
    
    return 0;
}
