/*************************************************************************
	> File Name: link_stack.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年08月14日 星期三 16时46分16秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Stack {
    Node head;
    int n;
} Stack;

Stack *init() {
    Stack *s = (Stack*) malloc (sizeof(Stack));
    s->head.next = NULL;
    s->n = 0;
    return s;
}

Node *getNewNode(int val) {
    Node *node = (Node *) malloc (sizeof(Node));
    node->data = val;
    node->next = NULL;
    return node;
}

int push(Stack *s, int val) {
    if (s == NULL) return 0;
    Node *p = getNewNode(val), *q;
    p->next = s->head.next;
    s->head.next = p;
    s->n += 1;
    return 1;
}

int empty(Stack *s) {
    return s->n == 0;
}

int top(Stack *s) {
    return s->head.next->data;
}

int pop(Stack *s) {
    if (empty(s)) return 0;
    Node *p = s->head.next;
    s->head.next = s->head.next->next;
    free(p);
    s->n -= 1;
    return 1;
}

void clear(Stack *s) {
    Node *p = s->head.next, *q;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    free(s);
}

int main() {
    srand(time(0));
    Stack *s = init();
    for (int i = 0; i < 10; i++) {
        int val = rand() % 100;
        push(s, val);
        cout << val << " ";
    }
    cout << endl;
    while (!empty(s)) {
        cout << top(s) << " ";
        pop(s);
    }
    cout << endl;
    clear(s);
    return 0;
}

