// Copyright (C) 2013 ~ 2014 Leslie Zhai <xiangzhai83@gmail.com>

#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>

#include "quick_sort.h"

typedef std::vector<int>                            IntList;
typedef std::map<int, IntList>                      BinMap; 
typedef std::map<int, IntList>::reverse_iterator    BinMapRIter;

void radix_sort(IntList & list, int bit)
{
    BinMap binList;
    BinMapRIter iter;
    int i;
    for (i = 0; i < list.size(); i++) {
        int bitIndex = list[i] / bit % 10;
        (binList[bitIndex]).push_back(list[i]);
    }
    for (iter = binList.rbegin(), i = 0; 
         iter != binList.rend(); 
         iter++, i++) {
        //printf("DEBUG: BIT %d\n", (*iter).first);
        quick_sort((*iter).second, 0, (*iter).second.size() - 1);
        for (int j = 0; j < (*iter).second.size(); j++, i++) {
            if (i >= list.size()) 
                continue;
            list[i] = (*iter).second[j];
            //printf("%d\t", (*iter).second[j]);
        }
        //printf("\n");
    }
    if (binList.size() == 1) 
        return;
    radix_sort(list, bit * 10);
}

int main(int argc, char* argv[]) 
{
    IntList numList;
    for (int i = 0; i < 1024; i++) {
        numList.push_back(rand() % 1000);
    }
    printf("DEBUG: ");
    for (int i = 0; i < numList.size(); i++) {
        printf("%d\t", numList[i]);
    }
    printf("\n\n");
    radix_sort(numList, 1);
    printf("\nSORT: ");
    for (int i = 0; i < numList.size(); i++) {
        printf("%d\t", numList[i]);
    }
    printf("\n");
    return 0;
}
