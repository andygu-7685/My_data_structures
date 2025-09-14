#ifndef TREE_FUNCTION_H
#define TREE_FUNCTION_H

#include <iostream>
#include <iomanip>
#include "tree_node.h"
#include "MyQueue.h"
#include "MyStack.h"
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;



//F
template <typename T>
void set_prev(treeNode<T>* current, treeNode<T>* prevNode = nullptr){
    if(current)
        current->_prev = prevNode;
}

template <typename T>
void set_left(treeNode<T>* current, treeNode<T>* leftNode = nullptr){
    if(current)
        current->_left = leftNode;
}

template <typename T>
void set_right(treeNode<T>* current, treeNode<T>* rightNode = nullptr){
    if(current)
        current->_right = rightNode;
}






//left == true, if insert root as left child, else insert as right child
//left is default true
template <typename T>
treeNode<T> *_insert_root(treeNode<T> *&root_ptr, const T &item, bool left = true){
  treeNode<T> *temp = new treeNode<T>(item);
  if(left)
    set_left(temp, root_ptr);
  else
    set_right(temp, root_ptr);
  set_prev(root_ptr, temp);
  root_ptr = temp;
  return root_ptr;
}












template<typename T>
void _print_tree(treeNode<T> *root_ptr, treeNode<T>* target = nullptr){
    //Exceptions
    //------------------------------------------------------------------------
    if(root_ptr == nullptr){
        cout << "empty tree\n";
        return;
    }
    else if(root_ptr == target){
        cout << ((root_ptr->_left) ? "<-" : "  ");
        cout << " {" << root_ptr->_item << "} ";
        cout << ((root_ptr->_right) ? "->" : "  ");
    }
    else{
        cout << *root_ptr;
    }
    cout << endl;

    //Variables
    //------------------------------------------------------------------------
    Queue<treeNode<T>*> order;
    treeNode<T>* placehold = new treeNode<T>();
    treeNode<T>* w1;
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
            (w1->_left) ? order.push(w1->_left) : order.push(placehold);
            (w1->_right) ? order.push(w1->_right) : order.push(placehold);
        }

        //Detect end of tree
        //------------------------------------------------------------------------
        typename Queue<treeNode<T>*>::Iterator it1 = order.begin();
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
                cout << (((*it1)->_left) ? "<-" : "  ");
                cout << " {" << (*it1)->_item << "} ";
                cout << (((*it1)->_right) ? "->" : "  ");
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







//I
//
/*
template<typename T>
void _print_tree(treeNode<T> *root_ptr, treeNode<T>* target = nullptr){
    if(root_ptr == nullptr){
        cout << "empty tree\n";
        return;
    }

    Queue<treeNode<T>*> order;
    treeNode<T>* placehold = new treeNode<T>();
    treeNode<T>* w1;
    int levelSize;
    if(root_ptr == target){
        if(root_ptr->_left != nullptr)
            cout << "<-";
        else
            cout << "  ";
        cout << " {" << root_ptr->_item << "} ";
        if(root_ptr->_right != nullptr)
            cout << "->";
        else
            cout << "  ";
        cout << endl;
    }
    else{
        cout << (*root_ptr) << endl;
    }
    order.push(root_ptr);

    while(true){
        levelSize = order.size();
        for(int i = 0; i < levelSize; i++){
            w1 = order.pop();
            if(w1->_left != nullptr && w1->_right != nullptr){
                order.push(w1->_left);
                order.push(w1->_right);
            }
            else if(w1->_left != nullptr && w1->_right == nullptr){
                order.push(w1->_left);
                order.push(placehold);
            }
            else if(w1->_left == nullptr && w1->_right != nullptr){
                order.push(placehold);
                order.push(w1->_right);
            }
            else{
                order.push(placehold);
                order.push(placehold);
            }
        }

        typename Queue<treeNode<T>*>::Iterator it1 = order.begin();
        bool EndofTree = true;
        while(it1 != order.end()){
            if(*it1 != placehold){
                EndofTree = false;
                break;
            }
            it1++;
        }

        if(EndofTree)
            break;
        
        it1 = order.begin();
        
        while(it1 != order.end()){
            if(*it1 == target){
                if((*it1)->_left != nullptr)
                    cout << "<-";
                else
                    cout << "  ";
                cout << " {" << (*it1)->_item << "} ";
                if((*it1)->_right != nullptr)
                    cout << "->";
                else
                    cout << "  ";
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

*/









//I C
    //ptr to previous node
    template <typename ITEM_TYPE>
    treeNode<ITEM_TYPE>* _previous_node(treeNode<ITEM_TYPE>* root, treeNode<ITEM_TYPE>* prev_to_this){
        if(prev_to_this)
            return prev_to_this->_prev;
        //there's no way to determine which nullptr
        return nullptr;
    }

    template <typename ITEM_TYPE>
    treeNode<ITEM_TYPE>* _next_right(treeNode<ITEM_TYPE>* root, treeNode<ITEM_TYPE>* next_to_this){
        return ((next_to_this) ? next_to_this->_right : root);
    }

    template <typename ITEM_TYPE>
    treeNode<ITEM_TYPE>* _next_left(treeNode<ITEM_TYPE>* root, treeNode<ITEM_TYPE>* next_to_this){
        return ((next_to_this) ? next_to_this->_left : root);
    }




    //this function assume only one child for root
    //root cannot be a subtree of another tree
    template <typename ITEM_TYPE>
    ITEM_TYPE _delete_root(treeNode<ITEM_TYPE> *&root){
        assert(root != nullptr);
        assert(!(root->_left && root->_right));
        ITEM_TYPE save = root->_item;
        treeNode<ITEM_TYPE>* saveNext;
        if(root->_left && !root->_right)
            saveNext = root->_left;
        else if(!root->_left && root->_right)
            saveNext = root->_right;
        else
            saveNext = nullptr;
        delete root;
        root = saveNext;
        set_prev(root);
        return save;
    }


//I C
    //brute force search
    template <typename ITEM_TYPE>
    treeNode<ITEM_TYPE>* _search_tree(treeNode<ITEM_TYPE>* root, ITEM_TYPE key) {
        if (!root) return nullptr;

        if (root->_item == key)
            return root;

        treeNode<ITEM_TYPE>* found = _search_tree(root->_left, key);
        if (found) return found;

        return _search_tree(root->_right, key);
    }

//I C


    //insert_left == true, if insert insert_this left, else insert right
    //concat_left apply when there's already a node in the inserting path
    //determine if the original node goes to left or right of the insert_this node
    //concat_left == true, if concat to left of insert_this, else concat right
    template <typename ITEM_TYPE>
    treeNode<ITEM_TYPE>* _insert_after(treeNode<ITEM_TYPE>*& root, treeNode<ITEM_TYPE> *after_this, ITEM_TYPE insert_this, bool insert_left = true, bool concat_left = true){
        if(after_this == nullptr)           
            return _insert_root<ITEM_TYPE>(root, insert_this, concat_left);

        treeNode<ITEM_TYPE> *saveNext = ((insert_left) ? after_this->_left : after_this->_right);
        treeNode<ITEM_TYPE> *tempLeft = nullptr;
        treeNode<ITEM_TYPE> *tempRight = nullptr;
        (concat_left) ? tempLeft = saveNext : tempRight = saveNext;
        treeNode<ITEM_TYPE> *temp = new treeNode<ITEM_TYPE>(insert_this, tempLeft, tempRight, after_this);
        (concat_left) ? set_prev(tempLeft, temp) : set_prev(tempRight, temp);
        (insert_left) ? set_left(after_this, temp) : set_right(after_this, temp);
        return temp;
    }



//I C
    //concat_left determine if the before this node goes to left or right of the insert_this node
    //concat_left == true, if concat to left of insert_this, else concat right
    template <typename ITEM_TYPE>
    treeNode<ITEM_TYPE>* _insert_before(treeNode<ITEM_TYPE>*& root, treeNode<ITEM_TYPE>* before_this, ITEM_TYPE insert_this, bool concat_left = true){
        treeNode<ITEM_TYPE>* prevPtr = _previous_node<ITEM_TYPE>(root, before_this);
        if(prevPtr == nullptr)                                    //in case if the iMarker is the first node                              //why dont you use insert head! ): ): ):
            return _insert_root<ITEM_TYPE>(root, insert_this, concat_left);

        bool is_bf_left = (prevPtr->_left == before_this);
        treeNode<ITEM_TYPE>* tempLeft = nullptr; 
        treeNode<ITEM_TYPE>* tempRight = nullptr;
        (concat_left) ? tempLeft = before_this : tempRight = before_this;
        treeNode<ITEM_TYPE>* temp = new treeNode<ITEM_TYPE>(insert_this, tempLeft, tempRight, prevPtr);
        set_prev(before_this, temp);
        (is_bf_left) ? set_left(prevPtr, temp) : set_right(prevPtr, temp);
        return temp;
    }



    //assumes only one child for delete this
    template <typename ITEM_TYPE>
    ITEM_TYPE _delete_node(treeNode<ITEM_TYPE>*&root, treeNode<ITEM_TYPE>* delete_this){
        assert(delete_this != nullptr);
        assert(!(delete_this->_left && delete_this->_right));
    
        treeNode<ITEM_TYPE>* prevPtr = _previous_node<ITEM_TYPE>(root, delete_this);
        if(prevPtr == nullptr && delete_this == root)
            return _delete_root(root);
        bool is_dt_left = (prevPtr->_left == delete_this);
        
        ITEM_TYPE save = delete_this->_item;
        treeNode<ITEM_TYPE>* saveNext;
        if(delete_this->_left && !delete_this->_right)
            saveNext = delete_this->_left;
        else if(!delete_this->_left && delete_this->_right)
            saveNext = delete_this->_right;
        else
            saveNext = nullptr;

        delete delete_this;
        (is_dt_left) ? prevPtr->_left = saveNext : prevPtr->_right = saveNext;
        set_prev(saveNext, prevPtr);
        return save;
    }



//I C
    //duplicate the tree...
    template <typename ITEM_TYPE>
    treeNode<ITEM_TYPE>* _copy_tree(treeNode<ITEM_TYPE>* root){
        if (root == nullptr)
            return nullptr;
    
        treeNode<ITEM_TYPE>* newRoot = new treeNode<ITEM_TYPE>(root->_item);

        treeNode<ITEM_TYPE>* left = _copy_tree(root->_left);
        set_prev(left, newRoot);
        treeNode<ITEM_TYPE>* right = _copy_tree(root->_right);
        set_prev(right, newRoot);

        newRoot->_left = left;
        newRoot->_right = right;
        return newRoot;
    }





//I  C
    //delete all the nodes
    template <typename ITEM_TYPE>
    void _clear_tree(treeNode<ITEM_TYPE>*& root){
        if(root){
            _clear_tree(root->_left);
            _clear_tree(root->_right);
            delete root;
            root = nullptr;
        }
    }




    template <typename ITEM_TYPE>
    string intToBinary(ITEM_TYPE num) {
        string binary = "";
        if (num <= 0)
            return "000000000000000000000000000000000000000000000000000000000000000000000000000000";
        
        while (num > 0) {
            binary = (((static_cast<int>(num) % 2) == 0) ? "0" : "1") + binary;
            num = floor(num / 2.0);
        }
        return binary;
    }


    // the pos is based on a perfect binary tree, pos must be greater than 0
    /*
             1
        2,         3
     4,   5,    6,    7
    8,9,10,11,12,13,14,15
    */
    template <typename ITEM_TYPE>
    ITEM_TYPE& _at(treeNode<ITEM_TYPE>* root, int pos){
        if(root == nullptr){
            cout << "Error at(): empty tree";
            return ITEM_TYPE();
        }

        int totalDec = static_cast<int>(floor(log(pos)/log(2)));
        string decMap = intToBinary((pos - pow(2, totalDec)));
        treeNode<ITEM_TYPE>* w1 = root;
        for(int i = 0; i < totalDec; i++){
            if(decMap[i] == '0'){
                //turn left
                w1 = w1->_left;
            }
            else{
                //turn right
                w1 = w1->_right;
            }

            if(!w1){
                cout << "the branch you want do not exist";
                return ITEM_TYPE();
            }
        }
        return w1->_item;
    }


    template <typename ITEM_TYPE>
    treeNode<ITEM_TYPE>* _at_index(treeNode<ITEM_TYPE>* root, int pos){
        if(root == nullptr){
            cout << "Error at(): empty tree";
            return nullptr;
        }

        int totalDec = static_cast<int>(floor(log(pos)/log(2)));
        string decMap = intToBinary((pos - pow(2, totalDec)));
        treeNode<ITEM_TYPE>* w1 = root;
        for(int i = 0; i < totalDec; i++){
            if(decMap[i] == '0'){
                //turn left
                w1 = w1->_left;
            }
            else{
                //turn right
                w1 = w1->_right;
            }

            if(!w1){
                cout << "the branch you want do not exist";
                return nullptr;
            }
        }
        return w1;
    }



#endif 
