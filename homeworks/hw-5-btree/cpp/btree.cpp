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

void split (btree* &root, int key) {

}

void merge (btree* &root, int key) {

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
	if (root->is_leaf == true) {
		if (root->num_keys < 5) {
			root->keys[root->num_keys] = key;
		} else {
			split(root, key);
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

}

// ----------------------------------------- C O N T A I N S --------
//
// Return true if any node accessed from the given root node contains
// the provided key value.
bool contains(btree* &root, int key) {
  return false;
}
