#include <stdio.h>
#include <stdlib.h>

#define STRING_NUM 7
#define STRING_LENGTH 128

extern void strsort(char** strs, int n);

int main() {
    char* strs[STRING_NUM];
    int i;
    for (i = 0; i < STRING_NUM; i++) {
        strs[i] = (char*)malloc(sizeof(char) * STRING_LENGTH);
    }

    for (i = 0; i < STRING_NUM; i++) {
        scanf("%s", strs[i]);
    }

    strsort(strs, STRING_NUM);
    
    for (i = 0; i < STRING_NUM; i++) {
        printf("%s\n", strs[i]);
    }
}