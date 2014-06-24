// Copyright (C) Leslie Zhai <xiangzhai83@gmail.com>

#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

typedef std::vector<int> RandNumList;

static void binary_search(RandNumList list, int low, int high, int key) 
{
    int mid = (high + low) / 2;
    if (low > high || mid <= low || mid >= high) 
        return;
    if (key == list[mid]) {
        printf("Found %d at %d\n", key, mid);
        return;
    }
    if (key < list[mid]) 
        binary_search(list, low, mid, key);
    else 
        binary_search(list, mid, high, key);
}

int main(int argc, char* argv[]) 
{
    RandNumList numList;
    for (int i = 0; i < 1024; i++) {
        numList.push_back(rand() % 100);
    }
    std::sort(numList.begin(), numList.end());
    printf("DEBUG: ");
    for (int i = 0; i < numList.size(); i++) {
        printf("%d\t", numList[i]);
    }
    printf("\n");
    binary_search(numList, 0, numList.size() - 1, argv[1] ? atoi(argv[1]) : 67);
    return 0;
}
