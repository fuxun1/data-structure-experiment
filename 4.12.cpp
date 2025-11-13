#include <stdio.h>
#include <string.h>
#define MAX_LEN 100

int main() {
    char str[MAX_LEN], stack[MAX_LEN];
    int top = -1, i = 0;
    // 读入字符串直到'#'
    while ((str[i] = getchar()) != '#') {
        stack[++top] = str[i]; // 入栈
        i++;
    }
    str[i] = '\0'; // 字符串结束符
    int mid = i / 2;
    for (int j = 0; j < mid; j++) {
        if (stack[top--] != str[j]) {
            printf("不是回文\n");
            return 0;
        }
    }
    printf("是回文\n");
    return 0;
}