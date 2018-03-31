//
//  main.c
//  Libevent-Study5
//
//  Created by YangHan on 2018/4/1.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include "SList.h"
#include "DList.h"
#include <time.h>

int main(int argc, const char * argv[]) {
    
    clock_t s = clock();

    DList dl = dl_create();
    for (int i = 0; i < 2000000; i++) {
        dl_insert_tail(dl, i);
    }
    dl_remove_all(dl);
    
    clock_t e = clock();
    printf("总时间 : %.3f\n", (e - s) * 1.0 / CLOCKS_PER_SEC);
    
    s = clock();
    SList sl = sl_create();
    for (int i = 0; i < 2000000; i++) {
        sl_insert_tail(sl, i);
    }
    sl_remove_all(sl);
    
    e = clock();
    printf("总时间 : %.3f\n", (e - s) * 1.0 / CLOCKS_PER_SEC);
    
    return 0;
}
