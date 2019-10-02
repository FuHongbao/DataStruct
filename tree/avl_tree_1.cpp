/*************************************************************************
	> File Name: avl_tree_1.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年09月19日 星期四 18时05分33秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

typedef struct Node {
    int key, h;
    struct Node *lchild, *rchild;
}Node;

Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL() {
    NIL->h = NIL->key = 0;
    NIL->lchild = NIL->rchild = NIL;
}

Node *getNewNode(int val) {
    Node *p = (Node *) malloc (sizeof(Node));
    p->key = val;
    p->h = 1;
    p->lchild = p->rchild = NIL;
    return p;
}

void cacl_heigth(Node *root) {
    int l = root->lchild->h;
    int r = root->rchild->h;
    root->h = (l > r ? l : r) + 1;
    return ;
}

Node *left_rotate(Node *root) {
    Node *p = root->rchild;
    root->rchild = p->lchild;
    p->lchild = root;
    return p;
}

Node *right_rotate(Node *root) {
    Node *p = root->lchild;
    root->lchild = p->rchild;
    p->rchild = root;
    return p;
}

Node *maintain(Node *root) {
    if (abs(root->lchild->h - root->rchild->h) <= 1) return root;
    if (root->lchild->h > root->rchild->h) {
        if (root->lchild->rchild->h > root->lchild->lchild->h) {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    } else {
        if (root->rchild->lchild->h > root->rchild->rchild->h) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
    return root;
}

Node *insert(Node *root, int val) {
    if( root == NIL )  return getNewNode(val);
    if (root->key == val) return root;
    if (val < root->key) root->lchild = insert(root->lchild, val);
    else root->rchild = insert(root->rchild, val);
    cacl_heigth(root);
    return maintain(root);
}

void clear(Node *root) {
    if (root == NIL) return;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
}

void output(Node *root) {
    if (root == NIL) return;
    output(root->lchild);
    printf("%d (height = %d)-", root->key, root->h);
    output(root->rchild);
}

int main() {
    Node *root = NIL;
    int op, val;
    while (~scanf("%d%d", &op, &val)) {
        switch(op) {
            case 1: {
                root = insert(root, val);
            }break;
            case 2: {
                //root = erase(root, val);
            }break;
        }
            output(root);
            printf("\n");
    }
    clear(root);
    return 0;
}

