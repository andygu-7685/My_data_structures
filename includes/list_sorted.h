#ifndef LIST_SORTED_H
#define LIST_SORTED_H
#include "linked_list_functions.h"
#include <iostream>

using namespace std;

template <class T>
class List {
public:

    class Iterator {
    public:
        friend class List;                  // give access to List to access _ptr

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
                    cout << "list is empty" << endl;
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
                    cout << "list is empty" << endl;
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





    // Constructors and assignmnet--------------------------------------------------------------
    List(bool order = true, bool unique = false) // CTOR: default args
    {
        _head_ptr = nullptr;
        _order = order;
        _unique = unique;
        _size = 0;
    }

    List(const List<T>& copyThis) {
        _head_ptr = nullptr;
        _copy_list(_head_ptr, copyThis._head_ptr);
        _size = copyThis._size;
        _order = copyThis._order;
        _unique = copyThis._unique;
    }

    List& operator=(const List& RHS) {
        if (this != &RHS) { // Self-assignment check
            this->~List();
            _head_ptr = _copy_list(RHS._head_ptr);
            _order = RHS._order;
            _unique = RHS._unique;
            _size = RHS._size;
        }
        return *this;
    }

    ~List() {
        if(_size != -1){
            _clear_list(_head_ptr);
            _size = -1;
            _order = false;
            _unique = true;
        }
    }
    // Constructors and assignmnet--------------------------------------------------------------



    // Mutators---------------------------------------------------------------------------------
    friend List<T> operator+(const List<T>& Lst1, const List<T>& Lst2){
        List<T> retLst = Lst2;
        List<T>::Iterator insertPt = retLst.begin();
        for(List<T>::Iterator it = Lst1.begin(); it != Lst1.end(); it++)
            insert_before(insertPt, *it);
        return retLst;
    }

    //require determine the validity of return value before hand
    // friend T split_list(List<T>& Lst1, List<T>& Lst2){
    //     int postSize;
    //     T midItem = _split_list(Lst1._head_ptr, Lst2._head_ptr, postSize);
    //     Lst1._size = postSize;
    //     Lst2._size = postSize;
    //     return midItem;
    // }
    
    Iterator insert_before(Iterator it, const T& i) { // Insert i
        assert(_size != -1); 
        _size++;
        return _insert_before(_head_ptr, it.get_ptr(), i);
    }

    Iterator insert_after(Iterator it, const T& i) { // Insert i
        assert(_size != -1);
        _size++;
        return _insert_after(_head_ptr, it.get_ptr(), i);
    }

    Iterator insert_before(int index, const T& i) { // Insert i
        assert(_size != -1); 
        _size++;
        Iterator it = this->operator()(index);
        return _insert_before(_head_ptr, it.get_ptr(), i);
    }

    Iterator insert_after(int index, const T& i) { // Insert i
        assert(_size != -1);
        _size++;
        Iterator it = this->operator()(index);
        return _insert_after(_head_ptr, it.get_ptr(), i);
    }
    
    Iterator insert_sorted(const T& i) { // Insert i
        assert(_size != -1); 
        _size++;
        return _insert_sorted(_head_ptr, i, _order);
    }

    Iterator insert_and_add(const T& i) { // Insert i
        assert(_size != -1); 
        node<T>* found = _search_list(_head_ptr, i);
        if (!_unique && found) { // Unique mode and item already exists
            found->_item += i;
            return found;
        }
        else {
            _size++;
            return _insert_sorted(_head_ptr, i, _order);
        }
    }

    T Delete(List<T>::Iterator iMarker) { // delete node at marker
        assert(_size != -1); 
        T deleted_value = _delete_node(_head_ptr, iMarker._ptr);
        _size--;
        return deleted_value;
    }

    T Delete(int index) { // delete node at marker
        assert(_size != -1);
        Iterator iMarker = this->operator()(index);
        T deleted_value = _delete_node(_head_ptr, iMarker._ptr);
        _size--;
        return deleted_value;
    }

    Iterator search(const T& key) const { // return Iterator to node [key]
        assert(_size != -1); 
        return _search_list(_head_ptr, key);
    }

    int search_index(const T& key) const { // return index to node [key]
        assert(_size != -1); 
        return _search_list_index(_head_ptr, key);
    }
    // Mutators---------------------------------------------------------------------------------



    // Accessors---------------------------------------------------------------------------------
    const T& operator[](int index) const { // const version of the operator [ ]
        assert(_size != -1 && index < _size); 
        return _at(_head_ptr, index);
    }

    T& operator[](int index) {
        assert(_size != -1 && index < _size);
        return _at(_head_ptr, index);
    }

    const Iterator operator()(int index) const { // const version of the operator ()
        assert(_size != -1 && index < _size); 
        return _at_index(_head_ptr, index);
    }

    Iterator operator()(int index) {
        assert(_size != -1 && index < _size); 
        return _at_index(_head_ptr, index);
    }

    T front(){
        assert(!empty());
        return _head_ptr->_item; 
    }
//I
    T back(){ 
        assert(!empty());
        return *last_node();
    }

    Iterator begin() const {
        assert(_size != -1); 
        return _head_ptr;
    }

    Iterator end() const {
        assert(_size != -1); 
        return nullptr;
    }

    Iterator last_node() const {
        assert(_size != -1); 
        return _last_node(_head_ptr);
    }

    bool empty() const { 
        assert(_size != -1); 
        return _size == 0;
    }

    int size() const { return _size; }
    // Accessors---------------------------------------------------------------------------------


    
    // Output---------------------------------------------------------------------------------
    friend ostream& operator<<(ostream& outs, const List<T>& l){
        assert(l._size != -1); 
        _print_list(l._head_ptr);
        return outs;
    }

    //print list with current indicator
    void print(Iterator& current = Iterator()){
        assert(_size != -1); 
        print_list(_head_ptr, current.get_ptr());
    }
    // Output---------------------------------------------------------------------------------



private:
    node<T>* _head_ptr;
    bool _order;                //ascending == true, descending == false
    bool _unique;
    int _size;
};

#endif
