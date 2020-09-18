//
// Created by noam on 12/31/17.
//

#ifndef HW_WET2_RANK_TREE_TEST_CPP
#define HW_WET2_RANK_TREE_TEST_CPP

#include "dstest.h"
#include "../SplayRankTree.h"
#include "../Objects.h"
using namespace std;

void generalFunctions() {
    SplayRankTree<Gladiator*,KeyGladiatorByScore> st;
    st.insertNode(new Gladiator(1,1),KeyGladiatorByScore(1,1));
    ASSERT_EQUALS(*st.getRootVal() ,Gladiator(1,1));
    for(int i=2; i<16; i++){
        st.insertNode(new Gladiator(i,i),KeyGladiatorByScore(i,i));
    }
//    cout << st.getSum_nodes() <<endl;
    ASSERT_EQUALS(st.getSum_nodes(),15);
    //cout << st << endl;

    ASSERT_PRINT("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 ", st);
    KeyGladiatorByScore key(5,5);
    SplayNode<Gladiator*,KeyGladiatorByScore>* c_node;
    c_node = st.findNode(key);
    ASSERT_EQUALS(key, c_node->getKey());
    ASSERT_PRINT("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 ", st);
    key = KeyGladiatorByScore(10,10);
    c_node = st.findNode(key);
    ASSERT_EQUALS(key, c_node->getKey());
    c_node = st.findMax();
    ASSERT_EQUALS(KeyGladiatorByScore(15,15), c_node->getKey());
    c_node = st.findMin();
    ASSERT_EQUALS(KeyGladiatorByScore(1,1), c_node->getKey());
    st.deleteNode(KeyGladiatorByScore(7,7));
    ASSERT_PRINT("1 2 3 4 5 6 8 9 10 11 12 13 14 15 ", st);
    st.deleteNode(KeyGladiatorByScore(3,3));
    ASSERT_PRINT("1 2 4 5 6 8 9 10 11 12 13 14 15 ", st);
    st.deleteNode(KeyGladiatorByScore(10,10));
    ASSERT_PRINT("1 2 4 5 6 8 9 11 12 13 14 15 ", st);

}


void testLeftZig() {
    //insertion
    SplayRankTree<int*,int> st1;
    st1.insertNode(new int(1),3);
    st1.insertNode(new int(1),2);
    SplayNode<int*,int>* root = st1.getRoot();
    ASSERT_EQUALS(root->getKey(), 2);
    ASSERT_TRUE(root->getL_child() == NULL);
    ASSERT_TRUE(root->getParent() == NULL);
    SplayNode<int*, int>* right_son = root->getR_child() ;
    ASSERT_TRUE(right_son != NULL);
    ASSERT_EQUALS(3, right_son->getKey());
    ASSERT_TRUE(right_son->getR_child() == NULL);
    ASSERT_TRUE(right_son->getL_child() == NULL);
    ASSERT_TRUE(right_son->getParent()->getKey() == root->getKey());
    //find
    SplayRankTree<int*,int> st2;
    st2.insertNode(new int(1),4);
    st2.insertNode(new int(1),5);
    SplayNode<int*,int>* finded_node = st2.findNode(4);
    ASSERT_EQUALS(finded_node ->getKey(), 4);
    ASSERT_TRUE(finded_node ->getL_child() == NULL);
    ASSERT_TRUE(finded_node ->getParent() == NULL);
    SplayNode<int*, int>* right_son_f = finded_node->getR_child() ;
    ASSERT_TRUE(right_son_f != NULL);
    ASSERT_EQUALS(5, right_son_f->getKey());
    ASSERT_TRUE(right_son_f->getR_child() == NULL);
    ASSERT_TRUE(right_son_f->getL_child() == NULL);
    ASSERT_TRUE(right_son_f->getParent()->getKey() == finded_node->getKey());
    //delete
    st2.findNode(5);
    st2.deleteNode(4);
    finded_node = st2.getRoot();
    ASSERT_TRUE(finded_node != NULL);
    ASSERT_TRUE(finded_node->getParent() == NULL);
    ASSERT_TRUE(finded_node->getL_child() == NULL);
    ASSERT_TRUE(finded_node->getR_child() == NULL);
    ASSERT_EQUALS(finded_node->getKey(),  5);
}

void testLeftZag() {
    //insertion
    SplayRankTree<int*,int> st1;
    st1.insertNode(new int(1),2);
    st1.insertNode(new int(1),3);
    SplayNode<int*,int>* root = st1.getRoot();
    ASSERT_EQUALS(root->getKey(), 3);
    ASSERT_TRUE(root->getR_child() == NULL);
    ASSERT_TRUE(root->getParent() == NULL);
    SplayNode<int*, int>* left_son = root->getL_child() ;
    ASSERT_TRUE(left_son != NULL);
    ASSERT_EQUALS(2, left_son->getKey());
    ASSERT_TRUE(left_son->getR_child() == NULL);
    ASSERT_TRUE(left_son->getL_child() == NULL);
    ASSERT_TRUE(left_son->getParent()->getKey() == root->getKey());
    //find
    SplayRankTree<int*,int> st2;
    st2.insertNode(new int(1),5);
    st2.insertNode(new int(1),4);
    SplayNode<int*,int>* finded_node = st2.findNode(5);
    ASSERT_EQUALS(finded_node ->getKey(), 5);
    ASSERT_TRUE(finded_node ->getR_child() == NULL);
    ASSERT_TRUE(finded_node ->getParent() == NULL);
    SplayNode<int*, int>* left_son_f = finded_node->getL_child() ;
    ASSERT_TRUE(left_son_f != NULL);
    ASSERT_EQUALS(4, left_son_f->getKey());
    ASSERT_TRUE(left_son_f->getR_child() == NULL);
    ASSERT_TRUE(left_son_f->getL_child() == NULL);
    ASSERT_TRUE(left_son_f->getParent()->getKey() == finded_node->getKey());
    //delete
    st2.findNode(4);
    st2.deleteNode(5);
    finded_node = st2.getRoot();
    ASSERT_TRUE(finded_node != NULL);
    ASSERT_TRUE(finded_node->getParent() == NULL);
    ASSERT_TRUE(finded_node->getL_child() == NULL);
    ASSERT_TRUE(finded_node->getR_child() == NULL);
    ASSERT_EQUALS(finded_node->getKey(),  4);
}

void leftZigZig(){
    SplayRankTree<int*,int> st1;
    st1.insertNode(new int(1),1);
    st1.insertNode(new int(1),2);
    st1.insertNode(new int(1),3);
    st1.findNode(1);

    SplayNode<int*,int>* root_st1 = st1.getRoot();
    SplayNode<int*,int>* st1_son = root_st1->getR_child();
    SplayNode<int*,int>* st1_gs = st1_son->getR_child();

    ASSERT_TRUE(root_st1);
    ASSERT_TRUE(st1_son);
    ASSERT_TRUE(st1_gs);
    ASSERT_TRUE(root_st1->getL_child() == NULL);
    ASSERT_TRUE(root_st1->getParent() == NULL);
    ASSERT_TRUE(st1_son->getL_child() == NULL);
    ASSERT_TRUE(st1_son->getParent() == root_st1);
    ASSERT_TRUE(st1_gs->getL_child() == NULL);
    ASSERT_TRUE(st1_gs->getR_child() == NULL);
    ASSERT_TRUE(st1_gs->getParent() == st1_son);
    ASSERT_EQUALS(1, root_st1->getKey());
    ASSERT_EQUALS(2, st1_son->getKey());
    ASSERT_EQUALS(3, st1_gs->getKey());
    //delete in zigzig
    st1.findNode(3);
    st1.deleteNode(1);
    root_st1 = st1.getRoot();
    st1_son = root_st1->getR_child();
    ASSERT_TRUE(root_st1);
    ASSERT_TRUE(st1_son);
    ASSERT_TRUE(root_st1->getParent() == NULL);
    ASSERT_TRUE(root_st1->getL_child() == NULL);
    ASSERT_TRUE(st1_son->getL_child() == NULL);
    ASSERT_TRUE(st1_son->getR_child() == NULL);
    ASSERT_TRUE(st1_son->getParent() == root_st1);
    ASSERT_EQUALS(root_st1->getKey(), 2);
    ASSERT_EQUALS(st1_son->getKey(), 3);
}

void rightZigZig(){
    SplayRankTree<int*,int> st1;
    st1.insertNode(new int(1),3);
    st1.insertNode(new int(1),2);
    st1.insertNode(new int(1),1);
    st1.findNode(3);

    SplayNode<int*,int>* root_st1 = st1.getRoot();
    SplayNode<int*,int>* st1_son = root_st1->getL_child();
    SplayNode<int*,int>* st1_gs = st1_son->getL_child();

    ASSERT_TRUE(root_st1);
    ASSERT_TRUE(st1_son);
    ASSERT_TRUE(st1_gs);
    ASSERT_TRUE(root_st1->getR_child() == NULL);
    ASSERT_TRUE(root_st1->getParent() == NULL);
    ASSERT_TRUE(st1_son->getR_child() == NULL);
    ASSERT_TRUE(st1_son->getParent() == root_st1);
    ASSERT_TRUE(st1_gs->getL_child() == NULL);
    ASSERT_TRUE(st1_gs->getR_child() == NULL);
    ASSERT_TRUE(st1_gs->getParent() == st1_son);
    ASSERT_EQUALS(3, root_st1->getKey());
    ASSERT_EQUALS(2, st1_son->getKey());
    ASSERT_EQUALS(1, st1_gs->getKey());
    //delete in zigzig
    st1.findNode(3);
    st1.deleteNode(1);
    root_st1 = st1.getRoot();
    st1_son = root_st1->getR_child();
    ASSERT_TRUE(root_st1);
    ASSERT_TRUE(st1_son);
    ASSERT_TRUE(root_st1->getParent() == NULL);
    ASSERT_TRUE(root_st1->getL_child() == NULL);
    ASSERT_TRUE(st1_son->getL_child() == NULL);
    ASSERT_TRUE(st1_son->getR_child() == NULL);
    ASSERT_TRUE(st1_son->getParent() == root_st1);
    ASSERT_EQUALS(root_st1->getKey(), 2);
    ASSERT_EQUALS(st1_son->getKey(), 3);
}

//NOT finish YETp
void testRightZigZag(){
    SplayRankTree<int*,int> st1;
    st1.insertNode(new int(1),1);
    st1.insertNode(new int(1),3);
    st1.insertNode(new int(1),5);
    st1.insertNode(new int(1),2);

    SplayNode<int*,int>* root_st1 = st1.getRoot();
    SplayNode<int*,int>* l1_son = root_st1->getL_child();
    SplayNode<int*,int>* r1_son = root_st1->getR_child();
    SplayNode<int*,int>* gs = r1_son->getR_child();

    ASSERT_EQUALS(root_st1->getKey(),2);
    ASSERT_EQUALS(l1_son->getKey(),1);
    ASSERT_EQUALS(r1_son->getKey(),3);
    ASSERT_EQUALS(gs->getKey(),5);
    ASSERT_TRUE(root_st1->getParent() == NULL);
    ASSERT_TRUE(r1_son->getParent() == root_st1);
    ASSERT_TRUE(r1_son->getL_child() == NULL);
    ASSERT_TRUE(l1_son->getParent() == root_st1);
    ASSERT_TRUE(l1_son->getL_child() == NULL);
    ASSERT_TRUE(l1_son->getR_child() == NULL);
    ASSERT_TRUE(gs->getParent() == r1_son);
    ASSERT_TRUE(gs->getR_child() == NULL);
    ASSERT_TRUE(gs->getL_child() == NULL);
}


void sumScoreOfBestNodesChecker() {
    SplayRankTree<Gladiator*,KeyGladiatorByScore> st;
    st.insertNode(new Gladiator(1,1),KeyGladiatorByScore(1,1));
    ASSERT_EQUALS(*st.getRootVal() ,Gladiator(1,1));
    for(int i=2; i<21; i++){
        st.insertNode(new Gladiator(i,1),KeyGladiatorByScore(i,1));
    }
//    cout << st.getSum_nodes() <<endl;
    ASSERT_EQUALS(st.getSum_nodes(),20);
    //cout << st << endl;

    ASSERT_PRINT("1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 ", st);
//    cout << st.getSumScoreOfKBestNodes(5) << endl;
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(5).getScore(),5);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(6).getScore(),6);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(7).getScore(),7);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(8).getScore(),8);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(9).getScore(),9);

    st.deleteTree();
    st.insertNode(new Gladiator(1,1),KeyGladiatorByScore(1,1));
    ASSERT_EQUALS(*st.getRootVal() ,Gladiator(1,1));
    for(int i=2; i<21; i++){
        st.insertNode(new Gladiator(i,i),KeyGladiatorByScore(i,i));
    }
    ASSERT_PRINT("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 ", st);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(1).getScore(),20);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(2).getScore(),39);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(3).getScore(),57);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(4).getScore(),74);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(5).getScore(),90);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(6).getScore(),105);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(7).getScore(),119);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(8).getScore(),132);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(9).getScore(),144);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(10).getScore(),155);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(11).getScore(),165);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(12).getScore(),174);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(13).getScore(),182);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(14).getScore(),189);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(15).getScore(),195);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(16).getScore(),200);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(17).getScore(),204);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(18).getScore(),207);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(19).getScore(),209);
    ASSERT_EQUALS(st.getSumScoreOfKBestNodes(20).getScore(),210);
    ASSERT_THROWS(ds_exceptions::NotEnoughNodesException, st.getSumScoreOfKBestNodes(21));
    ASSERT_THROWS(ds_exceptions::NotEnoughNodesException, st.getSumScoreOfKBestNodes(36));
}

int splay_tests() {
    RUN_TEST(generalFunctions);
    RUN_TEST(testLeftZig);
    RUN_TEST(testLeftZag);
    RUN_TEST(leftZigZig);
    RUN_TEST(rightZigZig);
    RUN_TEST(testRightZigZag);
    RUN_TEST(sumScoreOfBestNodesChecker);
    return 0;

}
#endif //HW_WET2_RANK_TREE_CPP
