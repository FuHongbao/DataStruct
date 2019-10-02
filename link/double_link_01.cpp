/*************************************************************************
	> File Name: double_link_01.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年07月14日 星期日 14时32分27秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
using namespace std;

typedef struct Node{
    int data;
    struct Node *next;
    struct Node *prior;
}Node;

typedef struct LinkList{
    Node head;
    Node *tail;
    int length;
}LinkList;

Node *init_Node(int val) {
    Node *nod = (Node*) malloc (sizeof(Node));
    nod->data = val;
    nod->prior = NULL;
    nod->next = NULL;
    return nod;
}

LinkList *init_List() {
    LinkList *link = (LinkList*) malloc (sizeof(LinkList));
    link->head.prior = NULL;
    link->head.next = NULL;
    link->tail =link-> head.next;
    link->length = 0;
    return link;
}

LinkList *insert(LinkList *l, int ind, int val) {
    if (l == NULL) return l;
    if (ind < 0 || ind > l->length) return l;
    Node *p = &(l->head);
    while (ind--) {
        p = p->next;
    }
    Node *q = init_Node(val);
    q->next = p->next;
    q->prior = p;
    if (p->next != NULL)
    p->next->prior = q;
    p->next = q;
    if (q->next == NULL) {
        l->tail = q;
    }
    l->length += 1;
    return l;
}

void clear_node(Node *nod) {
    if (nod == NULL) return ;
    free(nod);
}
void clear_List(LinkList *l) {
    if (l == NULL) return ;
    Node *p = l->head.next, *q;
    while (p) {
        q = p->next;
        clear_node(p);
        p = q;
    }
    free(l);
}

LinkList *erase(LinkList *l, int ind) {
    if (l == NULL) return l;
    if (ind < 0 || ind >= l->length) return l;
    Node *p = &(l->head);
    while (ind--) {
        p = p->next;
    }
    Node *q = p->next;
    q->next->prior = p;
    p->next = q->next;
    clear_node(q);
    l->length -= 1;
    return l;
}

void output(LinkList *l) {
    if (l == NULL) return ;
    Node *p = l->head.next;
    while (p) {
        cout << p->data << "<-->";
        p = p->next;
    }
    cout << "NULL" << endl;
}

void reoutput(LinkList *l) {
    if (l->tail == NULL) return ;
    Node *p = l->tail;
    while (p != &(l->head)) {
        cout << p->data << "<-->";
        p = p->prior;
    }
    cout << "NULL" << endl;
}

int main() {
    LinkList *l = init_List();
    for (int i = 0; i < 10; i++) {
        l = insert(l, i, i+1);
    }
    output(l);
    erase(l, 4);
    erase(l, 3);
    output(l);
    reoutput(l);
    clear_List(l);
    return 0;
}

