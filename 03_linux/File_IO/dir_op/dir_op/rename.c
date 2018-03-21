//
//  rename.c
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
        printf("命令行至少需要 2 个参数\n");
        exit(1);
    }
    
    if (rename(argv[1], argv[2]) < 0) {
        perror("rename fail ");
        exit(1);
    }
    return 0;
}
