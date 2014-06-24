/* Copyright (C) 2013 ~ 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

package main

import (
    "fmt"
)

type node_t struct {
    Item interface{}
    next *node_t
}

type linked_list_t struct {
    Size int
    head *node_t
}

func NewLinkedList() *linked_list_t {
    return &linked_list_t{Size: 0, head: nil}
}

func (this *linked_list_t) InsertItem(item interface{}) {
    n := &node_t{Item: item, next: this.head}
    this.Size++;
    this.head = n;
}

func (this *linked_list_t) DeleteItem(item interface{}) {
    cur     := this.head
    prev    := cur
    for ; cur != nil; cur = cur.next {
        if item == cur.Item {
            if cur == this.head {
                this.head = cur.next
            } else {
                prev.next = cur.next
            }
            fmt.Printf("DEBUG: delete item 0x%08x %d\n", cur, cur.Item)
            cur = nil
            break
        }
        prev = cur
    }
}

func (this *linked_list_t) FindItem(item interface{}) *node_t {
    for cur := this.head; cur != nil; cur = cur.next {
        if item == cur.Item {
            fmt.Printf("DEBUG: found item 0x%08x %d\n", cur, cur.Item)
            return cur
        }
    }
    return nil
}

func (this *linked_list_t) TravelLinkedList() {
    for cur := this.head; cur != nil; cur = cur.next {
        fmt.Println(cur);
    }
}

func (this *linked_list_t) ReverseLinkedList() {
    var prev    *node_t
    var tmp     *node_t
    for cur := this.head; cur != nil; {
        tmp = cur.next
        cur.next = prev
        prev = cur
        cur = tmp
    }
    this.head = prev
}

func main() {
    l := NewLinkedList()
    l.InsertItem(101)
    l.InsertItem(83)
    l.InsertItem(67)
    l.InsertItem(5)
    l.InsertItem(31)
    l.ReverseLinkedList()
    l.DeleteItem(5)
    l.FindItem(101)
    l.FindItem(67)
    l.TravelLinkedList()

    l1 := NewLinkedList()
    l1.InsertItem("isoft")
    l1.InsertItem("leslie")
    l1.TravelLinkedList()
}
