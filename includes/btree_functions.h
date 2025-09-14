#ifndef BTREE_FUNCTION_H
#define BTREE_FUNCTION_H

#include <iostream>
#include <iomanip>
#include "bt_node.h"
#include "MyQueue.h"
#include "MyStack.h"
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;


//brute force search
template <typename ITEM_TYPE>
BTNode<ITEM_TYPE>* _search_btree(BTNode<ITEM_TYPE>* root, ITEM_TYPE key) {
    if (!root) return nullptr;

    for(int i = 0; i < root->_item.size(); i++){
        if (root->_item[i] == key)
            return root;
    }
    
    for(int j = 0; j < root->_child.size(); j++){
        BTNode<ITEM_TYPE>* found = _search_btree(root->_child[j], key);
        if (found) return found;
    }
    return nullptr;
}


//duplicate the btree...
template <typename ITEM_TYPE>
BTNode<ITEM_TYPE>* _copy_btree(BTNode<ITEM_TYPE>* root){
    if (root == nullptr)
        return nullptr;

    BTNode<ITEM_TYPE>* newRoot = new BTNode<ITEM_TYPE>(root->_item);
    vector<BTNode<ITEM_TYPE>*> childVec;
    for(int i = 0; i < root->_child.size(); i++){
        BTNode<ITEM_TYPE>* child = _copy_tree(root->_child[i]);
        if(child)
            child->_parent = newRoot;
        childVec.push_back(child);
    }
    newRoot->_child = childVec;

    return newRoot;
}


//delete all the nodes of a btree
template <typename ITEM_TYPE>
void _clear_btree(BTNode<ITEM_TYPE>*& root){
    if(root){
        for(int i = 0; i < root->_child.size(); i++)
            _clear_btree(root->_child[i]);
        delete root;
        root = nullptr;
    }
}

template <typename T>
void _print_BTree(BTNode<T> *root_ptr, BTNode<T>* target = nullptr){
    //Exceptions
    //------------------------------------------------------------------------
    if(root_ptr == nullptr){
        cout << "empty tree\n";
        return;
    }
    else if(root_ptr == target){
        cout << " {";
        for(int i = 0; i < root_ptr->_item.size(); i++)
            cout << root_ptr->_item[i] << " ";
        cout << "} ";
    }
    else{
        cout << *root_ptr;
    }
    cout << endl;

    //Variables
    //------------------------------------------------------------------------
    Queue<BTNode<T>*> order;
    BTNode<T>* placehold = new BTNode<T>();
    BTNode<T>* w1;
    int levelSize;
    order.push(root_ptr);

    //Main Loop
    //------------------------------------------------------------------------
    while(true){
        //Push item of same level to stack
        //------------------------------------------------------------------------
        levelSize = order.size();
        for(int i = 0; i < levelSize; i++){
            w1 = order.pop();
            for(int i = 0; i < w1->_child.size(); i++)
                (w1->_child[i]) ? order.push(w1->_child[i]) : order.push(placehold);
        }

        //Detect end of tree
        //------------------------------------------------------------------------
        typename Queue<BTNode<T>*>::Iterator it1 = order.begin();
        bool EndofTree = true;
        while(it1 != order.end()){
            if(*it1 != placehold){
                EndofTree = false;
                break;
            }
            it1++;
        }
        if(EndofTree) break;

        //Print the level
        //------------------------------------------------------------------------ 
        it1 = order.begin();
        while(it1 != order.end()){
            if(*it1 == target){
                cout << " {";
                for(int i = 0; i < target->_item.size(); i++)
                    cout << target->_item[i] << " ";
                cout << "} ";
            }
            else if(*it1 == placehold){
                cout << "   [ ]   ";
            }
            else{
                cout << **it1;
            }
            it1++;
        }
        cout << endl;
    }
    delete placehold;
}


#endif 