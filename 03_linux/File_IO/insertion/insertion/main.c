//
//  main.c
//  insertion
//
//  Created by YangHan on 2018/3/13.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#define T_BEGIN \
clock_t start = clock()

#define T_END \
((clock() - start) * 1.0 / CLOCKS_PER_SEC)

double insertion_a(int a[], int size) {
    T_BEGIN;
    for (int i = 0; i < size; i++) {
        for (int j = i; j > 0 && a[j] < a[j - 1]; j--) {
            int t = a[j];
            a[j] = a[j - 1];
            a[j - 1] = t;
        }
    }
    
    return T_END;
}

double insertion_b(int a[], int size) {
    T_BEGIN;
    for (int i = 0; i < size; i++) {
        int v = a[i], j;
        for (j = i - 1; j >= 0 && v < a[j]; j--)
            a[j + 1] = a[j];
        a[j + 1] = v;
    }
    return T_END;
}

double insertion_c(int a[], int size) {
    T_BEGIN;
    int exchs = 0;
    for (int i = size - 1; i > 0; i--) {
        if (a[i] < a[i - 1]) {
            int t = a[i];
            a[i] = a[i - 1];
            a[i - 1] = t;
            exchs++;
        }
    }
    if (exchs == 0)  return T_END;
    for (int i = 2; i < size; i++) {
        int v = a[i], j = i;
        while (v < a[j - 1]) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = v;
    }
    return T_END;
}

int *arr(int N) {
    int *a = calloc(N, sizeof(int));
    int j = 0;
    for (int i = N; i > 0; i--) {
        a[j++] = i;
    }
    return a;
}

int *copy(int a[], int size) {
    int *b = calloc(size, sizeof(int));
    for (int i = 0; i < size; i++) {
        b[i] = a[i];
    }
    return b;
}

void print(int a[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%-3d", a[i]);
    }
    printf("\n");
}

int issorted(int a[], int size) {
    for (int i = 1; i < size; i++) {
        if (a[i] < a[i - 1]) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, const char * argv[]) {
    
    if (argc < 2) {
        printf("至少需要 1 个命令行参数\n");
        exit(1);
    }
    
    int N = atoi(argv[1]);
    
    if (N <= 0) {
        exit(1);
    }
    
    srand((unsigned int)time(NULL));
    int *a = arr(N);
    int *b = copy(a, N);
    int *c = copy(a, N);
    
    double t1 = insertion_a(a, N);
    double t2 = insertion_b(b, N);
    double t3 = insertion_c(c, N);
    
    printf("A : %.3f\n", t1);
    printf("B : %.3f\n", t2);
    printf("C : %.3f\n", t3);
    
    assert(issorted(a, N));
    assert(issorted(b, N));
    assert(issorted(c, N));
    
    return 0;
}
