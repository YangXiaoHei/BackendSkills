//
//  readdir.c
//  dir_op
//
//  Created by YangHan on 2018/3/11.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    DIR *dir = opendir(argv[1]);
    
    if (dir == NULL) {
        perror(argv[1]);
        exit(1);
    }
    
    struct dirent *dir_p = NULL;
    while ((dir_p = readdir(dir)) != NULL) {
        printf("file name : %s\n", dir_p->d_name);
        printf("file inode : %zd\n", dir_p->d_ino);
    }
    if (errno != 0) {
        perror("readdir fail ");
        exit(1);
    }
    return 0;
}
