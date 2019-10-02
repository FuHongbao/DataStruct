/*************************************************************************
	> File Name: str01.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年08月14日 星期三 22时09分21秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEST(func, a, b) {\
    printf("%s(\"%s\",\"%s\") = %d\n", #func, a, b, func(a, b));\
}

int bruteForce(char *str, char *pattern) {
    for (int i = 0; str[i]; i++) {
        int flag = 1;
        for (int j = 0; pattern[j]; j++) {
            if(str[i + j] == pattern[j]) continue;
            flag = 0;
            break;
        }
        if (flag) return i;
    }
    return -1;
}

int Kmp(char *str, char *pattern) {
    int *next = (int*) malloc (sizeof(int) *strlen(pattern));
    next[0] = -1;
    for (int i = 1; pattern[i]; i++) {
        int j = next[i - 1];
        while(j != -1 && pattern[i] != pattern[j + 1]) j = next[j];
        if (pattern[i] == pattern[j + 1]) {
            next[i] = j + 1;
        } else {
            next[i] = -1;
        }
    }
    int i = 0, j = -1;
    while (str[i]) {
        while (j != -1 && str[i] != pattern[j + 1]) j = next[j];
        if (str[i] == pattern[j + 1]) {
            j++;
        }
        i++;
        if (pattern[j + 1] == 0) return i - strlen(pattern);
    }
    return -1;
}

int Sunday(char *str, char *pattern) {
    int ind[128] = {0};
    int len1 = strlen(pattern);
    int len2 = strlen(str);
    for (int i = 0; i < 128; i++) {
        ind[i] = len1 + 1;
    }
    for (int i = 0; i < len1; i++) {
        ind[pattern[i]] = len1 - i;
    }
    for (int i = 0; i < len2 - len1 + 1;) {
        int flag = 1;
        for (int j = 0; j < len1; j++) {
            if (pattern[j] == str[i + j]) continue;
            i += ind[str[i + len1]];
            flag = 0;
            break;
        }
        if (flag) {
            return i;
        }
    }
    return -1;
}

int shift_and(char *str, char *pattern) {
    int codes[128] = {0};
    int len = strlen(pattern);
    for (int i = 0; pattern[i]; i++) {
        codes[pattern[i]] |= (1 << i);
    }
    int p = 0;
    for (int i = 0; str[i]; i++) {
        p = (p << 1 | 1) & codes[str[i]];
        if (p & (1 << (len - 1))) {
            return i - len + 1;
        }
    }
    return -1;
}


int main() {
    char str[1024];
    char pattern[1024];
    while (scanf("%s%s", str, pattern)!= EOF) {
        getchar();
        TEST(bruteForce, str, pattern);
        TEST(Kmp, str, pattern);
        TEST(Sunday, str, pattern);
        TEST(shift_and, str, pattern);
    }

    return 0;
}
