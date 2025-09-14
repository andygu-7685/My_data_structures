#ifndef BT_NODE_H
#define BT_NODE_H
#include <iomanip>
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

const int MAX_CHILD = 3;

template <typename T, int M = MAX_CHILD>
struct BTNode{
    vector<T> _item;
    vector<BTNode<T>*> _child;
    BTNode<T>* _parent;

    BTNode(vector<T> item = vector<T>(), vector<BTNode<T>*> child = vector<BTNode<T>*>(), BTNode<T>* parent = nullptr) 
        : _item(item) , _child(child), _parent(parent) {}

    friend ostream& operator<<(ostream& outs, const BTNode<T>& printMe){
        outs << " [";
        for(int i = 0; i < printMe._item.size(); i++)
            outs << printMe._item[i] << " ";
        outs << "] ";
        return outs;
    }

    bool _insert(T item, int index = 0){
        assert(index <= _item.size() && index <= _child.size() - 1);

        if(_child.size() != 0 && _item.size() != 0)
            _child.insert(_child.begin()+index+1, nullptr);
        else
            _child = {nullptr, nullptr};

        _item.insert(_item.begin()+index, item);
        if(_item.size() >= M) return false;
        
        return true;
    }

    bool _remove(int index = 0){
        if(index < _item.size() && index < _child.size() - 1) return false;
        if(_child.size() == 0 || _item.size() == 0) return false;
        
        _child.erase(_child.begin()+index+1);
        _item.erase(_item.begin()+index);

        if(_item.size() >= M) return false;
        
        return true;
    }

};

#endif