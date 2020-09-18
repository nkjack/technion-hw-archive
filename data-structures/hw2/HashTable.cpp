//
// Created by noam on 12/31/17.
//

#include "HashTable.h"

/********************************* PRIVATE  FUNCTIONS ******************/
/**####################################################################*/
int HashTable::hashFunction(int id){
    return id % hashArraySize;
}

void HashTable::transferNode(HashNode* &pHashNode, HashNode** &newHashArray){
    int new_index = hashFunction(pHashNode->trainGroup->getId());

    if (newHashArray[new_index] == NULL){
        pHashNode->nextNode = NULL;
        newHashArray[new_index] = pHashNode;
    }
    else {
        HashNode *tempHashNode = newHashArray[new_index];
        newHashArray[new_index] = pHashNode;
        pHashNode->nextNode = tempHashNode;
    }
}
void HashTable::resizeHashTable(){
    int oldArraySize = hashArraySize;
    hashArraySize = hashArraySize*2;
    HashNode** newHashArray = new HashNode*[hashArraySize]();
    for (int i=0;i<oldArraySize;i++){
        HashNode* tempNode = hashArray[i];
        while(tempNode){
            HashNode* nodeTransfer = tempNode;
            tempNode = nodeTransfer->nextNode;
            transferNode(nodeTransfer, newHashArray);
        }
        hashArray[i] = NULL;
    }
    delete [] hashArray;
    hashArray = newHashArray;
}

//NULL if not find
HashNode* HashTable::find(int trainingGroup){
    int index = hashFunction(trainingGroup);
    HashNode* hashNodeTemp = hashArray[index];
    while (hashNodeTemp){
        if (hashNodeTemp->trainGroup->getId() == trainingGroup){
            break;
        }
        hashNodeTemp = hashNodeTemp->nextNode;
    }
    return hashNodeTemp;
}

/********************************* PUBLIC  FUNCTIONS ******************/
/**####################################################################*/

void HashTable::addTrainingGroups(int n, int* trainingGroupIds,  HeapNode<int,int>*
trainGroupsPointers[]){
    for (int i=0;i<n;i++) {
//        insertTrainGroup(trainingGroupIds[i], trainGroupsPointers[i]);
        hashNumberOfNodes += 1;
        int index = hashFunction(trainingGroupIds[i]);
        HashNode* hashNodeToInsert = new HashNode(NULL,new TrainGroup
                (trainingGroupIds[i]),trainGroupsPointers[i]);
        if (hashArray[index] == NULL){
            hashArray[index] = hashNodeToInsert;
        }
        else{
            HashNode* tempHashNode = hashArray[index];
            hashNodeToInsert->nextNode = tempHashNode;
            hashArray[index] = hashNodeToInsert;
        }
    }
}

HashNode* HashTable::findTrainGroup(int trainingGroup){
    return find(trainingGroup);
}
//assuming there is no identical TrainGroup in the hashtable
bool HashTable::insertTrainGroup(int trainingGroup,HeapNode<int,int>* pTrainingGroupToHeap){
    if (find(trainingGroup)){
        return false;
    }
    if (2*hashArraySize <= hashNumberOfNodes){
        resizeHashTable();
    }
    hashNumberOfNodes += 1;
    int index = hashFunction(trainingGroup);
    HashNode* hashNodeToInsert = new HashNode(NULL,new TrainGroup
            (trainingGroup),pTrainingGroupToHeap);
    if (hashArray[index] == NULL){
        hashArray[index] = hashNodeToInsert;
    }
    else{
        HashNode* tempHashNode = hashArray[index];
        hashArray[index] = hashNodeToInsert;
        hashNodeToInsert->nextNode = tempHashNode;
    }
    return true;
}

bool HashTable::insertGladiatorGroup(int trainingGroup, int gladiatorID, int score ){
    HashNode* findedNode = find(trainingGroup);
    if (findedNode == NULL){
        return false;
    }
    findedNode->trainGroup->insertGladiator(gladiatorID,score);
    return true;
}

void HashTable::turnOffTrainGroup(int trainGroupId){
    HashNode* node = find(trainGroupId);
    if (node){
        node->trainGroup->turnOffGroup();
    }
}

int HashTable::trainingGroupsFight(int trainingGroup1, int trainingGroup2, int k1, int k2){
    if (trainingGroup1 < 0 || trainingGroup2 < 0 || k1 <=0 || k2<=0){
        throw ds_exceptions::InvalidInputException();
    }
    HashNode* nodeGroup1 = find(trainingGroup1);
    HashNode* nodeGroup2 = find(trainingGroup2);
    if (nodeGroup1 == NULL || nodeGroup2 == NULL){
        throw ds_exceptions::FailureException();
    }
    if (nodeGroup1->trainGroup->getNumGladiators() < k1 ||
        nodeGroup2->trainGroup->getNumGladiators() < k2){
        throw ds_exceptions::FailureException();
    }
    if (!nodeGroup1->trainGroup->isActive() || !nodeGroup2->trainGroup->isActive()){
        throw ds_exceptions::FailureException();
    }
    int score1 = nodeGroup1->trainGroup->getGroupScoreFight(k1);
    int score2 = nodeGroup2->trainGroup->getGroupScoreFight(k2);
    int groupID1 = nodeGroup1->trainGroup->getId();
    int groupID2 = nodeGroup2->trainGroup->getId();
    if (score1 == score2){
        return groupID1 < groupID2 ? groupID1 : groupID2;
    }
    else if (score1 > score2){
        return groupID1;
    }
    else{
        return groupID2;
    }

};

