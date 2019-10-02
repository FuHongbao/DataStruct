/*************************************************************************
	> File Name: hash_table.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年08月20日 星期二 13时10分13秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
using namespace std;

typedef struct Node {
    char *str;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node **data;
    int size;
} HashTable;

Node *init_node(char *str, Node *head) {
    Node *p = (Node*) malloc (sizeof(Node));
    p->str = strdup(str);
    p->next = head;
    return p;
}

HashTable *init_hash(int n) {
    HashTable *h = (HashTable*) malloc (sizeof(HashTable));
    h->size = n * 2;
    h->data = (Node**) calloc (sizeof(Node*), h->size);
    return h;
}

int BKDRHash(char *str) {
    int seed = 31;
    int hash = 0;
    for (int i = 0; str[i]; i++) {
        hash = hash *seed + str[i];
    }
    return hash & 0x7fffffff;
}

int insert(HashTable * h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    h->data[ind] = init_node(str, h->data[ind]);
    return 1;
} 

int search(HashTable *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    Node *p = h->data[ind];
    while(p && strcmp(p->str, str)) p = p->next;
    return p != NULL;
}

void clear_node(Node *node) {
    if (node == NULL) return ;
    Node *p = node, *q;
    while (p) {
        q = p->next;
        free(p->str);
        free(p);
        p = q;
    }
    return ;
}

void clear_hash(HashTable *h) {
    if (h == NULL) return ;
    for (int i = 0; i < h->size; i++) {
        clear_node(h->data[i]);
    }
    free(h->data);
    free(h);
    return ;
}

int main() {
    int op;
    char str[1000]; 
    HashTable *h = init_hash(100);
    while(scanf("%d%s", &op, str) != EOF) {
        switch (op) {
            case 0: {
                insert(h, str);
                printf("insert %s\n", str);
            }break;
            case 1:{
                int k = search(h, str); 
                printf("result = %d\n", k);
            }break;
        }
    }
    return 0;
}

