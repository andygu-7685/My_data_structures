#ifndef BINARY_TREE_H
#define BINARY_TREE_H


#include <iostream>
#include <iomanip>
#include "tree_node.h"
#include "tree_functions.h"


using namespace std;






template <typename T>
class BinaryTree{
    public:
        BinaryTree(){ root = NULL;}
        BinaryTree(const BinaryTree& other){
            root = _copy_tree(other.root);
        }
        BinaryTree& operator=(const BinaryTree& other){
            _clear_tree(root);
            root = _copy_tree(other.root);
            return *this;
        }
        ~BinaryTree(){ _clear_tree(root); }
       
        void insertNode(T ins){
            treeNode<T>* w1 = root;
            if(!w1){
                _insert_before(root, w1, ins, true);
                return;
            }

            while(true){
                if(w1->_item > ins){
                    if(!w1->_left){
                        _insert_after(root, w1, ins, true);
                        return;
                    }
                    w1 = w1->_left;
                }
                else{
                    if(!w1->_right){
                        _insert_after(root, w1, ins, false);
                        return;
                    }
                    w1 = w1->_right;
                }
            }
        }

        T remove(T rem){
            treeNode<T> *nodePtr = searchNode(rem);
            return makeDeletion(nodePtr);
        }

        bool search(T target){
            treeNode<T>* nodePtr = root;
           
            while(nodePtr){
                if (nodePtr->_item == target)
                    return true;
                else if (target < nodePtr->_item)
                    nodePtr = nodePtr->_left;
                else
                    nodePtr = nodePtr->_right;
            }
            return false;
        }

        treeNode<T>* searchNode(T target){
            treeNode<T>* nodePtr = root;
           
            while(nodePtr){
                if (nodePtr->_item == target)
                    return nodePtr;
                else if (target < nodePtr->_item)
                    nodePtr = nodePtr->_left;
                else
                    nodePtr = nodePtr->_right;
            }
            return nullptr;
        }
       
        void displayInOrder() const{ displayInOrder(root);}
        void displayPreOrder() const{ displayPreOrder(root);}
        void displayPostOrder() const{ displayPostOrder(root);}
        int leaf_count(){ return _leaf_count(root); }
        int non_leaf_count(){ return _non_leaf_count(root); }
        int size(){ return _size(root); }
        void displayTree(){ _print_tree(root); }
   

    private:
        treeNode<T>* root;

        T makeDeletion(treeNode<T>* nodePtr){
            treeNode<T> *tempNodePtr;
           
            if (nodePtr == NULL){
                cout << "Cannot delete non exist node\n";
                return T();
            }

            if(nodePtr->_left != NULL && nodePtr->_left != NULL){
                tempNodePtr = nodePtr->_right;
                while(tempNodePtr->_left)
                    tempNodePtr = tempNodePtr->_left;
                nodePtr->_item = tempNodePtr->_item;
                return makeDeletion(nodePtr);
            }
            else{
                return _delete_node(root, nodePtr);
            }
        }

        void displayInOrder(treeNode<T> *nodePtr) const{
            if(nodePtr){
                displayInOrder(nodePtr->left);
                cout << nodePtr->value << " | ";
                displayInOrder(nodePtr->right);
            }
        }

        void displayPreOrder(treeNode<T> *nodePtr) const{
            if(nodePtr){
                cout << nodePtr->value << " | ";
                displayPreOrder(nodePtr->left);
                displayPreOrder(nodePtr->right);
            }
        }

        void displayPostOrder(treeNode<T> *nodePtr) const{
            if(nodePtr){
                displayPostOrder(nodePtr->left);
                displayPostOrder(nodePtr->right);
                cout << nodePtr->value << " | ";
            }
        }

        int _leaf_count(treeNode<T> *nodePtr){
            if(nodePtr->left == nullptr && nodePtr->right == nullptr)
                return 1;
            else if(nodePtr->left == nullptr && nodePtr->right != nullptr)
                return _leaf_count(nodePtr->right);
            else if(nodePtr->left != nullptr && nodePtr->right == nullptr)
                return _leaf_count(nodePtr->left);
            else
                return _leaf_count(nodePtr->left) + _leaf_count(nodePtr->right);
            return 0;
        }

        int _non_leaf_count(treeNode<T> *nodePtr){
            if(nodePtr->left == nullptr && nodePtr->right == nullptr)
                return 0;
            else if(nodePtr->left == nullptr && nodePtr->right != nullptr)
                return 1 + _non_leaf_count(nodePtr->right);
            else if(nodePtr->left != nullptr && nodePtr->right == nullptr)
                return 1 + _non_leaf_count(nodePtr->left);
            else
                return 1 + _non_leaf_count(nodePtr->left) + _non_leaf_count(nodePtr->right);
            return 0;
        }

        int _size(treeNode<T> *nodePtr){
            if(nodePtr)
                return 1 + _size(nodePtr->left) + _size(nodePtr->right);
            return 0;
        }
};




#endif

