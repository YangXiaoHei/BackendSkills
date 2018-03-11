//
//  link.c
//  dir_op
//
//  Created by YangHan on 2018/3/11.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    if (argc < 3) {
        printf("命令行参数至少需要 2 个\n");
        exit(1);
    }
    
    /**
     *  创建一个硬链接
     */
    if (link(argv[1], argv[2]) < 0) {
        perror("link fail : ");
        exit(1);
    }
    return 0;
}
