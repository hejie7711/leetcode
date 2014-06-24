/* Copyright (C) 2013 ~ 2014 Leslie Zhai <xiangzhai83@gmail.com> */

#include <stdio.h>
#include <stdlib.h>

typedef struct node_s {
    int             item;
    struct node_s   *left;
    struct node_s   *right;
} node_t; 

void insert(int key, node_t **leaf)
{
    if (*leaf == NULL) {
        *leaf = (node_t *)malloc(sizeof(node_t));
        (*leaf)->item = key;
        (*leaf)->left = NULL;    
        (*leaf)->right = NULL;  
    } else if (key < (*leaf)->item) {
        insert(key, &(*leaf)->left);
    } else if (key > (*leaf)->item) {
        insert(key, &(*leaf)->right);
    }
}

node_t *search(int key, node_t *leaf)
{
    if (leaf != NULL) {
        if (key == leaf->item) {
            return leaf;
        } else if (key < leaf->item) {
            return search(key, leaf->left);
        } else {
            return search(key, leaf->right);
        }
    } 
    return NULL;
}

void travel_tree(node_t *leaf) 
{
    if (leaf != NULL) {
        printf("%d\t", leaf->item);
        travel_tree(leaf->left);
        travel_tree(leaf->right);
    }
}

void destroy_tree(node_t *leaf)
{
    if (leaf != NULL) {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        free(leaf);
        leaf = NULL;
    }
}

int main(int argc, char *argv[]) 
{
    node_t *root = NULL;
    int key = argv[1] ? atoi(argv[1]) : 67;
    for (int i = 0; i < 1024; i++) {
        insert(rand() % 100, &root);
    }
    travel_tree(root);
    printf("\n");
    printf("search %d 0x%08x\n", key, search(key, root));
    destroy_tree(root);
    return 0;
}
