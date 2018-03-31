//
//  DList.h
//  Libevent-Study5
//
//  Created by YangHan on 2018/4/1.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#ifndef DList_h
#define DList_h

#include <stdio.h>

struct _DNode {
    char a[100];
    double b;
    short c;
    long d[300];
    int data;
    struct _DNode *next;
    char e[100];
    double f;
    short g;
    long h[300];
    struct _DNode **prev;
    char i[100];
    double j;
    short k;
    long l[300];
};
typedef struct _DNode *DNode;

struct _DList {
    struct _DNode *first;
    struct _DNode **last;
    int size;
};
typedef struct _DList *DList;

DList dl_create(void);
void dl_insert_head(DList dl, int d);
void dl_insert_tail(DList dl, int d);
void dl_remove(DList dl, DNode n) ;
void dl_remove_all(DList dl);
void dl_print(DList dl);

#endif /* DList_h */
