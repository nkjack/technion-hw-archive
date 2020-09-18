//
// Created by noam on 11/7/17.
//

#ifndef HW_W1_NODE_H
#define HW_W1_NODE_H

template<class T, class K>
class Node {
    T data;
    K key;
    Node *l_child;
    Node *r_child;
    Node *parent;

    friend class SplayTree;

public:
    Node(T data, K key, Node *lchild, Node *rchild) : data(data),
                                                      key(key),
                                                      l_child(lchild),
                                                      r_child(rchild),
                                                      parent(nullptr) {}

    Node(T element) : data(element) {};

    ~Node() = default;

    bool hasParent();
    bool hasGrandParent();
    bool isLeftChild();
    bool operator==(const Node &node) const {
        return node.key == this->key;
    }

    bool operator<(const Node &rhs){
        return this ->key < rhs.key;
    }

    bool operator>(const Node &rhs){
        return rhs < this;
    }

    bool operator<=(const Node &rhs){
        return !(rhs < this);
    }

    bool operator>=(const Node &rhs){
        return !(this < rhs);
    }
};

template<class T, class K>
bool Node<T,K>::hasParent() {
    if (parent){
        return true;
    }
    return false;
}

template<class T, class K>
bool Node<T,K>::hasGrandParent(){
    if (hasParent()){
        if (parent->parent){
            return true;
        }
    }
    return false;
}

template<class T, class K>
bool Node<T,K>::isLeftChild() {
    if (parent){
        if (parent->l_child == this){
            return true;
        }
    }
    return false;
}
#endif //HW_W1_NODE_H
