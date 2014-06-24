// Copyright (C) 2013 ~ 2014 Leslie Zhai <xiangzhai83@gmail.com>

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

#include "bigint/BigIntegerLibrary.hh"

#define BUF_SIZE    64
#define STRA_SIZE   16
#define STRB_SIZE   8

typedef std::vector<int> IntList;

static IntList primeList;

const int primeNum[] = {2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,  
                        37,  41,  43,  47,  53,  59,  61,  67,  71,  73,  79,
                        83,  89,  97,  101, 103, 107, 109, 113, 127, 131, 137,
                        139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193,
                        197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257,
                        263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317,
                        331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 
                        397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457,
                        461, 463, 467, 479, 487, 491};

bool isPrime(int num) 
{
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) 
            return false;
    }
    return true;
}

static void findPrime() 
{
    int i, j;
    printf("DEBUG: ");
    for (i = 2, j = 0; i < 997 && j < 94; i++) {
        if (!isPrime(i)) 
            continue;
        printf("%d\t", i);
        j++;
    }
    printf("\n");
}

static int m_rand() 
{
    int fd = open("/dev/urandom", O_RDONLY);
    char buf[BUF_SIZE] = {'\0'};
    int ret = 0;
    read(fd, buf, BUF_SIZE);
    close(fd);
    for (int i = 0; i < BUF_SIZE; i++) {
        ret += abs(buf[i]);
    }
    return ret;
}

int main(int argc, char *argv[]) 
{
    char strA[STRA_SIZE] = {'\0'};
    char strB[STRB_SIZE] = {'\0'};
    BigInteger product = 1;
    int i;
    //findPrime();
    for (i = 0; i < STRA_SIZE - 1; i++) {
        int randNum = m_rand() % 93 + 33;
        strA[i] = randNum;
    }
    printf("strA: %s\n", strA);
    for (i = 0; i < STRB_SIZE - 1; i++) {
        int randNum = m_rand() % 93 + 33;
        strB[i] = randNum;
    }
    printf("strB: %s\n", strB);
    for (i = 0; i < STRA_SIZE; i++) {
        int index = strA[i] - '!';
        product *= primeNum[index];
    }
    std::cout << product << std::endl;
    try {
        for (i = 0; i < STRB_SIZE; i++) {
            int index = strB[i] - '!';
            if (product % primeNum[index] != 0)
                break;
        }
    } catch (const char *e) {
        std::cout << e << std::endl;
    }
    printf("DEBUG: %d\n", i);
    return 0;
}
