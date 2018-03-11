//
//  readlink.c
//  dir_op
//
//  Created by YangHan on 2018/3/11.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("至少需要两个命令行参数\n");
        exit(1);
    }
    
    char buf[1024];
    
    /**
     *  读符号链接所指向的文件名字，不读文件内容
     */
    if (readlink(argv[1], buf, sizeof(buf)) < 0) {
        perror("readlink fail ");
        exit(1);
    }
    int len = (int)strlen(buf);
    buf[len] = '\0';
    printf("%s \n", buf);
    
    return 0;
}
