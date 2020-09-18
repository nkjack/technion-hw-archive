/*
 * KidsRoom.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: Noam
 */

#include "KidsRoom.h"

namespace mtm {
namespace escaperoom {

void KidsRoom::setNewAgeLimit(const int& limit) {
	if (limit < 0) {
		throw KidsRoomIllegalAgeLimit();
	}
	age_limit = limit;
}
int KidsRoom::getAgeLimit() const{
	return age_limit;
}

void KidsRoom::print(std::ostream& output) const {
	output << "Kids Room: " << getName() << " (";
	output << getMaxTime() << "/" << level() << "/";
	output << getMaxParticipants() << "/";
	output << age_limit << ")";
}

}  // namespace escaperoom
}  // namespace mtm

