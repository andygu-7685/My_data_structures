#ifndef BTREE_NODE_H
#define BTREE_NODE_H
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

#include "list_sorted.h"

const int MAX_CHILD = 3;

template <typename T, int M = MAX_CHILD>
struct btreeNode{
    List<T> _item;
    List<btreeNode<T>*> _child;
    btreeNode<T>* _prev;

    btreeNode(const List<T>& item = List<T>(), List<btreeNode<T>*> child = List<btreeNode<T>*>(), btreeNode<T>* prev = nullptr) 
        : _item(item) , _child(child), _prev(prev) {}

    btreeNode(const T& item, btreeNode<T>* leftChild = nullptr, btreeNode<T>* rightChild = nullptr, btreeNode<T>* prev = nullptr) 
    : _prev(prev) {
        _item.insert_sorted(item);
        _child.insert_before(_child.begin(), leftChild);
        _child.insert_after(_child.begin(), rightChild);
    }

    friend ostream& operator<<(ostream& outs, const btreeNode<T>& printMe){
        outs << " {" << printMe._item << "} ";
        return outs;
    }
};

#endif