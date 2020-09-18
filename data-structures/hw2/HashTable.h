//
// Created by noam on 12/31/17.
//

#ifndef HW_WET2_HASHTABLE_H
#define HW_WET2_HASHTABLE_H

#include "Objects.h"
#include "HeapNode.h"

/**
 * The Hash Node is not a generic Node because the HashTable itself is not generic.
 * The HashNode is used in the linked list of each cubical in the Array of the HashTable
 * because the hash table is implemented as Chain Hash Table.
 * Each node contains a pointer to the next node, a pointer to TrainGroup that store
 * almost all the relevant information about the current node, and a pointer to the
 * Traing Group in an external Heap.
 *
 * HashNode* nextNode - the nextNode in the linked list
 * TrainGroup* trainGroup - the Train Group that the node store.
 * HeapNode<int,int>* pTrainGroupInHeap - the pointer to the group in the external Heap.
 */
class HashNode{
    HashNode* nextNode;
    TrainGroup* trainGroup;
    HeapNode<int,int>* pTrainGroupInHeap;
    friend class HashTable;
public:
    HashNode(HashNode *nextNode, TrainGroup *trainGroup,
             HeapNode<int,int>* pTrainGroupInHeap) :
                     nextNode(nextNode),
                     trainGroup(trainGroup),
                     pTrainGroupInHeap(pTrainGroupInHeap){}

    HashNode(HeapNode<int, int> *pTrainGroupInHeap) : pTrainGroupInHeap(pTrainGroupInHeap){};

    ~HashNode(){
        delete trainGroup;
    }

    TrainGroup* getTraingGroup(){
        return trainGroup;
    }

    HeapNode<int, int> *getPTrainGroupInHeap() const {
        return pTrainGroupInHeap;
    }
};

/**
 * This Hash Table is not Generic and implemented as Chain Hashing. The Hash Table is
 * implemented as an Array of HashNode pointers. In order to keep the complexity of the
 * Hash Table as mentioned in the Classroom, this hash table will double it space
 * whenever the amount of Nodes in the HashTable is more than double of the ArraySize.
 * That way we keep the alpha factor in O(1).
 *
 * This hash table assume there are no deleting single nodes, because there is no need
 * fo it in the Wet2 HW.
 */
class HashTable{
    HashNode** hashArray;
    int hashArraySize;
    int hashNumberOfNodes;

    int hashFunction(int id);

    void transferNode(HashNode* &pHashNode, HashNode** &newHashArray);
    void resizeHashTable();

    //NULL if not find
    HashNode* find(int trainingGroup);

public:
    HashTable(int n): hashArraySize(n), hashNumberOfNodes(0){
        hashArray = new HashNode*[n]();
    }
    HashTable(int n, int* trainingGroupIds, HeapNode<int,int>* trainGroupsPointers[]) :
            hashArraySize(n), hashNumberOfNodes(0) {
        hashArray = new HashNode*[n]();
        addTrainingGroups(n, trainingGroupIds, trainGroupsPointers);
    }

    /**
     * Function that get array of ids of training groups and array of pointers of each
     * training group to external Heap. This function will add each training group to
     * the hash table. This function is used when the hash table is intialize.
     * @param n - amount of training groups
     * @param trainingGroupIds - ids of training groups
     * @param trainGroupsPointers - pointers of training groups to the external Heap.
     */
    void addTrainingGroups(int n, int* trainingGroupIds, HeapNode<int,int>*
    trainGroupsPointers[]);

    /**
     * This function insert a new Train Group into the HashTable.
     * @param trainingGroup - id of training group
     * @param pTrainingGroupToHeap - pointer to the group in the exernal Heap.
     * @return True if inserted successfully, and false if the traing group is already
     * inside the hash table
     */
    bool insertTrainGroup(int trainingGroup,HeapNode<int,int>* pTrainingGroupToHeap);

    /**
     * Insert a gladiator into a TrainGroup. This Function first Fetch the
     * trainingGroup from the hashTable and than insert the gladiator into the tree of
     * gladiators of the founded training group.
     * @param trainingGroup - id of train Group
     * @param gladiatorID - id of gladiator to add
     * @param score - score of gladiator to add
     * @return
     */
    bool insertGladiatorGroup(int trainingGroup, int gladiatorID, int score);

    /**
     * Make a training Group inactive. This function first find the training Group and
     * than set the trainGroupActive boolean in the training group to false.
     * @param trainGroupId - id of training group
     */
    void turnOffTrainGroup(int trainGroupId);

    /**
     * This function make two training groups fight and turnOff the Training Group that
     * lost. First the method find Traing Group 1 and Traing Group 2. Than it checks
     * the score of each group according to the amount of gladiators that in the battle
     * finally it compare the scores and ouptut the wining training group id.
     * @param trainingGroup1 - id of training group 1
     * @param trainingGroup2 - id of treaining group 2
     * @param k1 - amount of gladiators from tg1
     * @param k2 - amount of gladiators from tg2
     * @return id of winning training group.
     * @throw FailureException if the condition of the HW is flase.
     */
    int trainingGroupsFight(int trainingGroup1, int trainingGroup2, int k1, int k2);

    /**
     * Search for a TraingGroup, and return the pointer of the HashNode of the founded
     * Traing Group in the HashTable.
     * @param trainingGroup - id of the Training Group.
     * @return HashNode*
     */
    HashNode* findTrainGroup(int trainingGroup);

    /**
     * deleting all the nodes in the array and than delete the array. This Destructor
     * takes O(size of the array of hash Table) because the maximum amout of nodes in
     * the array is double the size of the hash table array.
     */
    ~HashTable() {
        for (int i=0;i<hashArraySize;i++){
            HashNode* tempNode = hashArray[i];
            HashNode* tempDeleteNode = hashArray[i];
            while (tempNode){
                tempNode = tempNode->nextNode;
                delete tempDeleteNode;
                tempDeleteNode = tempNode;
            }
            hashArray[i] = NULL;
        }
        delete[] hashArray;
    }

};

//HashNode::HashNode


#endif //HW_WET2_HASHTABLE_H
