// Copyright (C) 2013 ~ 2014 Leslie Zhai <xiangzhai83@gmail.com>

#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef std::vector<std::string> NameList;

static int str2int(char* str) 
{
    int ret = 0;
    int size = strlen(str);
    char* cur = str;
    while (*cur) {
        printf("%d\t", *cur);
        ret += *cur;
        cur++;
        size--;
    }
    printf("\n");
    return ret;
}

static int hash_func(const char* str) 
{
    return str2int((char*)str) % 10;
}

int main(int argc, char* argv[]) 
{
    const char* names[] = {"Sarah Jones", "Tony Balognie", "Tom Katz", 
                           "John Smith", '\0'};
    NameList* nameArray = new NameList[10];
    int i = 0;
    /*
    printf("DEBUG: %d\n", str2int("Sarah Jones"));
    printf("DEBUG: %d\n", str2int("Tony Balognie"));
    printf("DEBUG: %d\n", str2int("John Smith"));
    */
    while (names[i] != '\0') {
        printf("DEBUG: %s\n", names[i]);
        int hashIndex = hash_func(names[i]);
        nameArray[hashIndex].push_back(names[i]);
        i++;
    }
    for (i = 0; i < 10; i++) {
        printf("%d %d\n", i, nameArray[i].size());
    }
    delete [] nameArray;
    return 0;
}
