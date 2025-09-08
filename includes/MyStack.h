#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include <iomanip>
#include <cassert>

#include "linked_list_functions.h"
#include "node.h"
using namespace std;








template <typename T>
class Stack{
public:

    class Iterator{
    public:
        friend class Stack;                              //give access to list to access _ptr

        Iterator() : _ptr(nullptr) , _save(nullptr), end(2){} // default ctor
        Iterator(node<T>* p) : _ptr(p), _save(p), end(2) {} // Point Iterator to where p is pointing to
        bool is_null() { return _ptr == nullptr; } // true if _ptr is NULL
        node<T>* get_ptr() { return _ptr; }
        friend bool operator!=(const Iterator& left, const Iterator& right) { return left._ptr != right._ptr; } // true if left != right
        friend bool operator==(const Iterator& left, const Iterator& right) { return left._ptr == right._ptr; } // true if left == right

        T& operator*() { 
            assert(_ptr);
            return _ptr->_item; 
        }                                       // dereference operator

        T* operator->() { 
            assert(_ptr);
            return &_ptr->_item; 
        }                                       // member access operator

        const T& operator *()const{
            assert(_ptr);
            return _ptr->_item;
        }                        //dereference operator

        const T* operator ->()const{                       //member access operator
            assert(_ptr);
            return &_ptr->_item;
        }

        Iterator& operator=(const Iterator& rhs){
            if(this != &rhs){
                _ptr = rhs._ptr;
                _save = rhs._save;
                end = rhs.end;
            }
            return *this;
        }

        Iterator& operator++() { // member operator:  ++it; or  ++it = new_value
            if(_ptr){
                if(_ptr->_next == nullptr){
                    _save = _ptr;
                    _ptr = _ptr->_next;
                    end = 0;
                }
                else{
                    _ptr = _ptr->_next;
                    end = 2;
                }
            }
            else{
                if(end == 0){
                    cout << "++ reached end of list" << endl;
                    end = 0;
                }
                else if(end == 1){
                    _ptr = _save;
                    end = 2;
                }
            }
            return *this;
        }

        friend Iterator operator++(Iterator& it, int unused) { // friend operator: it++
            Iterator temp = it;
            ++it;
            return temp;
        }

        Iterator& operator--() { // member operator:  ++it; or  ++it = new_value
            if(_ptr){
                if(_ptr->_prev == nullptr){
                    _save = _ptr;
                    _ptr = _ptr->_prev;
                    end = 1;
                }
                else{
                    _ptr = _ptr->_prev;
                    end = 2;
                }
            }
            else{
                if(end == 1){
                    cout << "-- reached head of list" << endl;
                    end = 1;
                }
                else if(end == 0){
                    _ptr = _save;
                    end = 2;
                }
            }
            return *this;
        }

        friend Iterator operator--(Iterator& it, int unused) { // friend operator: it++
            Iterator temp = it;
            --it;
            return temp;
        }


    private:
        node<T>* _ptr; // pointer being encapsulated
        node<T>* _save; // save _ptr at end and head
        int end;         //which side is the iterator on, 0 = end or 1 = head, 2 = null
    };







    //Constructor and Assignment ---------------------------------------------------------------------
//I
    Stack(){
        _top = nullptr;
        _size = 0;
    }
//I
    Stack(const Stack<T>& copyMe){
        _top = _copy_list<T>(copyMe._top);
        _size = copyMe._size;
    }
//I
    ~Stack(){
        if(_size != -1){
            _clear_list<T>(_top);
            _size = -1;
        }
    }
//I
    Stack<T>& operator=(const Stack<T>& RHS){
        this->~Stack();
        _top = _copy_list<T>(RHS._top);
        _size = RHS._size;
    }
    //Constructor and Assignment ---------------------------------------------------------------------



    //Mutator -------------------------------------------------------------------------------------
    //I
    void push(T item){
        assert(_size != -1);
        _size++;
        _top = _insert_head<T>(_top, item);
    }
    //I
    T pop(){
        assert(!empty());
        _size--;
        return _delete_head<T>(_top);
    }
    //Mutator -------------------------------------------------------------------------------------



    //Accessor -------------------------------------------------------------------------------------
//I
    T top(){
        assert(!empty());
        return _top->_item; 
    }
//I
    Iterator begin() const{ 
        assert(_size != -1);
        return Iterator(_top); 
    }              //Iterator to the head node
//I
    Iterator end() const{ 
        assert(_size != -1);
        return Iterator(nullptr); 
    }                //Iterator to NULL

    const T& operator[](int index) const { // const version of the operator [ ]
        assert(_size != -1);
        return _at(_top, index);
    }

    T& operator[](int index) {
        assert(_size != -1);
        return _at(_top, index);
    }

    const Iterator operator()(int index) const { // const version of the operator ()
        assert(_size != -1); 
        return _at_index(_top, index);
    }

    Iterator operator()(int index) {
        assert(_size != -1); 
        return _at_index(_top, index);
    }
//I
    bool empty(){ 
        assert(_size != -1);
        return _top == nullptr; 
    }
//I
    int size() const { return _size; }
    //Accessor -------------------------------------------------------------------------------------



    //Output -------------------------------------------------------------------------------------
    friend ostream& operator<<(ostream& outs, const Stack<T>& printMe){
        assert(printMe._size != -1);
        node<T> *walker = printMe._top;
        while (walker!=nullptr){
            //if you are here, walker is not nullptr:
            outs << *walker;
            walker = walker->_next;
        }
        outs << "|||" << endl;
        return outs;
    }
    //print list with current indicator
    void print(Iterator& current = Iterator()){
        assert(_size != -1);
        print_list(_top, current.get_ptr());
    }
    //Output -------------------------------------------------------------------------------------



private:
    node<T>* _top;
    int _size;
};














#endif