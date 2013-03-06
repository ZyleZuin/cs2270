//
// binary_search_tree.cpp
//
// Please refer to binary_search_tree.h for documentation.
//

#include "binary_search_tree.h"
int i = 0;

bt_node* init_node(int data) {
    bt_node* a = new bt_node;
    a->data = data;
    a->left = NULL;
    a->right = NULL;
    return a;
}

void insert_recursively(bt_node* top, bt_node* new_node) {
    if (new_node->data < top->data) {
        if (top->left == NULL) {
            top->left = new_node;
        } else {
            insert_recursively(top->left, new_node);
        }
    } else {
        if (top->right == NULL) {
            top->right = new_node;
        } else {
            insert_recursively(top->right, new_node);
        }
    }
}

void insert(bt_node** top_ref, bt_node* new_node) {
    if (*top_ref == NULL) {
        *top_ref = new_node;
    } else {
        insert_recursively(*top_ref, new_node);
    }
}

void insert_data(bt_node** top_ref, int data) {
    bt_node* new_node = init_node(data);
    insert(top_ref, new_node);
}

void remove(bt_node** top_ref, int data) {
    // implement me
}

bool contains(bt_node* top, int data) {
    // implement me
    return false;
}

bt_node* get_node(bt_node* top, int data) {
    // implement me
    return NULL;
}

int size(bt_node* top) {
    // implement me
    return -1;
}

void to_array(bt_node* top, int arr[]) {
    if (top != NULL) {
        to_array(top->left, arr);
        arr[i] = top->data;
        i++;
        to_array(top->right, arr);
    }
}
