//
//  main.c
//  hostbyteorder
//
//  Created by YangHan on 2018/4/13.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>

#include <arpa/inet.h>

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

/**
 *  转换为网络字节序，大端，如果在大端机器中，hton 等宏被定义为空宏
 */
void test1() {
    short a = 0x1234;
    printf("%x\n", htons(a));
}

/**
 *  inet_aton、inet_addr、inet_ntoa
    ⚠️ 以下函数均被废弃，不要再使用
 */
void test2() {
    
    // inet_aton
    {
        struct sockaddr_in addr;
        // 成功返回 1，失败返回 0
        if (inet_aton("10.10.3.24", &addr.sin_addr) > 0) {
            printf("ip 地址有效 : %d\n", addr.sin_addr.s_addr);
        } else {
            printf("ip 地址无效");
        }
    }
    
    // inet_addr
    {
        int ipv4 = 0;
        if ((ipv4 = inet_addr("10.10.3.24")) != INADDR_NONE) {
            printf("字符串有效，返回 32 位二进制网络字节序 IPv4 地址 : %d\n", ipv4);
        } else {
            printf("字符串无效\n");
        }
    }
   
    // inet_ntoa
    {
        char *ipstr = NULL;
        struct in_addr iaddr;
        iaddr.s_addr = 402852362;
        if ((ipstr = inet_ntoa(iaddr)) != NULL) {
            printf("ip 串为 : %s\n", ipstr);
        } else {
            printf("ip 地址无\n");
        }
    }
}


int main(int argc, const char * argv[]) {
    
    test2();
    
    return 0;
}
