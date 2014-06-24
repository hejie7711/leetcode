/* Copyright (C) 2013 ~ 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <stdio.h>
#include <string.h>
#include <assert.h>

void rotate(char *str, int m) 
{
    char *p1 = NULL, *p2 = NULL;
    assert(str != NULL);
    assert(m < strlen(str));
    p2 = p1 = str;
    while (m--) p2++;
    while (*p1 && *p2) {
        char tmp = 0;
        tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2++;
    }
}

int main(int argc, char *argv[]) 
{
    char str[10] = "abcdefghi";
    rotate(str, 3);
    printf("ROTATE: %s\n", str);
    return 0;
}
