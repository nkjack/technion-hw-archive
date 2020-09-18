/*
 * ScaryRoom.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: Noam
 */

#include "ScaryRoom.h"

namespace mtm {
namespace escaperoom {

void ScaryRoom::setNewAgeLimit(const int& limit) {
	if (limit < 0) {
		throw ScaryRoomIllegalAgeLimit();
	}
	age_limit = limit;
}

void ScaryRoom::incNumberOfScaryEnigmas() {
	num_of_scary_enigmas++;
}

int ScaryRoom::getAgeLimit() const {
	return this->age_limit;
}

void ScaryRoom::print(std::ostream& output) const {
	output << "Scary Room: " << getName() << " (";
	output << getMaxTime() << "/" << level() << "/";
	output << getMaxParticipants() << "/";
	output << age_limit << ")";
}

int ScaryRoom::getNumOfScaryEnigmas() const {
	return this->num_of_scary_enigmas;
}

}  // namespace escaperoom
}  // namespace mtm

