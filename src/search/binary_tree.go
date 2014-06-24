/* Copyright (C) 2013 ~ 2014 Leslie Zhai <xiangzhai83@gmail.com> */

package main

import (
    "fmt"
    "os"
    "strconv"
    "math/rand"
)

type node_t struct {
    item    int
    left    *node_t
    right   *node_t
}

func insert(key int, leaf **node_t) {
    if (*leaf == nil) {
        *leaf = new(node_t)
        (*leaf).item   = key
        (*leaf).left   = nil
        (*leaf).right  = nil
    } else if (key < (*leaf).item) {
        insert(key, &(*leaf).left)
    } else if (key > (*leaf).item) {
        insert(key, &(*leaf).right)
    }
}

func search(key int, leaf *node_t) *node_t {
    if (leaf != nil) {
        if (key == leaf.item) {
            return leaf
        } else if (key < leaf.item) {
            return search(key, leaf.left)
        } else {
            return search(key, leaf.right)
        }
    }
    return nil
}

func travel_tree(leaf *node_t) {
    if (leaf != nil) {
        fmt.Printf("%d\t", leaf.item)
        travel_tree(leaf.left)
        travel_tree(leaf.right)
    }
}

func main() {
    var root *node_t    = nil
    key                 := 67;
    if len(os.Args) > 1 {
        key, _ = strconv.Atoi(os.Args[1])
    }
    for i := 0; i < 1024; i++ {
        insert(rand.Intn(100), &root)
    }
    travel_tree(root)
    fmt.Println()
    fmt.Printf("search %d %v\n", key, search(key, root))
}
