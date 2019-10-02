/*************************************************************************
	> File Name: 2.linklist.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年06月30日 星期日 18时51分08秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;

typedef struct LinkListNode {
    int data;
    struct LinkListNode *next;
} LinkListNode;

typedef struct LinkList {
    LinkListNode head;
    int length;
}LinkList;
    
LinkListNode *init_listnode(int val) {
    LinkListNode *p = (LinkListNode*) malloc(sizeof(LinkListNode));
    p->data = val;
    p->next = NULL;
    return p;
}

LinkList *init_list() {
    LinkList *l = (LinkList*)malloc (sizeof(LinkList));
    l->head.next = NULL;
    l->length = 0;
    return l;
}

int insert(LinkList *l, int ind, int val) {
    if (l == NULL) return 0;
    if (ind < 0 || ind >l->length) return 0;
    LinkListNode *p = &(l->head), *node = init_listnode(val);
    while(ind --) {
        p = p->next;
    }
    node->next = p->next;
    p->next = node;
    l->length += 1;
    return 1;
}
void clear_listnode(LinkListNode *node);
int erase(LinkList *l, int ind) {
    if (l == NULL) return 0;
    if (ind < 0 || ind >= l->length) return 0; //有等于
    LinkListNode *p = &(l->head), *q;
    while(ind--) {
        p = p->next ;
    }
    q = p->next;
    p->next = q->next;
    clear_listnode(q);
    l->length -= 1;
    return 1;
}

void clear_listnode(LinkListNode *node) {
    if(node == NULL) return;
    free(node);
    return ;
}

void clear_linklist(LinkList *l) {
    if(l == NULL) return ;
    LinkListNode *p = l->head.next, *q;
    while (p) {
        q = p->next;
        clear_listnode(p);
        p = q;
    }
    free(l);
    return ;
}
void output(LinkList *l) {
    printf("LinkList(%d) : ",l->length);
    LinkListNode *p = l->head.next;
    while(p != NULL) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
    return ;
}
    
int main() {
    #define MAX_N 20
    srand(time(0));
    LinkList *l = init_list();

    for(int i = 0; i < MAX_N ; i++) {
        int op = rand() % 3;
        int ind = rand() % (l->length + 1);
        int val = rand() % 100;
        switch(op) {
            case 0:
            case 1:{
                printf("insert %d at %d to LinkList = %d \n", val ,ind, insert(l, ind, val));
            }
            break;
            case 2:{
                printf("erase item at %d from LinkList = %d\n", ind, erase(l, ind));
            }break;
        }
        output(l);
        printf("\n");
    }
    
    
    
    return 0;
}


