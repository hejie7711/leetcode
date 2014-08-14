/* Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <stdio.h>

int main(int argc, char *argv[]) 
{
    double a = 323.0;
    int b = 1;
    float c = 124.0f;

    printf("sizeof(a)=%d sizeof(short)=%d a=%g b=%d c=%g\n", 
        sizeof(a), sizeof(short), (short)a, b, c);
    printf("sizeof(a)=%d sizeof(short)=%d a=%g b=%d c=%g\n", 
        sizeof(a), sizeof(short), a, b, c);

    return 0;
}
