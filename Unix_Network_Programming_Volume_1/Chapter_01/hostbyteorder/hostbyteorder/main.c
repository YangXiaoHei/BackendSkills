//
//  main.c
//  hostbyteorder
//
//  Created by YangHan on 2018/4/13.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>

/**
 *  内存模型图测试
 */
void test() {
    int a = 0x87654321;
    
    struct {
        int a[2];
    } s;
    
    int b = 0x12345678;
    
    s.a[0] = 0x11223344;
    s.a[1] = 0x19283746;
    
    printf("%ld\n", (long)&a);
    printf("%ld\n", (long)&s.a[1]);
    printf("%ld\n", (long)&s.a[0]);
    printf("%ld\n", (long)&b);
    
    char *p = (char *)&a;
    for (int i = 0; i <= 16; i++) {
        printf("地址 : %ld  值 : %x\n", (long)(p - i), *(p - i));
    }
}

int main(int argc, const char * argv[]) {
    
   
    
    return 0;
}
