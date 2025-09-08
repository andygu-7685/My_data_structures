#ifndef BTREE_FUNCTION_H
#define BTREE_FUNCTION_H

#include <iostream>
#include <iomanip>
#include "btree_node.h"
#include "MyQueue.h"
#include "MyStack.h"
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;



//F
template <typename T>
void set_prev(btreeNode<T>* current, btreeNode<T>* prevNode = nullptr){
    if(current)
        current->_prev = prevNode;
}

template <typename T>
void set_child(btreeNode<T>* current, int index){
    if(current)
        current->_child[index] = nullptr;
}

template <typename T>
void set_child(btreeNode<T>* current, btreeNode<T>* childNode, int index){
    if(current)
        current->_child[index] = childNode;
}

template <typename T>
void set_item(btreeNode<T>* current, const T& item, int index){
    if(current)
        current->_item[index] = item;
}

template <typename T>
void insert_item(btreeNode<T>* current, const T& item){
    if(current)
        current->_item.insert_sorted(item);
}

template <typename T>
void insert_item(btreeNode<T>* current, const T& item, int index){
    if(current)
        current->_item.insert_before(index, item);
}

//return index of the current in it's parent
template <typename T>
int find_parent_index(btreeNode<T>* current){
    if(current && current->_prev)
        return current->_prev->_child.search_index(current);
    return -1;
}






//left determine if the old root is at left or right of the new root
template <typename T>
btreeNode<T> *_insert_root(btreeNode<T> *&root_ptr, const T &item, bool left = true){
  btreeNode<T> *temp = new btreeNode<T>(item);
  if(left)
    set_child(temp, root_ptr, 0);
  else
    set_child(temp, root_ptr, 1);
  set_prev(root_ptr, temp);
  root_ptr = temp;
  return root_ptr;
}


//index determine which new root child is the old root
//the function rewrite the original child at index with the old root
// 0 1 2 3 4 5 6 7 8
//0 1 2 3 4 5 6 7 8 9
//assume that any key has a left and right child can be nullptr, by definition of btree 
template <typename T>
btreeNode<T> *_insert_root(btreeNode<T> *&root_ptr, const List<T>& item, const List<btreeNode<T>*>& child, int index = 0){
  btreeNode<T> *temp = new btreeNode<T>(item, child);
  set_child(temp, root_ptr, index);
  set_prev(root_ptr, temp);
  root_ptr = temp;
  return root_ptr;
}



//I
//
template<typename T>
void _print_tree(btreeNode<T> *root_ptr, btreeNode<T>* target = nullptr){
    //Exceptions
    //------------------------------------------------------------------------
    if(root_ptr == nullptr){
        cout << "empty tree\n";
        return;
    }
    else if(root_ptr == target){
        cout << " >" << root_ptr->_item << "< ";
    }
    else{
        cout << *root_ptr;
    }
    cout << endl;

    //Variables
    //------------------------------------------------------------------------
    Queue<btreeNode<T>*> order;
    btreeNode<T>* placehold = new btreeNode<T>();
    btreeNode<T>* w1;
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
        typename Queue<btreeNode<T>*>::Iterator it1 = order.begin();
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
            if(*it1 == target)
                cout << " >" << (*it1)->_item << "< ";
            else if(*it1 == placehold)
                cout << "   { }   ";
            else
                cout << **it1;
            it1++;
        }
        cout << endl;
    }
    delete placehold;
}





//I C
    //ptr to previous node
    template <typename ITEM_TYPE>
    btreeNode<ITEM_TYPE>* _previous_node(btreeNode<ITEM_TYPE>* root, btreeNode<ITEM_TYPE>* prev_to_this){
        return ((prev_to_this) ? prev_to_this->_prev : nullptr);
    }

    template <typename ITEM_TYPE>
    btreeNode<ITEM_TYPE>* _next_node(btreeNode<ITEM_TYPE>* root, btreeNode<ITEM_TYPE>* next_to_this, int index = 0){
        return ((next_to_this) ? next_to_this->_child[index] : root);
    }




    //this function assume only one child for root
    //root node can have less than min key
    template <typename ITEM_TYPE>
    ITEM_TYPE _delete_root_key(btreeNode<ITEM_TYPE> *&root, int index, int min_key){
        assert(root != nullptr);
        ITEM_TYPE save = root->_item[index];
        //only root node in tree
        if(root->_child.empty()){
            root->_item.Delete(index);
            //only one item
            if(root->_item.size() <= 0){
                delete root;
                root = nullptr;
            }
        }
        else{
            btreeNode<ITEM_TYPE> right = root->_child[index + 1];
            root->_item[index] = right->_item[0];
            _delete_node_key(right, 0, min_key);
        }
        return save;
    }




    //delete key at index for delete from
    template <typename ITEM_TYPE>
    ITEM_TYPE _delete_node_key(btreeNode<ITEM_TYPE>*& root, btreeNode<ITEM_TYPE>* delete_from, int index, int min_key){
        assert(delete_from != nullptr);
        if(delete_from->_prev == nullptr && delete_from == root)
            return _delete_root_key(delete_from, index, min_key);
    
        //index of left sib in _child
        int self = find_parent_index(delete_from);
        int left = self - 1;
        int right = self + 1;
        btreeNode<ITEM_TYPE>* selfNode = delete_from;
        btreeNode<ITEM_TYPE>* parenNode = delete_from->_prev;
        List<ITEM_TYPE>& selfItem = selfNode->_item;
        List<ITEM_TYPE>& parenItem = parenNode->_item;
        List<btreeNode<ITEM_TYPE>*>& selfChild = selfNode->_child;
        List<btreeNode<ITEM_TYPE>*>& parenChild = parenNode->_child;

        if(right >= 0){
            btreeNode<ITEM_TYPE>* rightNode = parenNode->_child[right];
            List<ITEM_TYPE>& rightItem = rightNode->_item;
            List<btreeNode<ITEM_TYPE>*>& rightChild = rightNode->_child;

            //swap
            if(rightItem.size() > min_key){
                selfItem[index] = parenItem[self];
                parenItem[right] = leftItem[leftItem.size() - 1];
                //works for both leaf and branch node
                _delete_root_key(leftNode, leftItem.size() - 1, min_key);
            }
            //merge assume that min_key/max_key is less than 1/2
            else{
                //works for both leaf and branch node
                _delete_root_key(selfNode, index, min_key);
                selfItem.insert_before(selfItem.begin(), parenItem[left]);
                selfItem = leftItem + selfItem;
                selfChild = leftChild + selfChild;
                parenItem.Delete(left);
                delete parenChild[left];
                parenChild.Delete(left);
            }
        }
        else if(left >= 0){
            btreeNode<ITEM_TYPE>* leftNode = parenNode->_child[left];
            List<ITEM_TYPE>& leftItem = leftNode->_item;
            List<btreeNode<ITEM_TYPE>*>& leftChild = leftNode->_child;

            //swap
            if(leftItem.size() > min_key){
                //ordered case:
                //---------------------------------------------------------------------
                // _delete_root_key(selfNode, index, min_key);
                // selfItem.insert_before(selfItem.begin(), parenItem[left]);
                //---------------------------------------------------------------------
                
                //unordered case: (can have null branch)
                //---------------------------------------------------------------------
                selfItem[index] = parenItem[left];
                //---------------------------------------------------------------------

                parenItem[left] = leftItem[leftItem.size() - 1];
                //works for both leaf and branch node
                _delete_root_key(leftNode, leftItem.size() - 1, min_key);
            }
            //merge assume that min_key/max_key is less than 1/2
            //works for both ordered and unordered case
            else{
                //works for both leaf and branch node
                _delete_root_key(selfNode, index, min_key);
                selfItem.insert_before(selfItem.begin(), parenItem[left]);
                selfItem = leftItem + selfItem;
                selfChild = leftChild + selfChild;
                parenItem.Delete(left);
                delete parenChild[left];
                parenChild.Delete(left);
            }
        }
    }



//I C
    //brute force search
    // template <typename ITEM_TYPE>
    // treeNode<ITEM_TYPE>* _search_tree(treeNode<ITEM_TYPE>* root, ITEM_TYPE key) {
    //     if (!root) return nullptr;

    //     if (root->_item == key)
    //         return root;

    //     treeNode<ITEM_TYPE>* found = _search_tree(root->_left, key);
    //     if (found) return found;

    //     return _search_tree(root->_right, key);
    // }

//I C


    //This function is not possible for ordered b tree
    template <typename ITEM_TYPE>
    btreeNode<ITEM_TYPE>* _insert_after(btreeNode<ITEM_TYPE>*& root, btreeNode<ITEM_TYPE>* insert_to, int after_this, ITEM_TYPE insert_this, btreeNode<ITEM_TYPE>* insert_subtree = nullptr, bool subtree_left = true){
        insert_to->_item.insert_after(after_this, insert_this);
        if(subtree_left)
            insert_to->_child.insert_after(after_this, insert_subtree);
        else
            insert_to->_child.insert_after(after_this + 1, insert_subtree);
        return insert_to;
    }



//I C
    //This function is not possible for ordered b tree
    template <typename ITEM_TYPE>
    btreeNode<ITEM_TYPE>* _insert_before(btreeNode<ITEM_TYPE>*& root, btreeNode<ITEM_TYPE>* insert_to, int before_this, ITEM_TYPE insert_this, btreeNode<ITEM_TYPE>* insert_subtree = nullptr, bool subtree_left = true){
        insert_to->_item.insert_before(before_this, insert_this);
        if(subtree_left)
            insert_to->_child.insert_before(before_this, insert_subtree);
        else
            insert_to->_child.insert_beofre(before_this + 1, insert_subtree);
        return insert_to;
    }





    //assume sorted tree
    template <typename ITEM_TYPE>
    btreeNode<ITEM_TYPE>* _insert_sorted(btreeNode<ITEM_TYPE>*& root, ITEM_TYPE insert_this, int max_key){
        btreeNode<ITEM_TYPE>* currentNode = root;
        while(!currentNode->_child.empty()){
            for(int i = 0; i < currentNode->_item.size(); i++){
                if(insert_this < currentNode->_item[i])
                    currentNode = currentNode->_child[i];
            }
        }
        List<ITEM_TYPE> Lst1;
        List<ITEM_TYPE> Lst2;
        if(currentNode->_child)        
        return currentNode;
    }





//I C
    //duplicate the list...
    template <typename ITEM_TYPE>
    treeNode<ITEM_TYPE>* _copy_tree(treeNode<ITEM_TYPE>* root){
        if (root == nullptr)
            return nullptr;
    
        treeNode<ITEM_TYPE>* left = _copy_tree(root->left);
        set_prev(left, root);
        treeNode<ITEM_TYPE>* right = _copy_tree(root->right);
        set_prev(right, root);
        return new treeNode<ITEM_TYPE>(root->value, left, right);
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
