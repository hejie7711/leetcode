/* Copyright (C) 2014 Leslie Zhai <xiangzhai83@gmail.com> */

#include <stdio.h>
#include <string.h>

#define BUF_SIZE 80

char* LeslieStrcpy(char* dest, char* src) 
{
    while ((*dest++ = *src++) != '\0');

    return dest;
}

char* LeslieStrncpy(char* dest, char* src, size_t n) 
{
    while (n--) 
        *dest++ = *src++;

    return dest;
}

int main(int argc, char *argv[]) 
{
    char buf[BUF_SIZE] = {'\0'};

#if 0    
    strncpy(buf, "hello", BUF_SIZE);
#endif

    LeslieStrcpy(buf, "world");
#if 0
    LeslieStrncpy(buf, "hello", 3);
#endif
    printf("%s\n", buf);
    
    return 0;
}
