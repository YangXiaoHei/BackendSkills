//
//  SList.c
//  Libevent-Study5
//
//  Created by YangHan on 2018/4/1.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include "SList.h"
#include <stdlib.h>
#include <stdio.h>

SList sl_create() {
    SList ls = malloc(sizeof(struct _SList));
    ls->first = NULL;
    ls->last = NULL;
    ls->size = 0;
    return ls;
}

void sl_insert_before(SList ls, SNode n, int d) {
    ++ls->size;
    SNode newn = malloc(sizeof(struct _SNode));
    newn->data = d;
    newn->prev = n->prev;
    newn->next = n;
    if (n->prev) {
        n->prev->next = newn;
    }
    n->prev = newn;
}

void sl_insert_after(SList ls, SNode n, int d) {
    ++ls->size;
    SNode newn = malloc(sizeof(struct _SNode));
    newn->data = d;
    newn->prev = n;
    newn->next = n->next;
    if (n->next) {
        n->next->prev = newn;
    }
    n->next = newn;
}

void sl_insert_head(SList ls, int d) {
    SNode newn = malloc(sizeof(struct _SNode));
    newn->data = d;
    newn->next = ls->first;
    newn->prev = NULL;
    if (ls->first) {
        ls->first->prev = newn;
    }
    ls->first = newn;
    if (ls->first == NULL) {
        ls->first = newn;
    }
    if (ls->last == NULL) {
        ls->last = newn;
    }
}

void sl_insert_tail(SList ls, int d) {
    SNode newn = malloc(sizeof(struct _SNode));
    newn->data = d;
    newn->next = NULL;
    newn->prev = ls->last;
    if (ls->last) {
        ls->last->next = newn;
    }
    ls->last = newn;
    if (ls->first == NULL) {
        ls->first = newn;
    }
    if (ls->last == NULL) {
        ls->last = newn;
    }
}

void sl_remove(SList ls, SNode n) {
    if (n->next != NULL) {
        n->next->prev = n->prev;
    } else {
        ls->last = n->prev;
    }
    if (n->prev != NULL) {
        n->prev->next = n->next;
    } else {
        ls->first = n->next;
    }
    free(n);
}

void sl_remove_all(SList ls) {
    while (ls->first != NULL) {
        sl_remove(ls, ls->first);
    }
}

void sl_printt(SList ls) {
    if (ls->first == NULL) {
        printf("空\n");
        return;
    }
    SNode f = NULL;
    for (f = ls->first; f->next; f = f->next) {
        printf("%zd -> ", f->data);
    }
    printf("%zd\n", f->data);
}









