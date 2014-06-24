/* Copyright (C) 2013 ~ 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node_s {
    void            *item;
    struct node_s   *next;
} node_t;

typedef struct {
    int     size;
    node_t *head;
} linked_list_t;

linked_list_t *NewLinkedList() 
{
    linked_list_t *ret = NULL;
    ret = malloc(sizeof(linked_list_t));
    assert(ret != NULL);
    ret->size = 0;
    ret->head = NULL;
    return ret;
}

void InsertItem(linked_list_t *this, void *item) 
{
    assert(this != NULL);
    assert(item != NULL);
    node_t *n = malloc(sizeof(node_t));
    assert(n != NULL);
    n->item = item;
    n->next = this->head;
    this->size++;
    this->head = n;
}

void DeleteItem(linked_list_t *this, void *item) 
{
    assert(this != NULL);
    assert(this->head != NULL);
    assert(item != NULL);
    node_t *cur, *prev;
    prev = cur = this->head;
    while (cur != NULL) {
        if (item == cur->item) {
            if (cur == this->head)
                this->head = cur->next;
            else 
                prev->next = cur->next;
            printf("DEBUG: delete item 0x%08x %d\n", cur, *((int*)&cur->item));
            this->size--;
            free(cur);
            cur = NULL;
            break;
        }
        prev = cur;
        cur = cur->next;
    }
}

node_t *FindItem(linked_list_t *this, void *item)                                
{                                                                               
    assert(this != NULL);                                                       
    assert(item != NULL);                                                       
    node_t *cur = this->head;                                                         
    while (cur != NULL) {                                                       
        if (item == cur->item) {                                                
            printf("DEBUG: found item 0x%08x %d\n", cur, *((int*)&cur->item));
            return cur;
        }                                                                       
        cur = cur->next;                                                        
    }                  
    return NULL;    
}

void DeleteLinkedList(linked_list_t *this) 
{
    assert(this != NULL);
    node_t *n = this->head;
    while (n != NULL) {
        free(n);
        n = n->next;
    }
    free(this);
    this = NULL;
}

void TravelLinkedList(linked_list_t *this)                                      
{                                                                               
    assert(this != NULL);                                                       
    node_t *n = this->head;                                                     
    while (n != NULL) {                                                         
        printf("0x%08x %d\n", n, *((int*)&n->item));
        n = n->next;                                                            
    }                                                                           
}

void ReverseLinkedList(linked_list_t *this) 
{
    assert(this != NULL);
    node_t *cur, *prev, *tmp;
    prev    = NULL;
    cur     = this->head;
    while (cur != NULL) {
        tmp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = tmp;
    }
    this->head = prev;
}

int main(int argc, char *argv[]) 
{
    linked_list_t *l = NewLinkedList();
    if (l) {
        InsertItem(l, (void *)101);
        InsertItem(l, (void *)83);
        InsertItem(l, (void *)67);
        InsertItem(l, (void *)5);
        InsertItem(l, (void *)31);
        ReverseLinkedList(l);
        DeleteItem(l, (void *)5);
        FindItem(l, (void *)101);
        FindItem(l, (void *)67);
        TravelLinkedList(l);
        DeleteLinkedList(l);
    }
    return 0;
}
