#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    
    if (argc < 3) {
        printf("应该至少有 3 个参数 [path] [r or w or x or e]\n");
        exit(1);
    }
    
    int flag = -1;
    
    if (strlen(argv[2]) != 1) {
        printf("无效权限位！-- %zd", strlen(argv[2]));
        exit(1);
    }
    
    argv[2][0] = tolower(argv[2][0]);
    
    if (strcmp(argv[2], "r") == 0) {
        if (access(argv[1], R_OK) != 0) {
            printf("没有读权限\n");
        } else {
            printf("读\n");
        }
    } else if (strcmp(argv[2], "w") == 0) {
        if (access(argv[1], W_OK) != 0) {
            printf("没有写权限\n");
        } else {
            printf("写\n");
        }
    } else if (strcmp(argv[2], "x") == 0) {
        if (access(argv[1], X_OK) != 0) {
            printf("没有执行权限\n");
        } else {
            printf("执行\n");
        }
    } else if (strcmp(argv[2], "f") == 0) {
        if (access(argv[1], F_OK) != 0) {
            printf("文件不存在\n");
        } else {
            printf("文件存在\n");
        }
    } else {
        printf("无效权限位!\n");
        exit(1);
    }
    
    return 0;
}
