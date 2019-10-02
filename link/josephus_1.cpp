/*************************************************************************
	> File Name: josephus_1.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年07月13日 星期六 22时25分11秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct Node{
    int data;
    struct Node *next;
} Node, *LinkList;

LinkList insert(LinkList head, Node *nod, int ind) {
    if (head == NULL) {
        if (ind == 0) {
            head = nod;
            head->next = head;
            return head;
        }
        return head;
    }
    if (ind == 0) {
        nod->next = head->next;
        head->next = nod;
        return head;
    } 
    Node *p = head->next;
    int cnt = 0;
    while (p->next != p && cnt < ind - 1) {
        cnt++;
        p = p->next;
    }
    if (cnt == ind - 1) {
        nod->next = p->next;
        p->next = nod;
    }
    if (nod = head->next) {
        head = nod;
    }
    return head; 
}

void output(LinkList head, int ind) {
    Node *tmp = head, *q;
    head = NULL;
    while (tmp->next != tmp) {
        for (int i = 0;i < ind - 1; i++) {
            tmp = tmp->next;
        }
        q = tmp->next;
        tmp->next = q->next;
        cout << q->data << " " ;
        free(q);
    }
    cout << tmp->data << endl;
    free(tmp);
}

int main() {
    LinkList head = NULL;
    int m;
    cin >> m;
    for (int i = 1; i < 10; i++) {
        Node *nod = (Node*)malloc(sizeof(Node));
        nod->data = i;
        nod->next = NULL;
        head = insert(head, nod, i - 1);
    }
    output(head, m);
    return 0;
}


