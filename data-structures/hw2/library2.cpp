//
// Created by noam on 12/31/17.
//

#include"library2.h"
#include"Colosseum.h"

void* init(int n, int *trainingGroupsIDs){
    if( n < 2 || !trainingGroupsIDs){
        return NULL;
    }
    for (int i=0 ; i< n; i++){
        if (trainingGroupsIDs[i] < 0){
            return NULL;
        }
    }
    Colosseum* DS = new Colosseum(n, trainingGroupsIDs);
    return (void*)DS;
}

StatusType addTrainingGroup(void *DS, int trainingGroupID){
    if (!DS) {
        return INVALID_INPUT;
    }
    return ((Colosseum *) DS)->addTrainingGroup(trainingGroupID);
}

StatusType addGladiator(void *DS, int gladiatorID, int score, int trainingGroup){
    if (!DS) {
        return INVALID_INPUT;
    }
    return ((Colosseum *) DS)->addGladiator(gladiatorID,score,trainingGroup);

}

StatusType trainingGroupFight(void *DS, int trainingGroup1, int trainingGroup2, int k1,
                              int k2){
    if (!DS) {
        return INVALID_INPUT;
    }
    return ((Colosseum *) DS)->trainingGroupFight(trainingGroup1,trainingGroup2,k1,k2);

}

StatusType getMinTrainingGroup(void* DS, int* trainingGroup) {
    if (!DS || !trainingGroup) {
        return INVALID_INPUT;
    }
    return ((Colosseum *) DS)->getMinTrainingGroup(trainingGroup);
}

void quit(void** DS){
    if (DS) {
        delete ((Colosseum *) (*DS));
        *DS = NULL;
    }
}