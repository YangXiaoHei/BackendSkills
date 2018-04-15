//
//  main.c
//  addrmethods
//
//  Created by YangHan on 2018/4/15.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

/**
 *  inet_pton
 inet_ntop
 */
void test() {
    
    const char *ipstr = "172.20.10.3";
    
    // inet_pton
    {
        struct in_addr addr;
        int ret = inet_pton(AF_INET, ipstr, &addr);
        if (ret != 1) {
            if (ret == 0) {
                printf("不是有效的表达式\n");
            } else {
                perror("inet_pton ");
            }
        } else {
            printf("IPv4 十进制地址  %d\n", addr.s_addr);
        }
    }
    
    // inet_ntop
    {
        /**
         *  调用者必须为串分配存储空间
         */
        //        INET_ADDRSTRLEN
        //        INET6_ADDRSTRLEN
        
        char ipv4[INET_ADDRSTRLEN];
        //        char ipv4[3];
        struct in_addr addr;
        addr.s_addr = 50992300;
        const char * ret = inet_ntop(AF_INET, &addr, ipv4, sizeof(ipv4));
        if (ret != NULL) {
            printf("ip 地址串 : %s\n", ipv4);
        } else {
            //inet_ntop: No space left on device
            perror("inet_ntop");
        }
    }
}

/**
 *  自己写一个 inet_pton
 */
int yh_ipv4_pton(const char *ip) {
    
    /* ip 串长度超出值 */
    if (strlen(ip) > INET_ADDRSTRLEN) {
        return -1;
    }
    
    /* 空指针 */
    if (ip == NULL) {
        return -2;
    }
    
    char buf[4]     = { 0 };
    unsigned ipv4   = 0;
    int nshf        = 0;
    int cur         = 0;
    
    for (const char *p = ip; *p; ++p) {
        
        /* ip 串中包含非法字符 */
        if ((*p < '0' || *p > '9') && *p != '.') {
            return -3;
        }
        
        /* 截取每一个字节 */
        if (*p == '.') {
            int n = atoi(buf);
            ipv4 |= (n << nshf);
            bzero(buf, sizeof(buf));
            nshf += 8;
            cur = 0;
            
            /* 临时存储字符串 */
        } else {
            buf[cur++] = *p;
        }
    }
    
    /* 最后是以 '/0' 结尾的 */
    ipv4 |= (atoi(buf) << nshf);
    
    return ipv4;
}

/**
 *  自己写一个 inet_ntop
 */
int yh_ipv4_ntop(unsigned ipv4, char *buf, size_t buf_len) {
    
    char tmp[INET_ADDRSTRLEN] = { 0 };
    
    unsigned char *p = (unsigned char *)&ipv4;
    snprintf(tmp, sizeof(tmp), "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
    
    /* 调用者分配的内存太小 */
    if (strlen(tmp) > buf_len) {
        return -1;
    }
    
    /* 傻逼传了个 NULL 进来 */
    if (buf == NULL) {
        return -2;
    }
    
    memcpy(buf, tmp, strlen(tmp));
    
    return 1;
}

void test2() {
    
    const char *ipstr = "172.20.10.3";
    
    /* 测试自己写的 pton */
    printf("%d\n", inet_addr(ipstr));
    printf("%d\n", yh_ipv4_pton(ipstr));
    
    /* 测试自己写的 ntop */
    char buf[INET_ADDRSTRLEN];
    bzero(buf, sizeof(buf));
    yh_ipv4_ntop(50992300, buf, sizeof(buf));
    printf("%s\n", buf);
}


int main(int argc, const char * argv[]) {
    
    test2();
    
    return 0;
}
