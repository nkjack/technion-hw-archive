//
// Created by noam on 1/1/18.
//

#ifndef HW_WET2_HEAP_H_H
#define HW_WET2_HEAP_H_H

#include <cassert>
#include <iostream>
#include "HeapNode.h"



template<class T, class K>
class Heap{

    HeapNode<T, K> *root;
    int n;
    K min_key;

    /**
     * private method used to create an 'almost-full' binary tree.
     * method recursively runs over a list of nodes, creating left and right sons for them
     * until the desired size is reached.
     * @param nodes - a list of Node pointers, to read the current level from, and save new Nodes into.
     * @param nodes_left - int, holding the remaining num of Nodes still to be created.
     * @param level_count - int, the number of Nodes in the current level.
     * returns void, but Nodes are now saved in the array to use later.
     */
    void makeComplete(HeapNode<T, K> **nodes, int nodes_left, int level_count){
        int nodes_created = 0;
        for(int i = 0; nodes_left - nodes_created > 0 && i < level_count; i++){
            nodes[i] -> l_child = new HeapNode<T, K>();
            nodes[i] -> l_child -> parent = nodes[i];
            nodes[level_count + i * 2] = nodes[i] -> l_child;
            nodes_created++;
            if(nodes_left - nodes_created != 0){
                nodes[i] -> r_child = new HeapNode<T, K>();
                nodes[i] -> r_child -> parent = nodes[i];
                nodes[level_count + i * 2 + 1] = nodes[i] -> r_child;
                nodes_created++;
            }
        }
        if(nodes_left - nodes_created != 0){
            makeComplete(nodes + level_count, nodes_left - nodes_created, level_count * 2);
        }
    }

    /**
     * private method used to switch Nodes without harming the tree structure.
     * @param a - Node pointer to switch with b, ASSUMING A IS THE PARENT OF B!!!!!!!!!
     * @param b - same
     */
    void swapNodes(HeapNode<T, K> *a, HeapNode<T, K> *b){
        HeapNode<T, K> *a_l = a -> l_child;
        HeapNode<T, K> *a_r = a -> r_child;
        HeapNode<T, K> *a_p = a -> parent;
        HeapNode<T, K> *b_l = b -> l_child;
        HeapNode<T, K> *b_r = b -> r_child;
        assert(b -> parent == a);
        b -> parent = a_p;
        if(a -> isLeftChild()) a_p -> l_child = b;
        else if(a_p) a_p -> r_child = b;
        if(a_l == b){
            b -> l_child = a;
            b -> r_child = a_r;
            if(a_r) a_r -> parent = b;
        }
        else {
            b -> r_child = a;
            b -> l_child = a_l;
            if(a_l) a_l -> parent = b;
        }
        a -> parent = b;
        a -> l_child = b_l;
        if(b_l) b_l -> parent = a;
        a -> r_child = b_r;
        if(b_r) b_r -> parent = a;
        if(root == a) root = b;
    }

    /**
     * a heap tree method used to preserve it's nodes top-to-bottom order
     * @param sifting - Node pointer to sift down, if necessary.
     */
    void siftDown(HeapNode<T, K> * sifting){
        if((sifting -> l_child && sifting -> key > sifting -> l_child -> key) ||
           (sifting -> r_child && sifting -> key > sifting -> r_child -> key)){
            if(sifting -> l_child && sifting -> key > sifting -> l_child -> key &&
               sifting -> r_child && sifting -> key > sifting -> r_child -> key)
                if(sifting -> l_child -> key < sifting -> r_child -> key){
                    swapNodes(sifting, sifting -> l_child);
                }
                else{
                    swapNodes(sifting, sifting -> r_child);
                }
            else if(sifting -> l_child && sifting -> key > sifting -> l_child -> key){
                swapNodes(sifting, sifting -> l_child);
            }
            else{
                swapNodes(sifting, sifting -> r_child);
            }
            siftDown(sifting);
        }
    }

    /**
     * a heap tree method used to preserve it's nodes top-to-bottom order
     * @param sifting - Node pointer to sift down, if necessary.
     */
    void siftUp(HeapNode<T, K> * sifting){
        if(sifting -> parent && (sifting -> key < sifting -> parent -> key)){
            swapNodes(sifting -> parent, sifting);
            siftUp(sifting);
        }
    }

    /**
     * method converts a given number to binary, and inserts it into an array.
     * relying on the fact that a Node position in a full binary tree matches it's binary representation,
     * this will guide us to a desired leaf without a pointer.
     * @param place - int to be converted.
     * returns an array of "directions" - 0 being left and 1 being right
     */
    int *makeRoute(int place){
        int len = 0;
        for(int i = place; i > 0; i /= 2, len++);
        int *route = new int[len];   ////// needs to be deleted!
        int num = place;
        for(int i = 0; i < len; i++){
            route[len - 1 -i] = num % 2;
            num /= 2;
        }
        return route;
    }

    /**
     * method uses a created route representation created with makeRoute to find the leaf.
     * @param current - HeapNode<T, K> * to deepen from
     * @param route - int* to read the directions from
     * returns a pointer to the leaf
     */
    HeapNode<T, K> *find(HeapNode<T, K> *current, int* route){
        if(current -> l_child && route) {
            if (*route == 0) return find(current -> l_child, route + 1);
            else return current -> r_child ? find(current -> r_child, route + 1) : current;
        }
        else return current;
    };

public:

    Heap(int size, K min_key): root(new HeapNode<T, K>()), n(size), min_key(min_key){};

    void makeHeap(HeapNode<T, K> **nodes, T *data_list, K *Key_list){
        assert(n > 0);
        nodes[0] = root;
        makeComplete(nodes, n - 1, 1);
        for (int i = 0; i < n; i++){
            nodes[i] -> key = Key_list[i];
            nodes[i] -> data = data_list[i];
        }
        for(int i = n; i > 0; i--){
            siftDown(nodes[i - 1]);
        }
    }

    ~Heap(){
        while(n != 0){
            remove(root);
        }
    }

    HeapNode<T, K> *getMin() { return n > 0 ? root : NULL;}

    HeapNode<T, K> *insert(T data, K key){
        if(!root){
            root = new HeapNode<T, K>(data, key, NULL);
            n++;
            return root;
        }
        n++;
        int *route = makeRoute(n);
        HeapNode<T, K> *parent = find(root, route + 1);
        delete[] route;
        HeapNode<T, K> *leaf = new HeapNode<T, K>(data, key, parent);
        if(parent -> l_child) parent -> r_child = leaf;
        else parent -> l_child = leaf;
        siftUp(leaf);
        return leaf;
    };

    void remove(HeapNode<T, K> *to_remove){
        to_remove -> key = min_key;
        siftUp(to_remove);
        assert(root == to_remove);
        int *route = makeRoute(n);
        HeapNode<T, K> *leaf = find(root, route + 1);
        delete[] route;
        if(to_remove -> l_child) to_remove -> l_child -> parent = leaf;
        if(to_remove -> r_child) to_remove -> r_child -> parent = leaf;
        leaf -> l_child = to_remove -> l_child;
        leaf -> r_child = to_remove -> r_child;
        if(leaf -> isLeftChild()) leaf -> parent -> l_child = NULL;
        else if(leaf -> parent) leaf -> parent -> r_child = NULL;
        leaf -> parent = NULL;
        root = leaf;
        siftDown(leaf);
        delete to_remove;
        n--;
        if(n == 0) root = NULL;
    }

};

#endif //HW_WET2_HEAP_H_H
