//
//  symlink.c
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
        printf("命令行至少需要 1 个参数\n");
        exit(1);
    }
    
    /**
     *  创建一个符号链接
     */
    if (symlink(argv[1], argv[2]) < 0) {
        perror("symlink fail : ");
        exit(1);
    }
    
    return 0;
    
}
