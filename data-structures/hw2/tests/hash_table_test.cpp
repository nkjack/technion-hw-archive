//
// Created by noam on 12/31/17.
//
#ifndef HW_WET2_HASH_TABLE_TEST_CPP
#define HW_WET2_HASH_TABLE_TEST_CPP

#include "dstest.h"
#include "../HashTable.h"
#include "../HeapNode.h"
using namespace std;

void generalHashFunctions() {
    int trainers[20];
    for (int i=0; i < 20; i++){
        trainers[i] = i;
    }
    HeapNode<int,int>** trainGroupArray = new HeapNode<int,int>*[20];
    HashTable hashTable(20,trainers,trainGroupArray);

    ASSERT_TRUE(hashTable.findTrainGroup(6));
    ASSERT_TRUE(hashTable.findTrainGroup(19));

    hashTable.insertTrainGroup(57,NULL);
    ASSERT_TRUE(hashTable.findTrainGroup(57));

    for (int i=100; i < 300; i++){
        hashTable.insertTrainGroup(i,NULL);
    }
    ASSERT_TRUE(hashTable.findTrainGroup(234));
    hashTable.insertGladiatorGroup(234,1,1);
    hashTable.insertGladiatorGroup(234,2,2);
    hashTable.insertGladiatorGroup(234,3,3);
    hashTable.insertGladiatorGroup(234,4,4);
    hashTable.insertGladiatorGroup(234,5,5);
    HashNode* hNode = hashTable.findTrainGroup(234);
    ASSERT_EQUALS(hNode->getTraingGroup()->getNumGladiators(),5);
    ASSERT_EQUALS(hNode->getTraingGroup()->getGroupScoreFight(5),15);
    ASSERT_EQUALS(hNode->getTraingGroup()->getGroupScoreFight(2),9);

    hashTable.insertGladiatorGroup(143,1,10);
    hashTable.insertGladiatorGroup(143,2,22);
    hashTable.insertGladiatorGroup(143,3,33);
    hashTable.insertGladiatorGroup(143,4,4);
    hashTable.insertGladiatorGroup(143,5,5);
    hNode = hashTable.findTrainGroup(143);
    ASSERT_EQUALS(hNode->getTraingGroup()->getNumGladiators(),5);
    ASSERT_EQUALS(hNode->getTraingGroup()->getGroupScoreFight(5),74);
    ASSERT_EQUALS(hNode->getTraingGroup()->getGroupScoreFight(2),55);

    ASSERT_EQUALS(hashTable.trainingGroupsFight(143,234,2,5),143);
    hashTable.insertGladiatorGroup(100,999,33);
    ASSERT_EQUALS(hashTable.trainingGroupsFight(143,100,1,1),100);
    hashTable.turnOffTrainGroup(100);
    ASSERT_TRUE(!hashTable.trainingGroupsFight(143,100,1,1));
    delete [] trainGroupArray;
}

int hash_tests() {
    RUN_TEST(generalHashFunctions);
    return 0;
}

#endif