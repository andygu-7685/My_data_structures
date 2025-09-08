#ifndef TREE_NODE_H
#define TREE_NODE_H
#include <iomanip>
#include <iostream>
using namespace std;

template <typename T>
struct treeNode{
    T _item;
    treeNode<T>* _left;
    treeNode<T>* _right;
    treeNode<T>* _prev;

    treeNode(const T& item = T(), treeNode<T>* left = nullptr, treeNode<T>* right = nullptr, treeNode<T>* prev = nullptr) 
        : _item(item) , _left(left), _right(right), _prev(prev) {}

    friend ostream& operator<<(ostream& outs, const treeNode<T>& printMe){
        if(printMe._left != nullptr)
            outs << "<-";
        else
            outs << "  ";
        outs << " [" << printMe._item << "] ";
        if(printMe._right != nullptr)
            outs << "->";
        else
            outs << "  ";
        return outs;
    }
};

#endif