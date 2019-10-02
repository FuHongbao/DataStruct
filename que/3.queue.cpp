/*************************************************************************
	> File Name: 3.queue.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年07月17日 星期三 14时11分07秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

typedef struct Queue{
    int *data;
    int head, tail;
    int length, count;
}Queue;

Queue *init(int n) {
    Queue *q = (Queue*) malloc (sizeof(Queue));
    q->data = (int*)malloc(sizeof(int) * n);
    q->length = n;
    q->count = 0;
    q->head = q->tail = 0;
    return q;
}

int empty(Queue *q) {
    return q->count == 0;
}

int front(Queue *q) {
    return q->data[q->head];
}

int push(Queue *q, int val) {
    if (!q) return 0;
    if (q->count >= q->length) return 0;
    q->data[q->tail++] = val;
    if (q->tail >= q->length) q->tail -= q->length;
    q->count += 1;
    return 1;
}

int pop(Queue *q) {
    if (!q) return 0;
    if (empty(q)) return 0;
    q->head ++;
    if (q->head >= q->length) q->head -= q->length;
    q->count -= 1;
    return 1;
}

void clear(Queue *q) {
    if (!q) return ;
    free(q->data);
    free(q);
}

void output(Queue *q) {
    cout << "queue:[";
    for (int i = 0; i < q->count; i++) {
        printf("%d ", q->data[(q->head + i) % q->length]);
    }
    cout << "]" << endl;
}

int main() {
    #define MAX_OP 20
    srand(time(0));
    Queue *q = init(MAX_OP);
    for (int i = 0; i < MAX_OP; i++) {
        int val = rand()%100, op = rand()%2;
        switch(op) {
            case 0:{
                printf("push %d to queue = %d\n", val, push(q, val));
            }break;
            case 1:{
                printf("pop %d from queue = %d\n", front(q), pop(q));
            }break;
        }
    output(q);
    }
    printf ("head : %d, tail : %d, count : %d\n", q->head, q->tail, q->count);
    for (int i = 0; i < MAX_OP; i++) {
        push(q, i);
    }
    output(q);
    clear(q);
    return 0;
}

