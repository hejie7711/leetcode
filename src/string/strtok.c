/* Copyright (C) 2014 Leslie Zhai <xiangzhai83@gmail.com> */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define BUF_SIZE 80

static char *m_oldstr = NULL;

char *LeslieStrTok(char *str, char *delim) 
{
    char*   s       = NULL;
    char*   token   = NULL;
    char*   d       = NULL;
    int     n       = 0;

    if (str != NULL) 
        m_oldstr = str;

    if (*m_oldstr == '\0') 
        return NULL;

    s = m_oldstr;

    /* FIXME: Mr.Cleanup */
    token = malloc(BUF_SIZE);
    assert(token);

    while (*m_oldstr != '\0') {
        d = delim;
        while (*d != '\0') {
            if (*m_oldstr == *d) {
                m_oldstr++;
                strncpy(token, s, n);
                return token;
            }
            d++;
        }
        m_oldstr++;
        n++;
    }

    return s;
}

int main(int argc, char *argv[]) 
{
    char str[BUF_SIZE] = {'\0'};
    char delim[3] = ",|";
    char *token = NULL;
    if (argv[1]) 
        snprintf(str, BUF_SIZE, argv[1]);
    else 
        snprintf(str, BUF_SIZE, "hello|world,leslie,zhai");
    printf("strtok %s with %s\n", str, delim);
#if 0
    token = strtok(str, delim);
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, delim);
    }
#endif
    token = LeslieStrTok(str, delim);
    while (token != NULL) {
        printf("%s\n", token);
        token = LeslieStrTok(NULL, delim);
    }
    return 0;
}
