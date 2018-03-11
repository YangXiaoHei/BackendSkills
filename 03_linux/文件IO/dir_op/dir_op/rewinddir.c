//
//  rewinddir.c
//  dir_op
//
//  Created by YangHan on 2018/3/11.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("至少需要 1 个命令行参数\n");
        exit(1);
    }
    
    DIR * dir = opendir(argv[1]);
    
    if (dir == NULL) {
        perror(argv[1]);
        exit(1);
    }
    
    struct dirent *dir_p = NULL;
    while ((dir_p = readdir(dir)) != NULL) {
        printf("file name : %s\n", dir_p->d_name);
    }
    
    rewinddir(dir);
    
    printf("\n重头读一遍\n\n");
    
    while ((dir_p = readdir(dir)) != NULL) {
        printf("file name : %s\n", dir_p->d_name);
    }
    
    return 0;
    
}
