//
//  main.c
//  test
//
//  Created by YangHan on 2018/4/2.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

struct eventop {
    const char *name;
};

struct base {
    const struct eventop *evsel;
};

struct dump {
    char *a;
};

int main(int argc, const char * argv[]) {
    
    struct base *b = malloc(sizeof(struct base));
    struct eventop *e = malloc(sizeof(struct eventop));
    e->name = "yanghan";
    b->evsel = e;
    
    char **p = (char **)b;
    printf("%s\n", **p);
//    printf("%ld\n", *b);
//    printf("%ld\n", b->evsel);
//    printf("%s\n", *b->evsel);
    
    printf("\n\n\n");
    
    
    
    
    
    
    
    return 0;
}
