//
// Created by noam on 12/31/17.
//

#ifndef HW_WET2_SPLAYRANKTREE_H
#define HW_WET2_SPLAYRANKTREE_H

#include <stdio.h>
#include <ostream>

#include "SplayNode.h"
#include "Exceptions.h"


template<class T, class K>
class SplayRankTree {
    SplayNode<T, K> *root;

    int sum_nodes;

    /**
     * private function that update the parent pointer of a right child node.
     * @param parent - Node pointer reference
     * @param right_child - Node Pointer reference
     */
    void updateParentForRightChild(SplayNode<T, K> *&parent, SplayNode<T, K> *&right_child);
    /**
     * private function that update the parent pointer of a left child node.
     * @param parent - Node pointer reference
     * @param left_child - Node pointer reference
     */
    void updateParentForLeftChild(SplayNode<T, K> *&parent, SplayNode<T, K> *&left_child);

    /**
     * private function that helps with updating the pointers in a ZigZig or ZigZag
     * rotations were we have also the GrandParent the father and the son to update
     * their parents according to their new positions in the tree.
     * @param father_node - Node pointer reference
     * @param son_node - Node pointer reference
     */
    void updateParentForSonFatherGrandF(SplayNode<T, K> *&father_node,
                                        SplayNode<T, K> *&son_node);

    /**
     * This function update a node for it weight variables. The node has 2 variables
     * that indicate about Weight - sum of nodes, weightScore. Those 2 variables need
     * to be updated when a node is doing Zig or Zag. This function Update those
     * variables according to the sons of the node. Takes O(1) time.
     * @param node - the node that the funciton update.
     */
    void updateWeight(SplayNode<T, K> *&node);
    /**
     * left rotation according to the Lectures in Class. This function update the
     * neccessary pointers of each node, in order to keep the Tree as it suppose to be.
     * In addition it updates the node weight variables - sumNodes, WeighScore.
     * @param son_node - Node pointer.
     * @return son_node pointer - now with the new location
     */
    SplayNode<T, K> *leftZig(SplayNode<T, K> *son_node);

    /**
     * right rotation according to the Lectures in Class. This function update the
     * neccessary pointers of each node, in order to keep the Tree as it suppose to be.
     * In addition it updates the node weight variables - sumNodes, WeighScore.
     * @param son_node - Node pointer.
     * @return son_node pointer - now with the new location
     */
    SplayNode<T, K> *rightZag(SplayNode<T, K> *son_node);

    /**
     * This rotation is getting done in the function with a combinations of 2 right Zag
     * on the son_node itself and rightZag on its grandson if it has one.
     * @param son_node - Node pointer
     * @return son_node pointer - now with the new location
     */
    SplayNode<T, K> *rightZagZag(SplayNode<T, K> *son_node);

    /**
     * This rotation is getting done in the function with a combinations of right Zag
     * and leftZig on the son_node itself.
     * @param son_node - Node pointer
     * @return son_node pointer - now with the new location
     */
    SplayNode<T, K> *rightZigZag(SplayNode<T, K> *son_node);

    /**
     *This rotation is getting done in the function with a combinations of 2 leftZig
     * on the son_node itself and leftZag on its grandson if it has one.
     * @param son_node - Node pointer
     * @return son_node pointer - now with the new location
     */
    SplayNode<T, K> *leftZigZig(SplayNode<T, K> *son_node);

    /**
    * This rotation is getting done in the function with a combinations of left Zig
    * and rightZag on the son_node itself.
    * @param son_node - Node pointer
    * @return son_node pointer - now with the new location
    */
    SplayNode<T, K> *leftZigZag(SplayNode<T, K> *son_node);

    /**
     * The splay function get a Node pointer of a Node in the tree, and rotate it
     * according to the lecture rules up to the root.
     * if NULL than the return value will be NULL;
     * @param node - Node pointer
     * @return the node Pointer- now in the root.
     */
    SplayNode<T, K> *splay(SplayNode<T, K> *node);

    /**
     * This function will return the Node we are looking for from the SplayTree in O(h)
     * = O(log(n)) according to the hw conditions. It is a simple binary search,
     * because we assume the tree has an order inside. The function will try to find
     * the node with the inputed key, and if not will stop in the last stage of
     * recursion, means the 'father' of the inputed key. Than it will splay the node to
     * the root of the tree.
     *
     * @param current_node - the current root of the recursion.
     * @param key - the parameter to search the node with
     * @return a pointer for the founded node.
     */
    SplayNode<T, K> *findNode(SplayNode<T, K> *current_node, K key);

    /**
     * This function use a simple recursion to find the maximum node in the tree. It
     * will keep going left in the tree until it will find the last right node. We
     * assume the tree is in order.
     *
     * @param node - the current root node of the recursion
     * @return the pointer of the maximum node.
     */
    SplayNode<T, K> *findMax(SplayNode<T, K> *node);

    /**
     * This function use a simple recursion to find the maximum node in the tree. It
     * will keep going left in the tree until it will find the last right node. We
     * assume the tree is in order.
     *
     * @param node - the current root node of the recursion
     * @return the pointer of the maximum node.
     */
    SplayNode<T, K> *findMin(SplayNode<T, K> *node);

    /**
     * This function join two trees into one. The first tree is the root we have, and
     * the second tree is the one that transfer as an input param. if root is null the
     * the right tree is set to be root. otherwise, the right tree is set to be the
     * right child of the root we have (the left tree).
     * @param rightTree
     */
    void joinTrees(SplayNode<T, K> *&rightTree);

    /**
     * This function will split the Tree into two trees around the value of Key input
     * param. First it will use the FindNode function that will find the node with the
     * inputed key according to our findNode function, and will splay it up to the root.
     * Be aware that the root after finding the node, doesn't have to be the equal with
     * the key param (if the Node is not exists - happens in successful insertNode).
     * Than we split the Tree around the value of Key and set the pointers into the
     * leftOutput and rightOutput params accordingly.
     *
     * @param key - the parameter split the tree around
     * @param leftOutput - the Pointer of the Node that will represent the root of the
     *                      leftOutputed tree
     * @param rightOutput - the Pointer of the Node that will represent the root of the
     *                      rightOutputed tree
     */
    void splitTree(K key, SplayNode<T, K> *&leftOutput, SplayNode<T, K> *&rightOutput);

    void inorderData(std::ostream &os, SplayNode<T, K> *node) const;

    /**
     * Delete tree is a function the delete all the nodes of the SplayTree in O(n).
     * It is done in recursion. first deleting the left tree, than the right tree, and
     * then deleting the root node. The function is not using any  of the Tree
     * rotations therfore keeping the complexity in O(n)
     */
    void deleteTree(SplayNode<T, K> *root_tree);

    /**
     * This function get a root (node) of a splay tree, and index that represent a
     * vertex in the SplayTree, and r_score that will be changed accordingly through
     * the recursive calls. This function return the Sum of Keys of all the vertexes
     * that are bigger or equal than the index that was inputed.
     * @param node - the root of the SplayTree we oprate in.
     * @param index - the index of the vertex we want to search.
     * @param r_score - the total score the function will return (type Key)
     * @throw NotEnoughNodesException - if there are not enough nodes in the tree.
     * @return will return the score of all the nodes that are bigger or equal to index.
     */
    K getSumScoreOfKBestNodes(SplayNode<T, K>* node, int index, K r_score) const;

public:

    SplayRankTree() : root(NULL), sum_nodes(0) {};

    SplayRankTree(SplayNode<T, K> *node, int sum_nodes) : root(node), sum_nodes
            (sum_nodes) {};

    ~SplayRankTree();

    /**
     * insertNode functions is getting a Data and a Key, data is from type T (a pointer)
     * and Key is from type K. the function will first find the node in the tree with
     * the inputed key. The function first will operate the find function, and will splay
     * the finded node up to the root. If the node root has the same key has the
     * inputed key it will throw Exception. otherwise, it will split the tree for two,
     * set the node as a root for the left tree, and join the two trees into one.
     *
     * this function is O(log(n)) according to the wet conditions.
     * @param data - value of the node (pointer)
     * @param key - key of the node
     */
    void insertNode(T data, K key);

    /**
     * this function will delete the node with the inputed Key in O(log(n)) according
     * to the wet conditions. First it will find the node with the inputed Key, than it
     * will splay the founded node ( be aware, that the founded node can be different).
     * if the founded node is what we are looking for, than the function will split the
     * tree, delete the node of the left tree root, and join the trees into one.
     *
     * @param key - for searching the node.
     */
    void deleteNode(K key);

    /**
     * This function will return the Node we are looking for from the SplayTree in O(h)
     * = O(log(n)) according to the hw conditions. It is a simple binary search,
     * because we assume the tree has an order inside. The function will try to find
     * the node with the inputed key, and if not will stop in the last stage of
     * recursion, means the 'father' of the inputed key. Than it will splay the node to
     * the root of the tree.
     *
     * @param key - the parameter to search the node with
     * @return a pointer for the founded node.
     */
    SplayNode<T, K> *findNode(K key);

    /**
     * This function use a simple recursion to find the minimum node in the tree. It
     * will keep going right in the tree until it will find the last right node. We
     * assume the tree is in order.
     *
     * @return the pointer of the minimum node.
     */
    SplayNode<T, K> *findMin();

    /**
     * This function use a simple recursion to find the maximum node in the tree. It
     * will keep going left in the tree until it will find the last right node. We
     * assume the tree is in order.
     *
     * @return the pointer of the maximum node.
     */
    SplayNode<T, K> *findMax();

    /**
     * This function will return the value of the Root of the SplayTree. this function
     * is helpful for several tests, and works upon the the Tree.
     * @return Value of the Root node (pointer)
     */
    T getRootVal();

    /**
     * @return Returning the root node of the SplayTree.
     */
    SplayNode<T, K> *getRoot(); // for testing

    /**
     * inorderPrintData is a function that will print the values of the tree in a inorder
     * traversal. This function is mainely for tests reasons.
     * @param os - ostream
     */
    void inorderPrintData(std::ostream &os) const;

    /**
     * Delete tree is a function the delete all the nodes of the SplayTree in O(n).
     * It is done in recursion. first deleting the left tree, than the right tree, and
     * then deleting the root node. The function is not using any  of the Tree
     * rotations therfore keeping the complexity in O(n)
     */
    void deleteTree();

    /**
     * @return the amount of nodes in O(1).
     */
    int getSum_nodes() const;

    /**
     * Check if there is a node with the inputed key in the tree.
     * @param key
     * @return True if there is, false otherwise
     */
    bool isNodeInside(K key) ;
    K getSumScoreOfKBestNodes(int k) const;

    friend std::ostream &
    operator<<(std::ostream &output, const SplayRankTree<T, K> &splayTree) {
        splayTree.inorderPrintData(output);
        return output;
    };
};

//################################### PRIVATE FUNCTIONS ################################
//######################################################################################


/**
 * TESTING FUNCTIONS
 */
template<class T, class K>
SplayNode<T, K> *SplayRankTree<T, K>::getRoot() {
    return root;
};

/** SPLAY TREE */
template<class T, class K>
void SplayRankTree<T, K>::inorderPrintData(std::ostream &os) const {
    inorderData(os, root);
}

template<class T, class K>
void SplayRankTree<T, K>::inorderData(std::ostream &os, SplayNode<T, K> *node) const {
    if (node == NULL) {
        return;
    }
    inorderData(os, node->l_child);
    os << *node->data << " ";
    inorderData(os, node->r_child);
}


template<class T, class K>
void SplayRankTree<T, K>::updateParentForLeftChild(SplayNode<T, K> *&parent,
                                               SplayNode<T, K> *&left_child) {
    if (left_child) {
        left_child->parent = parent;
    }
}

template<class T, class K>
void SplayRankTree<T, K>::updateParentForRightChild(SplayNode<T, K> *&parent,
                                                SplayNode<T, K> *&right_child) {

    if (right_child) {
        right_child->parent = parent;
    }
}

template<class T, class K>
void SplayRankTree<T, K>::updateParentForSonFatherGrandF(SplayNode<T, K> *&father_node,
                                                     SplayNode<T, K> *&son_node) {
    SplayNode<T, K> *g_father = father_node->parent;
    son_node->parent = g_father;
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
void SplayRankTree<T, K>::updateWeight(SplayNode<T, K> *&node) {
    if (node) {
        int temp_sum_nodes = 1;
        K temp_weight = node->getKey();
        if (node->l_child){
            temp_sum_nodes += node->l_child->sumNodes;
            temp_weight += node->l_child->weightScore;
        }
        if (node->r_child){
            temp_sum_nodes += node->r_child->sumNodes;
            temp_weight += node->r_child->weightScore;
        }
        node->sumNodes = temp_sum_nodes;
        node->weightScore = temp_weight;
    }
}

template<class T, class K>
SplayNode<T, K> *SplayRankTree<T, K>::leftZig(SplayNode<T, K> *son_node) {
    SplayNode<T, K> *father_node = son_node->parent;
    father_node->l_child = son_node->r_child;
    son_node->r_child = father_node;
    updateParentForLeftChild(father_node, father_node->l_child);
    updateParentForSonFatherGrandF(father_node, son_node);
    if (son_node->parent == NULL) {
        root = son_node;
    }
    updateWeight(father_node);
    updateWeight(son_node);
    return son_node;
}

template<class T, class K>
SplayNode<T, K> *SplayRankTree<T, K>::rightZag(SplayNode<T, K> *son_node) {
    SplayNode<T, K> *father_node = son_node->parent;
    father_node->r_child = son_node->l_child;
    son_node->l_child = father_node;
    updateParentForRightChild(father_node, father_node->r_child);
    updateParentForSonFatherGrandF(father_node, son_node);
    if (son_node->parent == NULL) {
        root = son_node;
    }
    updateWeight(father_node);
    updateWeight(son_node);
    return son_node;
}

template<class T, class K>
SplayNode<T, K> *SplayRankTree<T, K>::rightZagZag(SplayNode<T, K> *son_node) {
    son_node = rightZag(son_node);
    son_node = rightZag(son_node);
    SplayNode<T, K> *grandson = son_node->l_child->r_child;
    if (grandson) {
        rightZag(grandson);
    }
    return son_node;
}

template<class T, class K>
SplayNode<T, K> *SplayRankTree<T, K>::rightZigZag(SplayNode<T, K> *son_node) {
    son_node = leftZig(son_node);
    son_node = rightZag(son_node);
    return son_node;
}

template<class T, class K>
SplayNode<T, K> *SplayRankTree<T, K>::leftZigZig(SplayNode<T, K> *son_node) {
    son_node = leftZig(son_node);
    son_node = leftZig(son_node);
    SplayNode<T, K> *grandson = son_node->r_child->l_child;
    if (grandson) {
        leftZig(grandson);
    }
    return son_node;
}

template<class T, class K>
SplayNode<T, K> *SplayRankTree<T, K>::leftZigZag(SplayNode<T, K> *son_node) {
    son_node = rightZag(son_node);
    son_node = leftZig(son_node);
    return son_node;
}

template<class T, class K>
SplayNode<T, K> *SplayRankTree<T, K>::splay(SplayNode<T, K> *node) {
    if (!node) {
        return NULL;
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
        } else {
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
    } else if (node->hasParent()) {
        if (node->isLeftChild()) {
            node = leftZig(node);
            return node;
        } else {
            node = rightZag(node);
            return node;
        }
    }
    return NULL;
}

template<class T, class K>
SplayNode<T, K> *SplayRankTree<T, K>::findNode(SplayNode<T, K> *current_node, K key) {
    if (current_node->key == key) {
        root = splay(current_node);
        return root;
    }
    // key belongs to the left tree
    if (current_node->key > key) {
        // if left child is null
        if (!current_node->l_child) {
            root = splay(current_node);
            return root;
        }
        return findNode(current_node->l_child, key);
    }
        //key belongs to the right tree
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

template<class T, class K>
SplayNode<T, K> *SplayRankTree<T, K>::findMax(SplayNode<T, K> *node) {
    if (!node) {
        return NULL;
    } else if (!node->r_child) {
        root = splay(node);
        return root;
    }
    return findMax(node->r_child);
}

template<class T, class K>
SplayNode<T, K> *SplayRankTree<T, K>::findMin(SplayNode<T, K> *node) {
    if (!node) {
        return NULL;
    } else if (!node->l_child) {
        root = splay(node);
        return root;
    }
    return findMin(node->l_child);
}

/* Functions splays max value of given left tree, assuring no values are bigger then the root.
  * the right son of that root becomes the given right tree. */
template<class T, class K>
void SplayRankTree<T, K>::joinTrees(SplayNode<T, K> *&rightTree) {
    findMax();

    if (!root) {
        root = rightTree;
    } else {
        root->r_child = rightTree;
        if (rightTree) {
            rightTree->parent = root;
            root->sumNodes+= rightTree->sumNodes;
            root->weightScore += rightTree->weightScore;
        }
    }
}

/* Functions splays Key or nearest value, then cuts tree into two separate trees.
 * @param outputT1 - Node*, is the left tree  holding all keys <= key.
 * @param outputT1 - Node*, is the right tree  holding all keys > key.*/
template<class T, class K>
void SplayRankTree<T, K>::splitTree(K key, SplayNode<T, K> *&leftOutput,
                                SplayNode<T, K> *&rightOutput) {
    //SplayTree &outputT1, SplayTree &outputT2, K &key - last input of Guy
    root = findNode(key);
    if (!root) {
        leftOutput = NULL;
        rightOutput = NULL;
        return;
    }
    if (root->key > key) {
        rightOutput = root;
        leftOutput = root->l_child;
        rightOutput->l_child = NULL;
        if (leftOutput) {
            leftOutput->parent = NULL;
            rightOutput->sumNodes -= leftOutput->sumNodes;
            rightOutput->weightScore -= leftOutput->weightScore;
        }
    } else {
        leftOutput = root;
        rightOutput = root->r_child;
        leftOutput->r_child = NULL;
        if (rightOutput) {
            rightOutput->parent = NULL;
            leftOutput->sumNodes -= rightOutput->sumNodes;
            leftOutput->weightScore -= rightOutput->weightScore;
        }
    }
}

template<class T, class K>
void SplayRankTree<T, K>::deleteTree(SplayNode<T, K> *root_tree) {
    if (root_tree) {
        SplayNode<T, K> *left = root_tree->getL_child();
        SplayNode<T, K> *right = root_tree->getR_child();
        deleteTree(left);
        deleteTree(right);
        delete root_tree;
    }
};


//################################### PUBLIC FUNCTIONS ################################
//######################################################################################

template<class T, class K>
SplayRankTree<T, K>::~SplayRankTree() {
    deleteTree(root);
};

template<class T, class K>
void SplayRankTree<T, K>::deleteTree() {
    deleteTree(root);
    root = NULL;
    sum_nodes = 0;
};

template<class T, class K>
void SplayRankTree<T, K>::insertNode(T data, K key) {
    SplayNode<T, K> *left = NULL;
    SplayNode<T, K> *right = NULL;
    splitTree(key, left, right);
    if (left && left->key == key) {
        if (right){
            left->r_child = right;
            left->sumNodes += right->sumNodes;
            left->weightScore += right->weightScore;
            right->parent = left;
        }
        delete data; // memory leak :)
        throw ds_exceptions::NodeIsAlreadyExistException();
    }
    SplayNode<T, K> *new_node = new SplayNode<T, K>(data, key);
    new_node->l_child = left;
    new_node->r_child = right;
    new_node->parent = NULL;
    new_node->sumNodes = 1;
    new_node->weightScore = key;
    if (right) {
        right->parent = new_node;
        new_node->sumNodes += right->sumNodes;
        new_node->weightScore += right->weightScore;
    }
    if (left) {
        left->parent = new_node;
        new_node->sumNodes += left->sumNodes;
        new_node->weightScore += left->weightScore;
    }
    root = new_node;
    sum_nodes += 1;
    //createNode(data, key);
}

template<class T, class K>
void SplayRankTree<T, K>::deleteNode(K key) {
    SplayNode<T, K> *left = NULL;
    SplayNode<T, K> *right = NULL;
    splitTree(key, left, right); //left holds the root with the key
    if (left) {
        if (left->key == key) {
            SplayNode<T, K> *new_left = left->l_child;
            if (new_left) {
                new_left->parent = NULL;
            }
            delete left; // calls ~Node()
            sum_nodes -= 1;
            root = new_left;
            joinTrees(right);
            return;
        }
    }
    root = left;
    joinTrees(right);
}

template<class T, class K>
SplayNode<T, K> *SplayRankTree<T, K>::findNode(K key) {
    // empty tree
    if (root == NULL) {
        return root;
    }
    return findNode(root, key);

}

template<class T, class K>
SplayNode<T, K> *SplayRankTree<T, K>::findMin() {
    // empty tree
    if (root == NULL) {
        return NULL;
    }
    return (findMin(root));
}

template<class T, class K>
SplayNode<T, K> *SplayRankTree<T, K>::findMax() {
    // empty tree
    if (root == NULL) {
        return NULL;
    }
    return (findMax(root));
}

template<class T, class K>
T SplayRankTree<T, K>::getRootVal() {
    if (root) {
        return root->data;
    }
    return NULL;
}

template<class T, class K>
int SplayRankTree<T, K>::getSum_nodes() const {
    return sum_nodes;
};

template<class T,class K>
K SplayRankTree<T,K>::getSumScoreOfKBestNodes(int k) const{
    //need to find the node rank n-k+1
    return getSumScoreOfKBestNodes(root, sum_nodes-k+1, root->weightScore);
}

//private function
template<class T,class K>
K SplayRankTree<T,K>::getSumScoreOfKBestNodes(SplayNode<T, K>* node, int index, K
    r_score) const{
    if (!node){
        throw ds_exceptions::NotEnoughNodesException();
    }
    if (node->l_child){
        if (node->l_child->sumNodes == index-1){
            r_score = r_score - node->l_child->weightScore;
            return r_score;
        }
        else if (node->l_child->sumNodes > index - 1){
            return getSumScoreOfKBestNodes(node->l_child,index,r_score);
        }
        else{
            r_score = r_score - node->key - node->l_child->weightScore;
            index = index - node->l_child->sumNodes - 1;
            return getSumScoreOfKBestNodes(node->r_child,index,r_score);
        }
    }
    else{
        if (index == 1){
            return r_score;
        }
        else{
            index = index - 1;
            r_score = r_score - node->key;
            return getSumScoreOfKBestNodes(node->r_child,index,r_score);
        }
    }
};

template<class T, class K>
bool SplayRankTree<T, K>::isNodeInside(K key)  {
    // empty tree
    if (root == NULL) {
        return false;
    }
    SplayNode<T,K>* node = findNode(key);
    if (!node){
        return false;
    }
    else{
        return node->key == key;
    }
}

#endif //HW_WET2_SPLAYRANKTREE_H
