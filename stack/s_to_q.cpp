/*************************************************************************
	> File Name: s_to_q.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年07月17日 星期三 12时49分49秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

typedef struct Stack{
    int *data;
    int top, size;
} Stack;

typedef struct Queue{
    Stack *a;
    Stack *b;
} Queue;

Stack *init_stack(int n) {
    Stack *s = (Stack*)malloc(sizeof(Stack));
    s->data = (int*)malloc(sizeof(int) * n);
    s->top = -1;
    s->size = n;
    return s;
}

int empty(Stack *s) {
    return s->top == -1;
}

int top_stack(Stack *s) {
    return s->data[s->top];
}

int push_stack(Stack *s, int val) {
    if (s->top >= s->size) return 0;
    s->top++;
    s->data[s->top] = val;
    return 1;
}

int pop_stack(Stack *s) {
    if (empty(s)) return 0;
    s->top--;
    return 1;
}

void clear(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
}

Queue *init_que(int n) {
    Queue *que = (Queue*) malloc (sizeof(Queue));
    que->a = init_stack(n);
    que->b = init_stack(n);
    return que;
}

int empty_que(Queue *q) {
    return (empty(q->a) && empty(q->b));
}

int push_que(Queue *q, int val) {
    if(push_stack(q->a, val)){
        return 1;
    }
    return 0;
} 

int pop_que(Queue *q) {
    int val;
    if (empty(q->b)) {
        while(!empty(q->a)) {
            val = top_stack(q->a);
            pop_stack(q->a);
            push_stack(q->b, val);
        }
    }
    val = top_stack(q->b);
    pop_stack(q->b);
    return val;
}

int top_que(Queue *q) {
    int val;
    if (empty(q->b)) {
        while (!empty(q->a)) {
            val = top_stack(q->a);
            pop_stack(q->a);
            push_stack(q->b, val);
        }
    }
    return top_stack(q->b);
}

void clear_que(Queue *q) {
    if (q == NULL) return ;
    clear(q->a);
    clear(q->b);
    free(q);
}


int main() {
    Queue *q = init_que(20); 
    for (int i = 0; i < 20; i++) {
        push_que(q, i+1);
    }
    for (int i = 0; i < 10; i++) {
        cout << pop_que(q) << " ";
    }
    cout << endl;
    cout << "top ：" << top_que(q) << endl;
    clear_que(q);
    return 0;
}

