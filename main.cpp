#include <iostream>
#include <iomanip>
#include <vector>

#include "C:\Users\agu4\Documents\CS8Projects\Test_Ground_full\includes\linked_list_functions.h"
using namespace std;










int main(int argv, char** argc) {
    node<int>* head = nullptr;
    node<int>* currentNode = nullptr;
    bool getKey = true;
    char key;
    int num;
    bool order = false;
    //search
    //insert after
    //insert before
    //delete
    //copy
    //clear
    //at
    //insert sorted(a/d)
    //insert sorted and add(a/d)
    //last node

    while(getKey){
        cout << "[f] find, [a] insert after, [b] insert before, [d] delete, [c] copy, [~] clear" << endl;
        cout << "[@] at, [s] insert sorted, [+] insert sorted and add, [l] last node, [q] quit" << endl;
        print_list<int>(head, currentNode);
        cin >> key;
        key = tolower(key);
        switch(key){
            //move right
            case '.':
            currentNode = _next_node<int>(head, currentNode);
            break;
            //move left
            case ',':
            currentNode = _previous_node<int>(head, currentNode);
            break;
            //find
            case 'f':
                cout << "Enter number you want find: ";
                cin >> num;
                currentNode = _search_list<int>(head, num);
                cout << ((currentNode) ?  "Result: Found" : "Result: Not found") << endl;
            break;
            //insert after
            case 'a':
                cout << "Enter number you want insert after: ";
                cin >> num;
                _insert_after<int>(head, currentNode, num);
            break;
            //insert before
            case 'b':
                cout << "Enter number you want insert before: ";
                cin >> num;
                _insert_before<int>(head, currentNode, num);
            break;
            //delete
            case 'd':
                _delete_node<int>(head, currentNode);
                currentNode = head;
            break;
            //copy
            case 'c':
                node<int>* dest;
                _copy_list<int>(dest, head);
                cout << "first copy: ";
                print_list(dest);
                _clear_list(dest);
                dest = _copy_list(head);
                cout << "second copy: ";
                print_list(dest);
                _clear_list(dest);
            break;
            //clear
            case '~':
                _clear_list(head);
                currentNode = head;
            break;
            //at
            case '@':
                cout << "Enter the index you want find: ";
                cin >> num;
                currentNode = _at_index(head, num);
                cout << ((currentNode) ?  "Result: Found" : "Result: Not found") << endl;
            break;
            //insert sorted(a/d)
            case 's':
                cout << "Enter the number you want insert sorted: ";
                cin >> num;
                cout << "Enter the order: [0] descending, [1] ascending ";
                cin >> key;
                (key != '0') ? order = true : order = false;
                _insert_sorted<int>(head, num, order);
            break;
            //insert sorted and add(a/d)
            case '+':
                cout << "Enter the number you want insert sorted and add: ";
                cin >> num;
                cout << "Enter the order: [0] descending, [1] ascending ";
                cin >> key;
                (key != '0') ? order = true : order = false;
                _insert_sorted_and_add<int>(head, num, order);
            break;
            //last node
            case 'l':
                currentNode = _last_node<int>(head);
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



