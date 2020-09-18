
#include <assert.h>
#include "SplayTree.h"

//********************************* PRIVATE FUNCTIONS *****************************//
//*********************************************************************************//
template<class T, class K>
void SplayTree<T, K>::updateParentForChildren(Node<T,K> *parent, Node<T,K> *left_child, Node<T,K> *right_child) {
    if (left_child) {
        left_child->parent = parent;
    }
    if (right_child) {
        right_child->parent = parent;
    }
};

template<class T, class K>
void SplayTree<T, K>::updateParentForSonFatherGrandF(Node<T,K> *father_node, Node<T,K> *son_node) {
    Node<T,K> *g_father = father_node->parent;
    son_node->parent = father_node->parent;
    father_node->parent = son_node;
    if (g_father) {
        if (g_father->l_child == father_node) {
            g_father->l_child = son_node;
        } else {
            g_father->r_child = son_node;
        }
    }
};

template<class T, class K>
Node<T,K> *SplayTree<T, K>::leftZig(Node<T,K> *son_node) {
    Node<T,K> *father_node = son_node->parent;
    father_node->l_child = son_node->r_child;
    son_node->r_child = father_node;
    updateParentForChildren(father_node, father_node->l_child, nullptr);
    updateParentForSonFatherGrandF(father_node, son_node);
    return son_node;
}

template<class T, class K>
Node<T,K> *SplayTree<T, K>::rightZag(Node<T,K> *son_node) {
    Node<T,K> *father_node = son_node->parent;
    father_node->r_child = son_node->l_child;
    son_node->l_child = father_node;
    updateParentForChildren(father_node, nullptr, father_node->r_child);
    updateParentForSonFatherGrandF(father_node, son_node);
    return son_node;
}

template<class T, class K>
Node<T,K> *SplayTree<T, K>::leftZigZig(Node<T,K> *son_node) {
    son_node = leftZig(son_node);
    son_node = leftZig(son_node);
    Node<T,K> *grandson = son_node->r_child->l_child;
    if (grandson) {
        leftZig(grandson);
    }
    return son_node;
    /**
    Node *father_node = gp_node->l_child;
    Node *son_node = father_node->l_child;
    gp_node->l_child = son_node->r_child;
    father_node->r_child = gp_node;
    father_node->l_child = son_node->r_child;
    son_node->r_child = father_node;
    **/

    /**
    Node *bigParent = gp_node->parent;
    son_node->parent = gp_node->parent;
    father_node->parent = son_node;
    gp_node->parent = father_node;
    if (bigParent) {
        if (bigParent->l_child = gp_node) {
            bigParent->l_child = son_node;
        } else {
            bigParent->r_child = son_node;
        }
    }
     */
}

template<class T, class K>
Node<T,K> *SplayTree<T, K>::rightZagZag(Node<T,K> *son_node) {
    son_node = rightZag(son_node);
    son_node = rightZag(son_node);
    Node<T,K> *grandson = son_node->l_child->r_child;
    if (grandson) {
        rightZag(grandson);
    }
    return son_node;
    /**
    Node *father_node = gp_node->r_child;
    Node *son_node = father_node->r_child;
    father_node->r_child = son_node->l_child;
    gp_node->r_child = father_node->l_child;
    son_node->l_child = father_node;
    father_node->l_child = gp_node;
    return son_node;
     */
}

template<class T, class K>
Node<T,K> *SplayTree<T, K>::leftZigZag(Node<T,K> *son_node) {
    son_node = rightZag(son_node);
    son_node = leftZig(son_node);
    return son_node;

    /**
    Node *father_node = gp_node->l_child;
    Node *son_node = father_node->r_child;
    father_node->r_child = son_node->l_child;
    gp_node->l_child = son_node->r_child;
    son_node->r_child = gp_node;
    son_node->l_child = father_node;
    */
    /**
    Node *bigParent = gp_node->parent;
    son_node->parent = gp_node->parent;
    father_node->parent = son_node;
    gp_node->parent = father_node;
    if (bigParent) {
        if (bigParent->l_child = gp_node) {
            bigParent->l_child = son_node;
        } else {
            bigParent->r_child = son_node;
        }
    }
     */
    //return son_node;
}

template<class T, class K>
Node<T,K> *SplayTree<T, K>::rightZigZag(Node<T,K> *son_node) {
    son_node = leftZig(son_node);
    son_node = rightZag(son_node);
    return son_node;
    /**
    Node *father_node = gp_node->r_child;
    Node *son_node = father_node->l_child;
    father_node->l_child = son_node->r_child;
    gp_node->r_child = son_node->l_child;
    son_node->r_child = father_node;
    son_node->l_child = gp_node;
    return son_node;
     */
}

template<class T, class K>
Node<T,K> *SplayTree<T,K>::splay(Node<T,K> *node) {
    if (!node) {
        //TODO- throw exception
    }
    if (node == root) {
        return node;
    }
    if (node->hasGrandParent()) {
        if (node->isLeftChild()) {
            // left zig zig
            if (node->parent->isLeftChild()) {
                node = leftZigZig(node);
                return splay(node);
            }
            // right zig zag
            else {
                node = rightZigZag(node);
                return splay(node);
            }
        }
        else {
            // left zig zag
            if (node->parent->isLeftChild()) {
                node = leftZigZag(node);
                return splay(node);
            }
            //  right zag zag
            else {
                node = rightZagZag(node);
                return splay(node);
            }
        }
    }
    else if (node->hasParent()) {
        if (node->isLeftChild()) {
            node = leftZig(node);
            return node;
        }
        else {
            node = rightZag(node);
            return node;
        }
    }
}

template<class T, class K>
Node<T,K> *SplayTree<T,K>::findNode(Node<T,K> *current_node, K key) {
    if (current_node->key == key) {
        root = splay(current_node);
        return root;
    }
    // key belongs to the left tree
    /**if (current_node->key < key) {*/// other way?
    if (current_node->key > key) {
        // if left child is null
        if (!current_node->l_child) {
            root = splay(current_node);
            return root;
        }
        return findNode(current_node->l_child, key);
    }
        //key belongs to the right tree
    /**else if (current_node->key > key) { */
    else if (current_node->key < key) {
            // if right child is null
        if (!current_node->r_child) {
            root = splay(current_node);
            return root;
        }
        return findNode(current_node->r_child, key);
    }
    return root;
}

template<class T,class K>
Node<T,K>* SplayTree<T,K>::findMin(Node<T,K>* node){
    if (!node){
        //throw exception
    }
    else if(!node->l_child){
        root = splay(node);
        return root;
    }
    return findMin(node->l_child);
}

template<class T,class K>
Node<T,K>* SplayTree<T,K>::findMax(Node<T,K>* node){
    if (!node){
        //throw exception
    }
    else if(!node->r_child){
        root = splay(node);
        return root;
    }
    return findMax(node->r_child);
}

/*
 * Functions splays max value of given left tree, assuring no values are bigger then the root.
 * the right son of that root becomes the given right tree.
*/
template<class T, class K>
SplayTree<T,K>& SplayTree<T,K>::joinTrees(SplayTree<T,K>& T1, SplayTree<T,K>& T2){
    root = T1.findMax();
    root ->r_child = T2.root;
    return *this;
};
/*
 * Functions splays Key or nearest value, then cuts tree into two separate trees.
 * @param outputT1 - Node*, is the left tree  holding all keys <= key.
 * @param outputT1 - Node*, is the right tree  holding all keys > key.
 */
template<class T, class K>
void SplayTree<T,K>::splitTree(SplayTree& outputT1, SplayTree& outputT2, K key){
    root = findNode(key);
    if (root ->data > key){
        outputT1.root = root->l_child;
        outputT1.root ->parent = nullptr;
        root ->l_child = nullptr;
        outputT2.root = root;
    }
    else {
        outputT2.root = root ->r_child;
        outputT2.root ->parent = nullptr;
        root ->r_child = nullptr;
        outputT1.root = root;
    }
};


//********************************* PUBLIC FUNCTIONS ******************************//
//*********************************************************************************//
template<class T, class K>
Node<T,K> *SplayTree<T, K>::findNode(K key) {
    // empty tree
    if (root == nullptr) {
        return root;
    }
    Node<T,K> *node_to_return = findNode(root, key);
    if (node_to_return->key == key) {
        return node_to_return;
    } else {
        //the node is not in the tree, we splayed the last node before null
        // maybe throw exception?
        return nullptr;
    }
}

template<class T, class K>
Node<T,K>* SplayTree<T,K>::findMin() {
    // empty tree
    if (root == nullptr) {
        return root;
        //maybe better to throw exception
    }
    Node<T,K>* node = findMin(root);
    return node;
}
template<class T, class K>
Node<T,K>* SplayTree<T,K>::findMax() {
    // empty tree
    if (root == nullptr) {
        return root;
        //maybe better to throw exception
    }
    Node<T,K>* node = findMax(root);
    return node;
}

template<class T, class K>
Node<T,K>* SplayTree<T,K>::insertNode(T data,K key){
    SplayTree left;
    SplayTree right;
    splitTree(left, right, key);
    root =  new Node<T,K>(data, key, left.root, right.root);
    return root;
}

template<class T, class K>
void SplayTree<T,K>::deleteNode(K key){
    SplayTree left;
    SplayTree right;
    splitTree(left, right, key);
    if (left.root ->key == key) {
        Node<T,K>* tmp = left.root;
        left.root = left.root ->l_child;
        left.root ->parent = nullptr;
        delete tmp;
    }
    joinTrees(left, right);
}

