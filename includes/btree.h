#ifndef BTREE_H
#define BTREE_H


#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

#include "bt_node.h"
#include "btree_functions.h"
#include "MyQueue.h"

using namespace std;



template<typename T>
class BTree {
private:

public:

    BTNode<T>* root;

    BTree() {
        root = new BTNode<T>();
    }

    BTree(const BTNode<T>& copyThis) {
        root = _copy_btree<T>(copyThis);
    }

    BTree& operator=(const BTree& other){
        _clear_btree<T>(root);
        root = _copy_btree(other.root);
        return *this;
    }

    ~BTree() {
        _clear_btree<T>(root);
    }

    void print_BTree(BTNode<T>* target = nullptr){
        _print_BTree(root, target);
    }

    BTNode<T>* search(T key){
        return _search_btree(root, key);
    }

};


#endif