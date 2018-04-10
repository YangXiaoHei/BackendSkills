//
//  SList.h
//  Libevent-Study5
//
//  Created by YangHan on 2018/4/1.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#ifndef SList_h
#define SList_h

#include <stdio.h>

struct _SNode {
    char a[100];
    double b;
    short c;
    long d[300];
    int data;
    struct _SNode *prev;
    char e[100];
    double f;
    short g;
    long h[300];
    struct _SNode *next;
    char i[100];
    double j;
    short k;
    long l[300];
};
typedef struct _SNode *SNode;

struct _SList {
    struct _SNode *first;
    struct _SNode *last;
    int size;
};
typedef struct _SList *SList;

SList sl_create(void);
void sl_insert_before(SList ls, SNode n, int d);
void sl_insert_after(SList ls, SNode n, int d) ;
void sl_insert_head(SList ls, int d);
void sl_insert_tail(SList ls, int d);
void sl_remove(SList ls, SNode n);
void sl_remove_all(SList ls);
void sl_printt(SList ls);


#endif /* SList_h */
