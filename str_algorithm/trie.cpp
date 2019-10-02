/*************************************************************************
	> File Name: trie.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年08月19日 星期一 19时11分52秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define BASE 26
#define BASE_LETTER 'a'

typedef struct Node {
    int flag;
    struct Node *next[BASE];
}Node;

typedef struct DANode {
    int base, check;
} DANode;

int cnt = 0;


DANode *getDANode(int cnt) {
    DANode *arr = (DANode*) calloc (sizeof(DANode), cnt);
    return arr;
}

Node *getNewNode() {
    cnt += 1;
    Node *p = (Node*) calloc(sizeof(Node), 1);
    return p;
}

void clear(Node *root) {
    if (root == NULL) return  ;
    for (int i = 0; i < BASE; i++) {
        clear(root->next[i]);
    }
    free(root);
    return ;
}

inline int code(char ch) {
    return ch - BASE_LETTER;
}

void output(Node *root, int k ,char *buff) {
    if (root == NULL) return ;
    if (root->flag) printf("%s\n", buff);
    for (int i = 0; i < BASE; i++) {
        buff[k] = BASE_LETTER + i;
        buff[k+1] = '\0';
        output(root->next[i], k + 1, buff);
    }
    return; 
}

void insert(Node *root, char *str) {
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        if (p->next[code(str[i])] == NULL) p->next[code(str[i])] = getNewNode();
        p = p->next[code(str[i])];
    }
    p->flag = 1;
    return ;
}

int query(Node *root, char *str) {
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        p = p->next[code(str[i])];
        if (p == NULL) return 0;
    }
    return p->flag;
}

int getBaseValue(Node *root, DANode *darr) {
    int base = 2;
    while (1) {
        int flag = 1;
        for (int i = 0; i < BASE; i++) {
            if (root->next[i] == NULL) continue;
            if (darr[base + i].check == 0) continue;
            flag = 0;
            break;
        }
        if (flag) return base;
        base += 1;
    }
    return base;
}

void trans_to_darr(Node *root, int ind, DANode *darr) {
    darr[ind].base = getBaseValue(root, darr);
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) continue;
        darr[darr[ind].base + i].check = ind * (root->next[i]->flag ? -1 : 1);
    } 
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) continue;
        trans_to_darr(root->next[i], darr[ind].base + i, darr);
    }
    return ;
}

int output_darr(int ind, int k, DANode *darr, char *buff) {
    if (darr[ind].check < 0) {
        printf("%s\n", buff);
    } 
    for (int i = 0; i < BASE; i++) {
        if (abs(darr[darr[ind].base + i].check) != ind) continue;
        buff[k] = BASE_LETTER + i;
        buff[k + 1] = '\0';
        output_darr(darr[ind].base+i, k + 1, darr, buff);
    }    
    
}

int main() {
    char str[1000];
    int n, m;
    Node *root = getNewNode();
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        insert(root, str);
    }
    DANode *darr = getDANode(cnt * 26 + 100);    
    trans_to_darr(root, 1, darr);
    output_darr(1, 0, darr, str);
    printf("\n[trie] : \n");
    output(root, 0, str);
    for (int i = 0; i < m; i++) {
        scanf("%s", str);
        printf("query %s, result = %s\n",str,  query(root, str) == 1?"YES":"NO");
    }

    return 0;
}

