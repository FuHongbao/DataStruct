/*************************************************************************
	> File Name: heap2.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年08月12日 星期一 09时50分22秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define swap(a, b) { \
    __typeof(a) _temp = a; \
    a = b, b = _temp; \
}

typedef struct Priority_queue {
    int *data;
    int cnt, size;
} Priority_queue;

Priority_queue *init(int n) {
    Priority_queue *q = (Priority_queue*) malloc (sizeof(Priority_queue));
    q->data = (int*) malloc (sizeof(int) * (n+1));
    q->cnt = 0;
    q->size = n;
    return q;
}

int empty(Priority_queue *q) {
    return q->cnt == 0;
}

int top(Priority_queue *q) {
    return q->data[1];
}

int push(Priority_queue *q, int val) {
    if (q == NULL) return 0;
    if (q->cnt == q->size) return 0;
    q->data[++q->cnt] = val;
    int ind = q->cnt;
    while ( ind >> 1 && q->data[ind] > q->data[ind >> 1] ) {
        swap (q->data[ind], q->data[ind >> 1]);
        ind >>= 1;
    }
    return 1;
}

int pop(Priority_queue *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0;
    q->data[1] = q->data[q->cnt];
    q->cnt--;
    int ind = 1;
    while (ind << 1 <= q->cnt) {
        int temp = ind, l = ind << 1, r = ind << 1 | 1;
        if (q->data[l] > q->data[temp]) temp = l;
        if (r <= q->cnt && q->data[r] > q->data[temp]) temp = r;
        if (temp == ind) break;
        swap(q->data[ind], q->data[temp]);
        ind = temp;
    }
    return 1;
}

void clear(Priority_queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

int main () {
    srand(time(0));
    #define MAX_OP 20
    Priority_queue *q = init(20);
    for (int i = 0; i < MAX_OP; i++) {
        int val = rand() % 100;
        push(q, val);
    }
    for (int i = 0; i < MAX_OP; i++) {
        printf("%d ", top(q));
        pop(q);
    }
    printf("\n");
    return 0;
}



