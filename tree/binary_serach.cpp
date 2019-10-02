/*************************************************************************
	> File Name: binary_serach.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年09月17日 星期二 18时49分19秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *lchild, *rchild;
}Node;

Node *getNewNode(int key) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NULL;
    return p;
}

Node *insert(Node *root, int val) {
    if (root == NULL) return getNewNode(val);
    if (root->key == val) return root;
    if (val < root->key) root->lchild = insert(root->lchild, val);
    else root->rchild = insert(root->rchild, val);
    return root;
}

Node *predecessor(Node *root) {
    Node *p = root->lchild;
    while(p->rchild) {
        p = p->rchild;
    }
    return p;
}

Node *erase(Node *root, int val) {
    if( root == NULL ) return root;
    if (val < root->key) root->lchild = erase(root->lchild, val);
    else if (val > root->key) root->rchild = erase(root->rchild, val);
    else {
        if (root->lchild == NULL || root->rchild == NULL) {
            Node *tmp = (root->lchild ? root->lchild : root->rchild);
            free(root);
            return tmp;
        } 
        Node *p = predecessor(root);
        root->key = p->key;
        root->lchild = erase(root->lchild, p->key);
    }
   return root; 
}

void clear(Node *root) {
    if (root == NULL) return;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return;
}

void __inorder_output(Node *root) {
    if( root == NULL ) return ;
    __inorder_output(root->lchild);
    printf("%d ", root->key);
    __inorder_output(root->rchild);
} 

void inorder_output(Node *root) {
    printf("中序遍历 : ");
    __inorder_output(root);
    printf("\n");
}

int main() {
    int op, val;
    Node *root = NULL;
    while(~scanf("%d%d", &op, &val)) {
        switch(op) {
            case 1: {
                root = insert(root, val);
            }break;
            case 2: {
                root = erase(root, val);
            }break;
        }
        inorder_output(root);
    }
    clear(root); 
    return 0;
}

