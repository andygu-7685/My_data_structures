#include <iostream>
#include <iomanip>
#include <vector>

#include "C:\Users\agu4\Documents\MyProject\Doubly-linked-list\includes\binary_tree.h"
using namespace std;










int main(int argv, char** argc) {
    treeNode<int>* root = nullptr;
    treeNode<int>* currentNode = nullptr;
    bool getKey = true;
    char key;
    int num;
    bool insert_order = false;
    bool concat_order = false;

    while(getKey){
        cout << "[f] find, [a] insert after, [b] insert before, [d] delete, [c] copy, [~] clear" << endl;
        cout << "[@] at, [q] quit" << endl;
        _print_tree<int>(root, currentNode);
        cin >> key;
        key = tolower(key);
        switch(key){
            //move up
            case 'l':
                currentNode = _previous_node(root, currentNode);
            break;
            //move right
            case '.':
                currentNode = _next_right(root, currentNode);
            break;
            //move left
            case ',':
                currentNode = _next_left(root, currentNode);
            break;
            //find
            case 'f':
                cout << "Enter number you want find: ";
                cin >> num;
                currentNode = _search_tree<int>(root, num);
                cout << ((currentNode) ?  "Result: Found" : "Result: Not found") << endl;
            break;
            //insert after
            case 'a':
                cout << "Enter number you want insert after: ";
                cin >> num;
                cout << "Enter insert order (0 right, 1 left): ";
                cin >> insert_order;
                cout << "Enter concat order (0 right, 1 left): ";
                cin >> concat_order;
                _insert_after<int>(root, currentNode, num, insert_order, concat_order);
            break;
            //insert before
            case 'b':
                cout << "Enter number you want insert before: ";
                cin >> num;
                cout << "Enter concat order (0 right, 1 left): ";
                cin >> concat_order;
                _insert_before<int>(root, currentNode, num, concat_order);
            break;
            //delete
            case 'd':
                if(currentNode && (!currentNode->_left || !currentNode->_right)){
                    _delete_node<int>(root, currentNode);
                    currentNode = nullptr;
                }
                else{
                    cout << "enter a valid node";
                }
            break;
            //copy
            case 'c':

            break;
            //clear
            case '~':

            break;
            //at
            case '@':
                cout << "Enter the index you want find: ";
                cin >> num;
                currentNode = _at_index(root, num);
                cout << ((currentNode) ?  "Result: Found" : "Result: Not found") << endl;
            break;
            //insert sorted(a/d)
            case 's':
            break;
            //insert sorted and add(a/d)
            case '+':
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



