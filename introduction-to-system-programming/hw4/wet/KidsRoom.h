/*
 * KidsRoom.h
 *
 *  Created on: Jun 26, 2017
 *      Author: Noam
 */

#ifndef KIDSROOM_H_
#define KIDSROOM_H_

#include "Exceptions.h"
#include "EscapeRoomWrapper.h"

namespace mtm {
namespace escaperoom {

class KidsRoom: public EscapeRoomWrapper {
	int age_limit;

public:
	/**
	 * KidsRoom constructor. This is a simple constructor that intializes
	 * each variable of the class with the inputed data.
	 *
	 * @param name - the name of the room
	 * @param esacpeTime - the max time of the escape Room
	 * @param level - the level of the room
	 * @param maxParticipants - max people that allowed in this room
	 * @param ageLimit - the age limit of this room
	 */
	KidsRoom(char* name, const int& escapeTime, const int& level,
			const int& maxParticipants, const int& ageLimit) :
			EscapeRoomWrapper(name, escapeTime, level, maxParticipants), age_limit(
					ageLimit) {
	}
	/**
	 * set a new age limit of this room.
	 *
	 * @param limit - the new age limit to set
	 * @throws - ScaryRoomIllegalAgeLimit - if the input limit is below 0
	 */
	void setNewAgeLimit(const int& limit);
	/**
	 * @return int - the age limit of this room
	 */
	int getAgeLimit() const;

protected:
	/*
	 * This is the function which the base function (<<) calls. This method
	 * insert to the ostream the KidsRoom description
	 *
	 * @param ouptut - the std::ostream& which this function update
	 */
	virtual void print(std::ostream& output) const;
};

}  // namespace escaperoom

}  // namespace mtm

#endif /* KIDSROOM_H_ */
