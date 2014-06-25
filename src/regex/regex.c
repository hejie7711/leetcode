/* Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <stdio.h>
#include <regex.h>
#include <assert.h>

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
    printf("DEBUG: Mr. Match!\n");
    regfree(&r);
    return TRUE;
}

BOOL LeslieMatch(const char *s, const char *p) 
{
    assert(s && p);
    if (*p == '\0') return *s == '\0';
    /* 假设p是.b 那么s最好是ab */
    if (*(p + 1) != '*') {
        assert(*p != '*');
        return ((*p == *s) || (*p == '.' && *s != '\0')) && LeslieMatch(s + 1, p + 1);
    }
    /* 假设p是.* */
    while ((*p == *s) || (*p == '.' && *s != '\0')) {
        if (LeslieMatch(s, p + 2)) return TRUE;
        s++;
    }
    return LeslieMatch(s, p + 2);
}

int main(int argc, char *argv[]) 
{
    printf("DEBUG: %d\n", isMatch("aa", "a"));
    printf("DEBUG: %d\n", isMatch("aa", "aa"));
    printf("DEBUG: %d\n", isMatch("aaa", "aa"));
    printf("DEBUG: %d\n", isMatch("aa", "a*"));
    printf("DEBUG: %d\n", isMatch("aa", ".*"));
    printf("DEBUG: %d\n", isMatch("ab", ".*"));
    printf("DEBUG: %d\n", LeslieMatch("aa", ".*"));
    return 0;
}
