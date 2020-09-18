//
// Created by noam on 12/31/17.
//

#ifndef HW_WET2_SPLAYNODE_H
#define HW_WET2_SPLAYNODE_H

#include <stdio.h>

/**
 * The SplayNode Class is used in the SplayRankTree as a node in the tree. As we can
 * see the node is a generic node with D for data and S for Key. In addition to a
 * regular node in a tree data stracture this node contains two important variables.
 * sumNodes - the amount of nodes in the subTree of the current Node.
 * WeightScore - the weight of the score in the subTree of the curren Node.
 * Those two variables are necessary in order to implement the funciontality of a
 * RankTree.
 * @tparam D - data of the node.
 * @tparam S - key of the node.
 */
template<class D, class S>
class SplayNode {
    D data; // a pointer that needs to be release
    S key;
    int sumNodes;
    S weightScore;
    SplayNode<D, S> *l_child;
    SplayNode<D, S> *r_child;
    SplayNode<D, S> *parent;

    template<class T, class K> friend
    class SplayRankTree;

public:
    SplayNode(D data, S key, SplayNode *lchild, SplayNode *rchild) : data(data),
                                                      key(key),
                                                      l_child(lchild),
                                                      r_child(rchild),
                                                      weightScore(key),
                                                      parent(NULL){
    }

    SplayNode(D element, S key) : data(element), key(key), weightScore(key),
                                            l_child(NULL),
                                            r_child(NULL), parent(NULL) {};

    SplayNode() : l_child(NULL), r_child(NULL), parent(NULL) {};

    ~SplayNode() {
        delete data;
        l_child = NULL;
        r_child = NULL;
        parent = NULL;
    };

    bool hasParent();

    bool hasGrandParent();

    bool isLeftChild();

    bool operator==(const SplayNode<D, S> &node) const { return node.key ==
                this->key; }

    bool operator<(const SplayNode<D, S> &rhs) { return this->key < rhs.key; }

    bool operator>(const SplayNode<D, S> &rhs) { return rhs < *this; }

    bool operator<=(const SplayNode<D, S> &rhs) { return !(rhs < *this); }

    bool operator>=(const SplayNode<D, S> &rhs) { return !(*this < rhs); }

    S operator*(const SplayNode<D, S> &node) { return key; }

    D getData() const;

    S getKey() const;

    S getWeight() const;

    int getSumNodes() const;

    SplayNode<D, S> *getL_child() const;

    SplayNode<D, S> *getR_child() const;

    SplayNode<D, S> *getParent() const;
};//End of class SplayNode
/**NODE*/

template<class D, class S>
bool SplayNode<D, S>::hasParent() {
    if (parent) {
        return true;
    }
    return false;
}

template<class D, class S>
bool SplayNode<D, S>::hasGrandParent() {
    if (hasParent()) {
        if (parent->parent) {
            return true;
        }
    }
    return false;
}

template<class D, class S>
bool SplayNode<D, S>::isLeftChild() {
    if (parent) {
        if ((parent->l_child) == this) {
            return true;
        }
    }
    return false;
}

template<class D, class S>
D SplayNode<D, S>::getData() const {
    return data;
}

template<class D, class S>
S SplayNode<D, S>::getKey() const {
    return key;
}

template<class D, class S>
S SplayNode<D, S>::getWeight() const {
    return weightScore;
}

template<class D, class S>
int SplayNode<D, S>::getSumNodes() const {
    return sumNodes;
}

/** TESTING FUNCTIONS **/
template<class D, class S>
SplayNode<D, S> *SplayNode<D, S>::getL_child() const {
    return l_child;
}

template<class D, class S>
SplayNode<D, S> *SplayNode<D, S>::getR_child() const {
    return r_child;
}

template<class D, class S>
SplayNode<D, S> *SplayNode<D, S>::getParent() const {
    return parent;
}

#endif //HW_WET2_SPLAYNODE_H
