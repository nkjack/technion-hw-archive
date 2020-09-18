//
// Created by noam on 12/31/17.
//

#ifndef HW_WET2_COLOSSEUM_H
#define HW_WET2_COLOSSEUM_H


#include "Objects.h"
#include "library2.h"
#include "HashTable.h"
#include "Heap.h"

/**
 * The Colosseum Class represent our main Data Structure that contains HashTable of
 * training groups, Minimum Heap of the training groups and SplayRankTree of all the
 * Gladiators in the Colosseum.
 */
class Colosseum {
    HashTable tgHashTable;
    Heap<int,int> tgMinHeap;
    SplayRankTree<Gladiator*, int> gldTrees; // sort by ID

public:
    Colosseum(int n, int* trainingGroupsIDs): tgHashTable(n),tgMinHeap(n,-1){
        HeapNode<int, int> **heapNodes = new HeapNode<int, int> *[n];
        int *dataArrayForHeap = new int[n];
        for(int i = 0; i < n; i++) dataArrayForHeap[i] = 0;
        tgMinHeap.makeHeap(heapNodes,dataArrayForHeap,trainingGroupsIDs);
        delete[] dataArrayForHeap;
        //arrray is array of pointers to the groups in the heap
        tgHashTable.addTrainingGroups(n,trainingGroupsIDs,heapNodes);
        delete[] heapNodes;
    }

    /**
     * Add training Group into the Colosseum. Adding it to the hash table of Training
     * Groups and to the minimum Heap.
     * @param trainingGroupID
     * @return StatusType - FAILURE - training group already in Colosseum,
     *                      INVALID INPUT - if id is not valid
     *                      SUCCESS - if inserted successfully
     */
    StatusType addTrainingGroup (int trainingGroupID){
        if (trainingGroupID < 0){
            return INVALID_INPUT;
        }
        if (tgHashTable.findTrainGroup(trainingGroupID)){
            return FAILURE;
        }
        HeapNode<int,int>* node = tgMinHeap.insert(0,trainingGroupID);
        tgHashTable.insertTrainGroup(trainingGroupID,node);
        return SUCCESS;
    }

    /**
     * Adding Gladiator into the Colosseum. The gladiator will be added into the big
     * gladiators tree of the Colosseum and into the gladiators tree of the Training
     * Group that he belongs to.
     * @param gladiatorID - id of gladiator
     * @param score - score of gladiator
     * @param trainingGroup - id of training group
     * @return Status Type - INVALID INPUT - if one of the input variables is not valid.
     *                       FAILURE - if gladiator is already in the system, or
     *                                  Training group is not in the system.
     *                       SUCCESS - if inserted successfully
     */
    StatusType addGladiator(int gladiatorID, int score, int trainingGroup){
        if (trainingGroup < 0 || gladiatorID < 0 || score < 0){
            return INVALID_INPUT;
        }
        HashNode* hashNodeTrainGroup = tgHashTable.findTrainGroup(trainingGroup);
        if(hashNodeTrainGroup ==NULL){
            return FAILURE;
        }

        if (gldTrees.isNodeInside(gladiatorID)){
            return FAILURE;
        }
        hashNodeTrainGroup->getTraingGroup()->insertGladiator(gladiatorID,score);
        gldTrees.insertNode(new Gladiator(gladiatorID,score),gladiatorID);
        return SUCCESS;
    }

    /**
     * Simulate the fight between two training groups. And update all of the components
     * in the data stracture accordingly.
     * @param trainingGroup1 - id of group 1
     * @param trainingGroup2 - id of group 2
     * @param k1 - amount of gladiator from group 1
     * @param k2 - amount of gladiator from group 2
     * @return Status Type - INVALUD INPUT - if one of the inputed variables not valid.
     *                       FAILURE - According to the HW Conditions
     *                       SUCCESS - if the battle happened without failures
     *                                  according to the hw conditions.
     */
    StatusType trainingGroupFight (int trainingGroup1, int trainingGroup2, int k1, int
    k2){
        if (k1<=0 || k2<=0 || trainingGroup1 < 0 || trainingGroup2 < 0){
            return INVALID_INPUT;
        }
        if (trainingGroup1 == trainingGroup2){
            return FAILURE;
        }
        HashNode* hashNodeTrainGroup1 = tgHashTable.findTrainGroup(trainingGroup1);
        HashNode* hashNodeTrainGroup2 = tgHashTable.findTrainGroup(trainingGroup2);
        if(hashNodeTrainGroup1 == NULL || hashNodeTrainGroup2 == NULL){
            return FAILURE;
        }
        if (hashNodeTrainGroup1->getTraingGroup()->getNumGladiators() < k1 ||
                hashNodeTrainGroup2->getTraingGroup()->getNumGladiators() < k2){
            return FAILURE;
        }

        try {
            // check who won and update the heap and the trainers flags
            int winGroupID = tgHashTable.trainingGroupsFight(trainingGroup1,
                                                             trainingGroup2,k1,k2);
            if (winGroupID == trainingGroup1){
                tgMinHeap.remove(hashNodeTrainGroup2->getPTrainGroupInHeap());
                hashNodeTrainGroup2->getTraingGroup()->turnOffGroup();
            }
            else {
                tgMinHeap.remove(hashNodeTrainGroup1->getPTrainGroupInHeap());
                hashNodeTrainGroup1->getTraingGroup()->turnOffGroup();
            }
        }
        catch (const ds_exceptions::InvalidInputException &e) {
            return INVALID_INPUT;
        }
        catch (const ds_exceptions::FailureException &e){
            return FAILURE;
        }
        return SUCCESS;
    }

    /**
     * Getting the minimum training group id from the heap of the colosseum.
     * @param trainingGroup - pointer of int to update.
     * @return StatusType - FAILURE if input is NULL, or minimum node doesnt exist.
     *                      SUCCESS otherwise
     */
    StatusType getMinTrainingGroup(int* trainingGroup){
        if (trainingGroup == NULL){
            return FAILURE;
        }
        HeapNode<int,int>* node = tgMinHeap.getMin();
        if (!node){
            return FAILURE;
        }
        *trainingGroup = node->getKey();
        return SUCCESS;
    }

    ~Colosseum(){}
};



#endif //HW_WET2_COLOSSEUM_H
