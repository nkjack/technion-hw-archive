//
// Created by noam on 11/7/17.
//

#ifndef HW_W1_SPLAY_H
#define HW_W1_SPLAY_H


#include "Node.h"

template<class T, class K>
class SplayTree{
    Node<T,K>* root;

    void updateParentForChildren(Node<T,K> *parent, Node<T,K> *left_child, Node<T,K> *right_child);
    void updateParentForSonFatherGrandF(Node<T,K>* father_node, Node<T,K>* son_node);
    Node<T,K>* rightZag(Node<T,K>* son_node);
    Node<T,K>* rightZagZag(Node<T,K>* son_node);
    Node<T,K>* rightZigZag(Node<T,K>* son_node);
    Node<T,K>* leftZig(Node<T,K>* son_node);
    Node<T,K>* leftZigZig(Node<T,K>* son_node);
    Node<T,K>* leftZigZag(Node<T,K>* son_node);
    Node<T,K>* findNode(Node<T,K>* current_node, K key);
    Node<T,K>* splay(Node<T,K>* node);
    Node<T,K>* findMax(Node<T,K>* node);
    Node<T,K>* findMin(Node<T,K>* node);
    SplayTree& joinTrees(SplayTree& T1, SplayTree& T2);
    void splitTree(SplayTree& outputT1, SplayTree& outputT2, K key);

public:
    SplayTree():root(nullptr){};
    SplayTree(Node<T,K>* root): root(root){};
    Node<T,K>* insertNode(T data,K key);
    void deleteNode(K key);
    Node<T,K>* findNode(K key);
    Node<T,K>* findMin();
    Node<T,K>* findMax();
};


#endif //HW_W1_SPLAY_H
