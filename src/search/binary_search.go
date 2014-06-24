/* Copyright (C) 2013 ~ 2014 Leslie Zhai <xiangzhai83@gmail.com> */

package main

import (
    "fmt"
    "os"
    "strconv"
    "math/rand"
    "sort"
)

func binary_search(list []int, low, high, key int) {
    mid := (high + low) / 2
    if (low > high || mid <= low || mid >= high) { return }

    if (key == list[mid]) {
        fmt.Printf("Found %d at %d\n", key, mid)
        return
    }
    if (key < list[mid]) {
        binary_search(list, low, mid, key)
    } else {
        binary_search(list, mid, high, key)
    }
}

func main() {
    numList := []int{}
    for i := 0; i < 1024; i++ {
        numList = append(numList, rand.Intn(100))
    }
    sort.Ints(numList)
    fmt.Printf("DEBUG: ")
    for i := 0; i < len(numList); i++ {
        fmt.Printf("%d\t", numList[i])
    }
    fmt.Printf("\n")
    key := 67
    if len(os.Args) > 1 {
        key, _ = strconv.Atoi(os.Args[1])
    }
    fmt.Println("binary search", key)
    binary_search(numList, 0, len(numList) - 1, key)
}
