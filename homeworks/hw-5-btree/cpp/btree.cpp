// 
// btree.cpp
//
// Your Name:
// 
// Collaboration is not only encouraged, it is basically
// demanded. Work together! Share code!
//
// Just write down your main collaborators here:
// ...

#include "btree.h"
#include "custom.h"

using namespace std;

void sort_keys(btree* &root) {
	for (int k = 0; k < 5; k++) {
		if (root->keys[k] == 0) {
			root->keys[k] = 999;
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < root->num_keys; j++) {
			if (root->keys[j + 1] < root->keys[j]) {
				int holder = root->keys[j];
				root->keys[j] = root->keys[j + 1];
				root->keys[j + 1] = holder;
			}
		}
	}
}

bool check_key(btree* &root, int key) {
	for (int i = 0; i < root->num_keys; i++) {
		if (key == root->keys[i]) {
			return true;
		}
	}
	return false;
}

void swap(int *a, int *b) {
	int x;
	x = *a;
	*a = *b;
	*b = x;
}

void split(btree* &root) {
}

void merge(btree* &root, int key) {

}

// -------------------------------------------- I N S E R T ---------
//
// Insert the given key into a b-tree rooted at 'root'.  If the key is
// already contained in the btree this should do nothing.  
// 
// On exit: 
// -- the 'root' pointer should refer to the root of the
//    tree. (the root may change when we insert or delete)
// -- the btree pointed to by 'root' is valid.
void insert(btree* &root, int key) {
	btree* cursor;
	if (check_key(root, key)) { // Check if key exists at current node
		return; // Returns if it finds key
	} else {
		if (root->is_leaf) { // Insert key
			root->keys[root->num_keys] = key;
			sort_keys(root);
			root->num_keys++;
			if (root->num_keys == 5) { // Check if split is needed
				split(root);
			}
		} else { // traverse down tree
			for (int i = 0; i < root->num_keys + 1; i++) {
				cursor = root->children[i];
				if (key < root->keys[i]) {
					break;
				} else if (i == root->num_keys) {
					break;
				}
			}
			insert(cursor, key);
		}
	}
}

// -------------------------------------------- R E M O V E ---------
//
// Remove the given key from a b-tree rooted at 'root'. If the key is
// not in the btree this should do nothing.
//
// On exit:
// -- the 'root' pointer should refer to the root of the
//    tree. (the root may change when we insert or delete)
// -- the btree pointed to by 'root' is valid.
void remove(btree* &root, int key) {
	btree* cursor;
	for (int i = 0; i < root->num_keys; i++) {
		cout << root->keys[i] << ", ";
	}
	if (check_key(root, key)) {
		for (int i = 0; i < root->num_keys; i++) {
			if (key == root->keys[i]) {
				cout << "Removed a Key " << root->keys[i] << endl;
				root->keys[i] = 999;
				sort_keys(root);
				root->num_keys--;
				cout << "Keys Remaining: ";
				for (int i = 0; i < root->num_keys; i++) {
					cout << root->keys[i] << ", ";
				}
				cout << " " << root->num_keys << endl;
			}
		}
	} else {
		if (root->is_leaf) { // Insert key
			return;
		} else { // traverse down tree
			for (int i = 0; i < root->num_keys + 1; i++) {
				cursor = root->children[i];
				if (key < root->keys[i]) {
					break;
				} else if (i == root->num_keys) {
					break;
				}
			}
			remove(cursor, key);
		}
	}
}
// ----------------------------------------- C O N T A I N S --------
//
// Return true if any node accessed from the given root node contains
// the provided key value.
bool contains(btree* &root, int key) {
	btree* cursor;
	if (check_key(root, key)) { // Check if key exists at current node
		return true; // Returns if it finds key
	} else if (root->is_leaf && !check_key(root, key)) {
		return false;
	} else { // traverse down tree
		for (int i = 0; i < root->num_keys + 1; i++) {
			cursor = root->children[i];
			if (key < root->keys[i]) {
				break;
			} else if (i == root->num_keys) {
				break;
			}
		}
		return contains(cursor, key);
	}
}
