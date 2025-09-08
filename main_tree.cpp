#include <iostream>
#include <iomanip>
#include <vector>

#include "C:\Users\agu4\Documents\MyProject\Doubly-linked-list\includes\binary_tree.h"
using namespace std;










int main(int argv, char** argc) {
    BinaryTree<int> root;
    bool found;
    bool getKey = true;
    char key;
    int num;

    while(getKey){
        cout << "[f] find, [a] insert, [d] delete" << endl;
        cout << "[q] quit" << endl;
        root.displayTree();
        cin >> key;
        key = tolower(key);
        switch(key){
            //find
            case 'f':
                cout << "Enter number you want find: ";
                cin >> num;
                found = root.search(num);
                cout << ((found) ?  "Result: Found" : "Result: Not found") << endl;
            break;
            //insert after
            case 'a':
                cout << "Enter number you want insert: ";
                cin >> num;
                root.insertNode(num);
            break;
            //delete
            case 'd':
                cout << "Enter number you want delete: ";
                cin >> num;
                root.remove(num);
            break;
            //copy
            case 'c':

            break;
            //clear
            case '~':

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



