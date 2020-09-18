//
// Created by noam on 12/31/17.
//

#ifndef HW_WET2_OBJECTS_H
#define HW_WET2_OBJECTS_H

#include "SplayRankTree.h"

/**
 * The KeyGladiatorByScore class is a class that will use as a Key. The key will override
 * the > < >= <= operators ,first comparing by Score and than by id
 *
 * This class will benefit our data stracure when using SplayRankTree ordering by that
 * condition.
 */

class KeyGladiatorByScore {
    int id;
    int score;
public:
    explicit KeyGladiatorByScore(int score):id(0),score(score){};
    KeyGladiatorByScore(int id, int score) : id(id), score(score) {};

    KeyGladiatorByScore(const KeyGladiatorByScore& rhs){
        id = rhs.id;
        score = rhs.score;
    }

    //assignment operator generate by compiler

    ~KeyGladiatorByScore() {};

    int getId() const {
        return id;
    }

    int getScore() const {
        return score;
    }

    bool operator==(const KeyGladiatorByScore &rhs) const {
        return (score == rhs.score && id == rhs.id);
    }

    bool operator!=(const KeyGladiatorByScore &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const KeyGladiatorByScore &rhs) const {
        if (score < rhs.score)
            return true;
        else if (score == rhs.score){
            if (id < rhs.id) {
                return true;
            }
        }
        return false;
    }

    bool operator>(const KeyGladiatorByScore &rhs) const { return rhs < *this; }

    bool operator<=(const KeyGladiatorByScore &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const KeyGladiatorByScore &rhs) const {
        return !(*this < rhs);
    }

    KeyGladiatorByScore& operator+=(const KeyGladiatorByScore &rhs) {
        score = score + rhs.score;
        return *this;
    }

    KeyGladiatorByScore& operator-=(const KeyGladiatorByScore &rhs) {
        score = score - rhs.score;
        return *this;
    }

    KeyGladiatorByScore operator+(const KeyGladiatorByScore &rhs) const{
        KeyGladiatorByScore result(*this);
        return (result += rhs);
    }

    KeyGladiatorByScore operator-(const KeyGladiatorByScore &rhs) const{
        KeyGladiatorByScore result(*this);
        return (result -= rhs);
    }

    friend std::ostream &
    operator<<(std::ostream &output, const KeyGladiatorByScore &key) {
        output << key.score;
        return output;

    };
};


/**
 * The Gladiator class will hold id and score.
 * Colosseum data structure will use Gladiator pointer when storing gladiators into the
 * structure storage.
 *
 * Gladiator will override the > < >= <= == != operator the same as KeyGladiatorByScore
 */
class Gladiator {
    int id;
    int score;

//    friend class Colosseum;

public:
    Gladiator(int id, int score) : id(id), score(score) {};
    ~Gladiator() {};

    bool operator==(const Gladiator &rhs) const {
        return id == rhs.id;
    }

    bool operator!=(const Gladiator&rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const Gladiator &rhs) const {
        if (score < rhs.score)
            return true;
        if (rhs.score < score)
            return false;
        return id < rhs.id;
    }

    bool operator>(const Gladiator &rhs) const { return rhs < *this; }

    bool operator<=(const Gladiator &rhs) const { return !(rhs < *this);  }

    bool operator>=(const Gladiator &rhs) const {return !(*this < rhs); }

    void updateLevel(int stimulantCode, int stimulantFactor){
        if (id % stimulantCode == 0){
            score = score*stimulantFactor;
        }
    }
    friend std::ostream &
    operator<<(std::ostream &output, const Gladiator &gld) {
        output << gld.score;
        return output;

    };
};


/**
 * TrainGroup is the object that will be contain in the Big Hash Table. Each TrainGroup
 * will contains id, traingGroupActive flag, and a SplayRankTree of Gladiators that
 * belongs to that TrainGroup.
 */
class TrainGroup {
    SplayRankTree<Gladiator *, KeyGladiatorByScore> gld_tree_lvl;
    int id;
    bool trainGroupActive;
public:
    TrainGroup(int trainer_id) : id(trainer_id),trainGroupActive(true) {};

    ~TrainGroup() {
        gld_tree_lvl.deleteTree();
    };

    int getId() const {
        return id;
    }

    int getNumGladiators() const{
        return gld_tree_lvl.getSum_nodes();
    }

    void insertGladiator(int gladiatorID, int key_score){
        gld_tree_lvl.insertNode(new Gladiator(gladiatorID,key_score),
                                  KeyGladiatorByScore(gladiatorID,key_score));

    }

    void turnOffGroup(){
        trainGroupActive = false;
    }

    bool isActive() const{
        return trainGroupActive;
    }

    int getGroupScoreFight(int k) const{
        int sumNodes = gld_tree_lvl.getSum_nodes();
        if (k > 0 && k <= sumNodes){
//            gld_tree_lvl.select(sumNodes - k);
            return gld_tree_lvl.getSumScoreOfKBestNodes(k).getScore();
        }
        return -1;
    }

};



#endif //HW_WET2_OBJECTS_H
