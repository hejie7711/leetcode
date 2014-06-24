// Copyright (C) 2013 ~ 2014 Leslie Zhai <xiangzhai83@gmail.com>

#include <stdio.h>
#include <stdlib.h>

#include "quick_sort.h"

static int partition(IntList & list, int left, int right)
{
    int index = left;
    int pivot = list[index];
    // put pivot to the end
    std::swap(list[index], list[right]);
    for (int i = left; i < right; i++) {
        if (list[i] >= pivot) 
            std::swap(list[index++], list[i]);
    }
    // get pivot back
    std::swap(list[right], list[index]);
    return index;
}
 
void quick_sort(IntList & list, int left, int right)
{
    if (left >= right) 
        return;
    int index = partition(list, left, right);
    quick_sort(list, left, index - 1);
    quick_sort(list, index + 1, right);
}
