/* Copyright (C) 2014 Leslie Zhai <xiangzhai83@gmail.com> */

#include <stdio.h>
#include <string.h>

static char *LeslieStrTok(char *str, char *delim);

int main(int argc, char *argv[]) 
{
    char str[80] = {0};
    char delim[3] = " ,";
    char *token = NULL;
    if (argv[1]) 
        snprintf(str, 80, argv[1]);
    else 
        snprintf(str, 80, "hello, world, leslie, zhai");
    printf("strtok %s with %s\n", str, delim);
    token = strtok(str, delim);
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, delim);
    }
    return 0;
}
