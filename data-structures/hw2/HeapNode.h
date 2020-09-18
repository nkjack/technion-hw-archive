//
// Created by noam on 1/1/18.
//

#ifndef HW_WET2_HEAPNODE_H
#define HW_WET2_HEAPNODE_H


#include <stdio.h>

template<class D, class S>
class HeapNode{
    D data; // a pointer that need to be release
    S key;
    HeapNode<D, S> *l_child;
    HeapNode<D, S> *r_child;
    HeapNode<D, S> *parent;

    template<class T, class K>
    friend class Heap;

public:
    HeapNode(D data, S key, HeapNode *parent) : data(data), key(key), l_child(NULL), r_child(NULL), parent(parent) {}

    HeapNode() : l_child(NULL), r_child(NULL), parent(NULL) {};

    ~HeapNode() {
        //delete data;
        l_child = NULL;
        r_child = NULL;
        parent = NULL;
    };

    bool isLeftChild() { return parent && parent -> l_child == this;}

    bool operator==(const HeapNode<D, S> &node) const { return node.key == this->key;}

    bool operator<(const HeapNode<D, S> &rhs) { return this->key < rhs.key;}

    bool operator>(const HeapNode<D, S> &rhs) { return rhs < *this;}

    bool operator<=(const HeapNode<D, S> &rhs) { return !(rhs < *this);}

    bool operator>=(const HeapNode<D, S> &rhs) { return !(*this < rhs);}

    S operator*(const HeapNode<D, S> &node) { return key;}

    D getData() const { return data;}

    S getKey() const{ return key;}

};//End of class HeapNode

#endif //HW_WET2_HEAPNODE_H
