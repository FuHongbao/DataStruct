/*************************************************************************
	> File Name: huffman.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年09月09日 星期一 15时43分13秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_N 1000
#define  swap(a, b) {\
    __typeof(a) _temp = a;\
    a = b; b = _temp;\
}

typedef struct Node {
    char ch;
    double p;
    struct Node *next[2];
} Node;

typedef struct Data {
    char ch;
    double p;
} Data;

typedef struct Code {
    char ch;
    char *str;
}Code;

typedef struct HuffmanTree {
    Node *root;
    int n;//多少种字符
    Code *codes;
} HuffmanTree;

Data arr[MAX_N + 5];

Node *getNewNode(Data *obj) {
    Node *p = (Node*) malloc (sizeof(Node));
    p->ch = (obj ? obj->ch : 0);
    p->p = (obj ? obj->p : 0);
    p->next[0] = p->next[1] = NULL;
    return p;
}

HuffmanTree *getNewTree(int n) {
    HuffmanTree *tree = (HuffmanTree*) malloc (sizeof(HuffmanTree));
    tree->root = NULL;
    tree->n = n;
    tree->codes = (Code*) malloc (sizeof(Code) * n);
    return tree;
}

int extract(Node *root, Code *arr, int k, int deep, char *buff) {
    buff[deep] = 0;
    if (root->next[0] == NULL && root->next[1] == NULL) {
        arr[k].ch = root->ch;
        arr[k].str = strdup(buff);
        return 1;
    }
    int delta = 0;
    buff[deep] = '0';
    delta += extract(root->next[0], arr, k, deep + 1, buff);
    buff[deep] = '1';
    delta += extract(root->next[1], arr, k + delta, deep + 1, buff);
    return delta;
}

void insertOnce(Node **arr, int n) {
    for (int j = n; j >= 1; j--) {
        if (arr[j]->p > arr[j - 1]->p) {
            swap(arr[j], arr[j - 1]);
            continue;
        }
        break;
    } 
}

HuffmanTree *build(Data *arr, int n) {
    Node **nodes = (Node**) malloc (sizeof(Node*) * n);
    for (int i = 0; i < n; i++) {
        nodes[i] = getNewNode(arr + i);
    }
    for (int i = 1; i < n; i++){
        insertOnce(nodes, i);
    }

    for (int i = n - 1; i >= 1; i--) {
        Node *p = getNewNode(NULL);
        p->next[1] = nodes[i];
        p->next[0] = nodes[i - 1];
        p->p = p->next[0]->p + p->next[1]->p;
        nodes[i - 1] = p;
        insertOnce(nodes, i - 1);
    }
    HuffmanTree *tree= getNewTree(n);
    tree->root = nodes[0];
    char *buff = (char*) malloc(sizeof(char) * n);
    extract(tree->root, tree->codes, 0, 0, buff);
    free(buff); 
    free(nodes);
    return tree;
}

int main() {
    int n;
    char str[10];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s%lf", str, &arr[i].p);
        arr[i].ch = str[0];
    }
    HuffmanTree *tree = build(arr, n);
    for (int i = 0; i < tree->n; i++) {
        printf("%c : %s\n", tree->codes[i].ch, tree->codes[i].str);
    }
    return 0;
}


