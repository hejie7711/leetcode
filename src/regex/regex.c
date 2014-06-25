/* Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <stdio.h>
#include <regex.h>

typedef enum {
    FALSE, 
    TRUE
} BOOL;

/* glibc regex */
BOOL isMatch(const char *s, const char *p) 
{
    regex_t r;
    /* 
     * http://www.gnu.org/software/libc/manual/html_node/Flags-for-POSIX-Regexps.html#Flags-for-POSIX-Regexps 
     */
    if (regcomp(&r, p, REG_EXTENDED | REG_NOSUB) != 0) {
        printf("ERROR: fail to regcomp!\n");
        return FALSE;
    }
    if (regexec(&r, s, 0, NULL, REG_NOTBOL) != 0) {
        regfree(&r); 
        return FALSE;
    }
    printf("DEBUG: Mr. Match\n");
    regfree(&r);
    return TRUE;
}

BOOL LeslieMatch(const char *s, const char *p) { return TRUE; }

int main(int argc, char *argv[]) 
{
    isMatch("aa", ".*");
    return 0;
}
