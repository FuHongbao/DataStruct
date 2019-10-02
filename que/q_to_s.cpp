/*************************************************************************
	> File Name: q_to_s.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年07月17日 星期三 11时32分41秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

typedef struct Queue{
    int *data;
    int head, tail, size, count;
}Queue;

typedef struct Stack{
    Queue *p;
    Queue *q;
}Stack;

Queue *init(int n) {
    Queue *que = (Queue*) malloc (sizeof(Queue));
    que->data = (int*)malloc(sizeof(int) * n);
    que->head = que->tail = 0;
    que->size = n;
    que->count = 0;
    return que;
}

Stack *init_stack(int n) {
    Stack *st = (Stack *)malloc(sizeof(Stack));
    st->p = init(n);
    st->q = init(n);
    return st;
}

int front(Queue *q) {
    if (q->count == 0) return -1;
    return q->data[q->head]; 
}

int push_que(Queue *q, int val) {
    if (q->count >= q->size) return 0;
    q->data[q->tail] = val;
    q->tail ++;
    if (q->tail >= q->size) q->tail -= q->size;
    q->count += 1;
    return 1;
}
bool empty(Queue *q) {
    return q->count == 0;
}
void push_stack(Queue *p, Queue *q, int val) {
    if (!empty(q)) {
        push_que(q, val);
    } else {
        push_que(p, val);
    }
}

int pop_que(Queue *q) {
    q->head += 1;
    if (q->head >= q->size) q->head -= q->size;
    q->count -= 1;
    return 1;
}

void pop_stack(Queue *p, Queue *q) {
    Queue *tmp = NULL, *tnp = NULL;
    if (!empty(p)) {
        tmp = p;
        tnp = q;
    } else {
        tmp = q;
        tnp = p;
    }
    while (tmp->count > 1) {
        int val = front(tmp);
        pop_que(tmp);
        push_que(tnp, val);
    }
    cout << "出栈元素: " << front(tmp) << endl;
    pop_que(tmp);
    return ;
}

void clear(Queue *q) {
    free(q->data);
    free(q);
}

void clear_stack(Stack *s) {
    clear(s->p);
    clear(s->q);
    free(s);
}

int main() {
    Stack *st = init_stack(20); 
    int k;
    for (int i = 0; i <= 5; i++) {
        cin >> k;
        push_stack(st->p, st->q, k);
    }
    for (int i = 0; i <= 5; i++) {
        pop_stack(st->p, st->q);
    }
    clear_stack(st);
    return 0;
}



