/*************************************************************************
	> File Name: red_black_tree.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年09月24日 星期二 11时27分50秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define RED_COLOR 0
#define BLACK_COLOR 1
#define DOUBLE_BLACK 2

typedef struct Node {
    int color, key;
    struct Node *lchild, *rchild;
}Node;

Node __NIL;
#define NIL (&__NIL)

__attribute__((constructor))
void init_NIL() {
    NIL->key = 0;
    NIL->lchild = NIL->rchild = NIL;
    NIL->color = BLACK_COLOR;
}

Node *getNewNode(int key) {
    Node *p = (Node*) malloc (sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NIL;
    p->color = RED_COLOR;
    return p;
}

int has_red_child(Node *root) {
    return root->lchild->color == RED_COLOR || root->rchild->color == RED_COLOR;
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

Node *insert_maintain(Node *root) {
    #define INSERT_MAIN ({root->color = RED_COLOR; root->lchild->color = root->rchild->color = BLACK_COLOR; return root;})
    if (!has_red_child(root)) {
        return root;
    }
    if (root->lchild->color == RED_COLOR && root->rchild->color == RED_COLOR) {
        if (!has_red_child(root->lchild) && !has_red_child(root->rchild)) return root;
        INSERT_MAIN;
    }
    if (root->lchild->color == RED_COLOR && has_red_child(root->lchild)) {
        if (root->lchild->rchild->color == RED_COLOR) {
            root->lchild = left_rotate(root->lchild);
        } 
        root = right_rotate(root);
    } else if (root->rchild->color == RED_COLOR && has_red_child(root->rchild)) {
        if (root->rchild->lchild->color == RED_COLOR) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    } else {
        return root;
    }
    INSERT_MAIN;
}

Node *__insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (root->key == key) return root;
    if (root->key > key) root->lchild = __insert(root->lchild, key);
    else root->rchild = __insert(root->rchild, key);
    return insert_maintain(root);
}

Node *insert(Node *root, int val) {
    root = __insert(root, val);
    root->color = BLACK_COLOR;
    return root;
}

Node *predecessor(Node *root) {
    Node *p = root->lchild;
    while (p->rchild != NIL) {
        p = p->rchild;
    }
    return p;
}

Node *erase_maintain(Node *root) {
    #define ERASE_MAIN ({root->color += 1; root->lchild->color -= 1; root->rchild->color -= 1; return root; })
    if (root->lchild->color != DOUBLE_BLACK && root->rchild->color != DOUBLE_BLACK) {
        return root;
    }
    if (has_red_child(root)) {
        Node *tmp = root;
        root->color = RED_COLOR;
        if (root->lchild->color == RED_COLOR) {
            root = right_rotate(root);
        } else {
            root = left_rotate(root);
        }
        root->color = BLACK_COLOR;
        if (tmp == root->lchild) root->lchild = erase_maintain(root->lchild);
        else root->rchild = erase_maintain(root->rchild);
        return root;
    }
    if (root->lchild->color == BLACK_COLOR) {
        if (!has_red_child(root->lchild))  {
            ERASE_MAIN;
        }
        if (root->lchild->lchild->color != RED_COLOR) {
            root->lchild->color = RED_COLOR;
            root->lchild = left_rotate(root->lchild);
            root->lchild->color = BLACK_COLOR;
        }
        root->rchild->color -= 1;
        root = right_rotate(root);
        root->color = root->rchild->color;
        root->lchild->color = root->rchild->color = BLACK_COLOR;
    } else {
        if (!has_red_child(root->rchild))  {
            ERASE_MAIN;
        }
        if (root->rchild->rchild->color != RED_COLOR) {
            root->rchild->color = RED_COLOR;
            root->rchild = right_rotate(root->rchild);
            root->rchild->color = BLACK_COLOR;
        } 
        root->lchild->color -= 1;
        root = left_rotate(root);
        root->color = root->rchild->color;
        root->lchild->color = root->rchild->color = BLACK_COLOR;
    }
    return root; 
}

Node *__erase(Node *root, int key) {
    if (root == NIL) return root;
    if (root->key > key) root->lchild = __erase(root->lchild, key);
    else if (root->key < key) root->rchild = __erase(root->rchild, key);
    else {
        if (root->lchild == NIL || root->rchild == NIL) {
            Node *p = root->lchild == NIL ? root->rchild : root->lchild;
            p->color += root->color;
            free(root);
            return p;
        }
        Node *tmp = predecessor(root);
        root->key = tmp->key;
        root->lchild = __erase(root->lchild, tmp->key);
    }
    return erase_maintain(root);
}


Node *erase(Node *root, int val) {
    root = __erase(root, val);
    root->color = BLACK_COLOR;
    return root;
}

void output(Node *root) {
    if (root == NIL) return ;
    output(root->lchild);
    printf("%d %d %d %d\n", root->key, root->color, root->lchild->key, root->rchild->key);
    output(root->rchild);
}

int main() {
    int op, val;
    Node *root = NIL;
    while (~scanf("%d%d", &op, &val)) {
        switch(op) {
            case 1: {
                root = insert(root, val);
            }break;
            case 2: {
                root = erase(root, val);
            }break;
            case 3: {
                output(root);
            }break;
        }
    }
    
    return 0;
}

