/*************************************************************************
	> File Name: sort01.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年08月17日 星期六 16时10分45秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define swap(a, b) {\
    a ^= b; b^=a; a^=b;\
}

#define TEST(arr, n, func, args...) {\
    int *num = (int*) malloc(sizeof(int)*n);\
    memcpy(num, arr, sizeof(int) * n);\
    output(num, n);\
    printf("%s = ", #func);\
    func(args);\
    output(num, n);\
    free(num);\
}

void insert_sort(int *num, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && num[j] < num[j -1]; j--) {
            swap(num[j], num[j - 1]);
        }
    }
}

void bubble_sort(int *num, int n) {
    int times = 1;
    for (int i = 1; i < n && times; i++) {
        times = 0;
        for (int j = 0; j < n - i; j++) {
            if (num[j] > num[j + 1]) {
                swap(num[j], num[j + 1]);
                times++;
            }
        }
    }
    return  ;
}

void merge_sort(int *num, int l, int r) {
    if (r - l <= 1) {
        if (r - l == 1 && num[r] < num[l]) {
            swap(num[r], num[l]);
        }
        return ;
    }
    int mid = (r + l) / 2;
    merge_sort(num, l, mid) ;
    merge_sort(num, mid + 1, r);
    int *temp = (int*) malloc (sizeof(int) * (r - l + 1));
    int p1 = l, p2 = mid + 1, k = 0;
    while (p1 <= mid || p2 <= r) {
        if (p2 > r || (p1 <= mid && num[p1] <= num[p2])) {
            temp[k++] = num[p1++];
        } else {
            temp[k++] = num[p2++];
        }
    }
    memcpy(num + l, temp, sizeof(int) * (r - l + 1));
    free(temp);
    return ;
}

void randint(int *num, int n) {
    while (n--) {
        num[n] = rand() % 100;
    }
}

void output(int *num, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf(" %d", num[i]);
    } 
    printf("]\n");
}

int main() {
    srand(time(0));
    #define MAX_OP 20
    int arr[MAX_OP];
    randint(arr, MAX_OP);
    TEST(arr, MAX_OP, insert_sort, num, MAX_OP);
    TEST(arr, MAX_OP, bubble_sort, num, MAX_OP);
    TEST(arr, MAX_OP, merge_sort, num, 0, MAX_OP - 1);
    
    return 0;
}

