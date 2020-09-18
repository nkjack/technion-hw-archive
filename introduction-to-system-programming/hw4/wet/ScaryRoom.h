/*
 * ScaryRoom.h
 *
 *  Created on: Jun 26, 2017
 *      Author: Noam
 */

#ifndef SCARYROOM_H_
#define SCARYROOM_H_

#include "EscapeRoomWrapper.h"
#include "Exceptions.h"

namespace mtm {
namespace escaperoom {

class ScaryRoom: public EscapeRoomWrapper {
	int age_limit;
	int num_of_scary_enigmas;

public:
	/**
	 * ScaryRoom constructor. This is a simple constructor that intializes
	 * each variable of the class with the inputed data.
	 *
	 * @param name - the name of the room
	 * @param esacpeTime - the max time of the escape Room
	 * @param level - the level of the room
	 * @param maxParticipants - max people that allowed in this room
	 * @param ageLimit - the age limit of this room
	 * @param numOfScaryEnigmas - amount of enigmas inside the room
	 */
	ScaryRoom(char* name, const int& escapeTime, const int& level,
			const int& maxParticipants, const int& ageLimit,
			const int& numOfScaryEnigmas) :
			EscapeRoomWrapper(name, escapeTime, level, maxParticipants), age_limit(
					ageLimit), num_of_scary_enigmas(numOfScaryEnigmas) {
	}

	/**
	 * set a new age limit of this room.
	 *
	 * @param limit - the new age limit to set
	 * @throws - ScaryRoomIllegalAgeLimit - if the input limit is below 0
	 */
	void setNewAgeLimit(const int& limit);
	/**
	 * increment the amount of scary enigmas of this room by 1
	 */
	void incNumberOfScaryEnigmas();
	/**
	 * @return int - the age limit of this room
	 */
	int getAgeLimit() const;
	/**
	 * @return int - the num of scary enigmas in this room
	 */
	int getNumOfScaryEnigmas() const;

protected:
	/*
	 * This is the function which the base function (<<) calls. This method
	 * insert to the ostream the ScaryRoom description
	 *
	 * @param ouptut - the std::ostream& which this function update
	 */
	virtual void print(std::ostream& output) const;

};

}  // namespace escaperoom
}  // namespace mtm

#endif /* SCARYROOM_H_ */
