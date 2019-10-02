/*************************************************************************
	> File Name: 1.vector.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年06月30日 星期日 15时18分05秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <string.h>
#include <time.h>
using namespace std;

typedef struct Vector {
    int *data;
    int size, length;
} Vector;

//#define init(n) ((#n)[0]?__init(n+0):__init(10))
#define default_value(n,val) ((#n)[0] ? n+0 : val)
#define init(n) __init(default_value(n, 10))

Vector *__init(int n) {
    Vector *vec = (Vector*) malloc (sizeof(Vector));
    vec->data = (int *)malloc (sizeof(int ) * n);
    vec->length = 0;
    vec->size = n;

    return vec;
}

int expand(Vector * vec) {
    int new_size = vec->size * 2;
    //realloc 失败返回NULL，原空间不会释放, 注意防止指针覆盖
    int *p =(int *)realloc(vec->data, sizeof(int) * new_size);
    if(p == NULL) return 0;
    vec->size = new_size;
    vec->data = p;
    printf("expand Vector to size %d\n", vec->size);
    return 1;
}

int insert(Vector *vec, int ind, int val) {
    if (vec == NULL) return 0;
    if (ind < 0 || ind > vec->length) return 0;
    if (vec->length >= vec->size) {
        if (!expand(vec)) {
            return 0;
        }
    }
    for (int i = vec->length; i > ind; i--) {
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[ind] = val;
    vec->length += 1;

    return 1;
}

int erase(Vector *vec, int ind){
    if (vec == NULL) return 0;
    if (ind < 0 || ind >= vec->length) return 0;
    if (vec->length == 0) return 0;
    for (int i = ind + 1; i < vec->length; i++) {
        vec->data[i-1] = vec->data[i];
    }
    vec->length -= 1;
    return 1;
}

void clear(Vector *vec) {
    if (vec == NULL) return ;
    free(vec->data);
    free(vec);
    return ;
}

int find(Vector *vec, int val) {
    if (vec == NULL) return -1;
    for( int i = 0; i < vec->length; i++) {
        if (vec->data[i] == val) return i;
    }
    return -1;
}

void output_ind(Vector *vec, int ind) {
    int cnt = 0;
    cnt += printf("arr(%d) = [", vec->length);
    int unt = cnt;
    for (int i = 0; i < vec->length; i++) {
        if (i > 0) {
            if (i <= ind)
                cnt += printf(", ");
            else 
                printf(", ");
        }
        
        int k = printf("%d", vec->data[i]);
        if (i <= ind) cnt += k;
    }
    printf("]\n");
    if (ind == -1) cnt = unt;
    for(int i = 0; i < cnt; i++) {
        if (i != cnt - 1) printf(" ");
        else printf("^");
    }
    printf("\n");
    for(int i = 0; i < cnt; i++) {
        if (i != cnt - 1) printf(" ");
        else printf("|");
    }
    printf("\n");
    return;

}

void output(Vector *vec) {
    printf("arr(%d) = [", vec->length);
    for (int i = 0; i < vec->length; i++) {
        if (i > 0) printf(", ");
        printf("%d", vec->data[i]);
    }
    printf("]\n");
    return;
}

int main() {
    srand(time(0));
    #define MAX_N 20
    Vector *vec = init();
    int op, ind, val;
    for (int i = 0; i < MAX_N; i++) {
        op = rand() % 4;
        ind = rand() % (vec->length + 3) - 1;
        val = rand() % 100;
        switch(op) {
            case 0:
            case 1:
            case 2:{
                printf("insert %d at %d to Vector = %d\n", val, ind, insert(vec, ind, val));
                output(vec);
            }break;
            case 3: {
                printf("erase item at %d from Vector = %d\n", ind, erase(vec, ind));
                output;
            }break;
        }
        printf("\n");
    }
    int c;
    while (~scanf("%d", &c)) {
        output_ind(vec, find(vec, c));
    }
    return 0;
}


