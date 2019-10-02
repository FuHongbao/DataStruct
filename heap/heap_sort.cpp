/*************************************************************************
	> File Name: heap_sort.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年08月05日 星期一 18时07分11秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX_N 1000
#define swap(a, b) { \
    __typeof(a) __temp = a;\
    a = b, b = __temp;\
}
int num[MAX_N + 5], n;

void heap_sort(int *num, int n) {
    num -= 1;
    for (int i = 2 ;i <= n; i++) {
        int ind = i;
        while (ind != 1 && num[ind] > num[ind >> 1]) {
            swap(num[ind], num[ind >> 1]);
            ind >>= 1;
        }
    }
    for (int i = n; i >= 2; i--) {
        swap(num[i], num[1]);
        int ind = 1;
        while ((ind << 1) < i) {
            int temp = ind, lchild = ind << 1, rchild = ind << 1 | 1;
            if (num[temp] < num[lchild]) temp = lchild;
            if (rchild < i && num[temp] < num[rchild]) temp = rchild;
            if (temp == ind) break;
            swap(num[temp], num[ind]);
            ind = temp;
        }
    } 
    return;
}


int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &num[i]);
    }
    heap_sort(num, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", num[i]);
    }
    printf("\n");
    return 0;
}


