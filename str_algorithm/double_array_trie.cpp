/*************************************************************************
	> File Name: double_array_trie.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年08月21日 星期三 14时15分01秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BASE 26
#define BEGIN_LETTER 'a'


typedef struct Node {
    int flag;
    struct Node *next[BASE];
} Node;

typedef struct DATrie {
    int *base, *check;
    int root, size;
}DATrie;

DATrie *getDATrie(int n) {
    DATrie *tree  = (DATrie *) calloc (sizeof(DATrie), 1);
    tree->root = 1;
    tree->size = n;
    tree->base = (int *) calloc (sizeof(int), n);
    tree->check = (int*) calloc (sizeof(int), n);
    tree->check[tree->root] = 1;
    return tree;
}

int getBaseValue(Node *root, DATrie *tree) {
    int base = 1, flag = 1;
    do {
        flag = 1;
        base += 1;
        for (int i = 0; i < BASE; i++) {
            if (root->next[i] == NULL) continue;
            if (tree->check[base + i] == 0) continue;
            flag = 0;
            break;
        }
    } while(!flag);
    return base; 
}

//返回占用最大下标编号
int build_DATrie(int ind, Node *root, DATrie *tree) {
    int base = tree->base[ind] = getBaseValue(root, tree);
    int maxind = ind;
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) continue;
        tree->check[base + i] = ind;
    }
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) continue;
        int temp = build_DATrie(base + i, root->next[i], tree);
        if (temp > maxind) maxind = temp;
    }
    if (root->flag) tree->check[ind] = -tree->check[ind];
    return maxind;
}

void clearDA(DATrie *tree) {
    if (tree == NULL) return ;
    free(tree->base);
    free(tree->check);
    free(tree);
    return;
}

Node *getNewNode() {
    Node *p = (Node*) calloc (sizeof(Node), 1);
    return p;
}

int insert(Node *root, const char *str) {
    int cnt = 0;
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        int ind = str[i] - BEGIN_LETTER;
        if (p->next[ind] == NULL) p->next[ind] = getNewNode(), cnt++;
        p = p->next[ind];
    }
    p->flag = 1;
    return cnt;
}

void clear(Node *root) {
    if (root == NULL) return;
    for (int i = 0; i < BASE; i++) {
        clear(root->next[i]);
    }
    free(root);
}

int query(DATrie *tree, const char *str) {
    int p = tree->root;
    for (int i = 0; str[i]; i++) {
        int ind = str[i] - BEGIN_LETTER;
        if (abs(tree->check[tree->base[p] + ind]) != p) return 0;
        p = tree->base[p] + ind;
    }
    return tree->check[p] < 0;
}

int main() {
    int n, cnt = 1;
    char str[1000];
    scanf("%d", &n);
    Node *root = getNewNode();
    while (n--) {
        scanf("%s", str);
        cnt += insert(root, str);
    }
    DATrie *tree = getDATrie(cnt * BASE + 5);
    int doublecnt = build_DATrie(tree->root, root, tree) + 1;
    while (~scanf("%s", str)) {
        printf("search %s, result = %s\n", str, query(tree, str) ? "YES" : "NO");
    }
    int mem1 = cnt * sizeof(Node);
    int mem2 = doublecnt * sizeof(int) * 2 + sizeof(int) * 2;
    printf("Trie memory : %d Bytes\n", mem1);
    printf("Double Array Trie memory : %d Bytes\n", mem2);
    printf("memory rate: %.4lf\n", (double)(1.0 * mem1 / mem2));
    clearDA(tree); 
    clear(root);
    return 0;
}

