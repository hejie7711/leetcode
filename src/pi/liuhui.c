/* Copyright (C) 2013 ~ 2014 Leslie Zhai <xiangzhai83@gmail.com> */

#include <stdio.h>
#include <math.h>

int liuhui(int n)
{
    int i;
    double k, y2;
    for (i = 0, k = 3.0, y2 = 1.0; i < n; ++i, k *= 2.0) {
        printf("sides = %d\tpi(%d) = %.51f\n", 3 * (1 << i), i, k * sqrt(y2));
        y2 = 2 - sqrt(4 - y2);
    }

    return i;
}

int main(int argc, char *argv[])
{
    printf("%.51f\n",
           sqrt(2 - sqrt(2 + sqrt(2 + sqrt(2 + sqrt(2 + 1))))) * 48.0);
    printf("DEBUG: %d\n", liuhui(17));
    return 0;
}
