#include <iostream>

#ifndef custom_h
#define custom_h

using namespace std;

void sort_keys(btree* &root);

bool check_key(btree* &root, int key);

void swap(int*a, int*b);

void split(btree* &root);

void merge(btree* &root, int key);

#endif
