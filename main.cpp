#include <iostream>
#include <iomanip>
#include <vector>

#include "C:\Users\USER\Documents\My_Projects\Doubly-linked-list\includes\btree.h"
using namespace std;







int main(int argv, char** argc) {
    BTree<int> root;
    BTNode<int>* target = root.root; 
    BTNode<int>* found = nullptr;
    bool getKey = true;
    char key;
    int num;
    int index;

    while(getKey){
        cout << "[f] find, [a] insert, [d] delete, [n] new node, [p] mov to parent, [c] mov to child, [j] add new node" << endl;
        cout << "[q] quit" << endl;
        root.print_BTree(target);
        cin >> key;
        key = tolower(key);
        switch(key){
            //find
            case 'f':
                cout << "Enter number you want find: ";
                cin >> num;
                found = root.search(num);
                target = found;
                cout << ((found) ?  "Result: Found" : "Result: Not found") << endl;
            break;
            //insert after
            case 'a':
                cout << "Enter number you want insert: ";
                cin >> num;
                cout << "Enter index you want insert: ";
                cin >> index;
                if(target)
                    target->_insert(num, index);
            break;
            //delete
            case 'd':
                cout << "Enter index you want delete: ";
                cin >> index;
                if(target)
                    target->_remove(index);
            break;

            case 'p':
                if(target && target->_parent)
                    target = target->_parent;
            break;

            case 'c':
                cout << "Enter child index you want mov to: ";
                cin >> index;
                if(target && target->_child[index])
                    target = target->_child[index];
            break;

            case 'j':
                cout << "Enter the first value of the new node: ";
                cin >> num;
                cout << "Enter child index you want add to: ";
                cin >> index;
                if(target && !target->_child[index])
                    target->_child[index] = new BTNode<int>(vector<int>{num}, vector<BTNode<int>*>{nullptr, nullptr}, target);
            break;
            //Quit
            case 'q':
                getKey = false;
            break;

            default:
                cout << "Invalid Command, Try Again" << endl;
            break;
        }
    }
    
    return 0;
}



