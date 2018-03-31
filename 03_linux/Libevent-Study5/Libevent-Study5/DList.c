//
//  DList.c
//  Libevent-Study5
//
//  Created by YangHan on 2018/4/1.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include "DList.h"
#include <stdlib.h>
#include <stdio.h>

DList dl_create() {
    DList dl = malloc(sizeof(struct _DList));
    dl->first = NULL;
    dl->last = &dl->first;
    dl->size = 0;
    return dl;
}

void dl_insert_head(DList dl, int d) {
    DNode newn = malloc(sizeof(struct _DNode));
    newn->data = d;
    if ((newn->next = dl->first) != NULL) {
        dl->first->prev = &newn->next;
    } else {
        dl->last = &newn->next;
    }
    dl->first = newn;
    newn->prev = &dl->first;
}

void dl_insert_tail(DList dl, int d) {
    DNode newn = malloc(sizeof(struct _DNode));
    newn->data = d;
    newn->prev = dl->last;
    newn->next = NULL;
    *(dl->last) = newn;
    dl->last = &newn->next;
}

void dl_remove(DList dl, DNode n) {
    if (n->next != NULL) {
        n->next->prev = n->prev;
    } else {
        dl->last = n->prev;
    }
    *(n->prev) = n->next;
    free(n);
}

void dl_remove_all(DList dl) {
    while (dl->first != NULL) {
        dl_remove(dl, dl->first);
    }
}

void dl_print(DList dl) {
    if (dl->first == NULL) {
        printf("空\n");
        return;
    }
    DNode f = NULL;
    for (f = dl->first; f->next; f = f->next) {
        printf("%d -> ", f->data);
    }
    printf("%d\n", f->data);
}










