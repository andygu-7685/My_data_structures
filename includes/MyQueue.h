#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include "linked_list_functions.h"
#include "node.h"
using namespace std;




template <typename T>
class Queue
{
public:

    class Iterator{
    public:
        friend class Queue;                              //give access to list to access _ptr

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
    Queue(){
        _front = nullptr;
        _rear = nullptr;
        _size = 0;
    }
//I
    Queue(const Queue<T>& copyMe){
        _rear = _copy_list<T>(_front, copyMe._front);
        _size = copyMe._size;
    }
//I
    ~Queue(){
        if(_size != -1){
            _clear_list<T>(_front);
            _size = -1;
        }
    }
//I
    Queue& operator=(const Queue<T>& RHS){
        this->~Queue();
        _rear = _copy_list<T>(_front, RHS._front);
        _size = RHS._size;
        return *this;
    }
    //Constructor and Assignment ---------------------------------------------------------------------



    //Mutator ---------------------------------------------------------------------
    //I
    void push(T item){
        assert(_size != -1); 
        _size++;
        //cout << "\npush fired: \n";
        _rear = _insert_after(_front, _rear, item);
    }
    //I
    T pop(){
        assert(!empty());
        _size--;
        //cout << "\npop fired: \n";
        if(_front == _rear){
            _rear = nullptr;
            return _delete_head(_front);
        }
        return _delete_head(_front);
    }
    //Mutator ---------------------------------------------------------------------



    //Accessors ---------------------------------------------------------------------
//I
    T front(){ 
        assert(!empty());
        return _front->_item; 
    }
//I
    T back(){ 
        assert(!empty());
        return _rear->_item;
    }
//I
    Iterator begin() const{ 
        assert(_size != -1); 
        return Iterator(_front); 
    }           

    Iterator end() const{ 
        assert(_size != -1); 
        return Iterator(nullptr); 
    }              

    const T& operator[](int index) const { // const version of the operator [ ]
        assert(_size != -1); 
        return _at(_front, index);
    }

    T& operator[](int index) {
        assert(_size != -1); 
        return _at(_front, index);
    }

    const Iterator operator()(int index) const { // const version of the operator ()
        assert(_size != -1); 
        return _at_index(_front, index);
    }

    Iterator operator()(int index) {
        assert(_size != -1); 
        return _at_index(_front, index);
    }
//I
    bool empty(){
        assert(_size != -1); 
        return _size == 0; 
    }
//I
    int size() const { return _size; }
    //Accessors ---------------------------------------------------------------------


    //Ouput -------------------------------------------------------------------------
    friend ostream& operator << (ostream& outs, const Queue<T>& printMe){
        assert(printMe._size != -1);
        _print_list(printMe._front);
        return outs;
    }
    //print list with current indicator
    void print(Iterator& current = Iterator()){
        assert(_size != -1);
        print_list(_front, current.get_ptr());
    }
    //Ouput -------------------------------------------------------------------------



private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};


















#endif