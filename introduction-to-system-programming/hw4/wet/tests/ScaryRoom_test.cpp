/*
 * ScaryRoom_test.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: Noam
 */

#include "../ScaryRoom.h"
#include "../mtmtest.h"

using namespace mtm::escaperoom;
using std::vector;

void scaryRoomCtor() {
	ASSERT_NO_THROW(ScaryRoom((char* )"ChanceTheWrapper", 60, 3, 6, 21, 100));
	ScaryRoom room((char*) "ChanceTheWrapper", 60, 3, 6, 21, 100);
	ASSERT_EQUALS("ChanceTheWrapper", room.getName());
	ASSERT_EQUALS(60, room.getMaxTime());
	ASSERT_EQUALS(3, room.level());
	ASSERT_EQUALS(6, room.getMaxParticipants());
	ASSERT_EQUALS(21, room.getAgeLimit());
}

void scaryCopyCtor() {
	ScaryRoom room1((char*) "ChanceTheWrapper", 60, 3, 6, 21, 100);
	ScaryRoom room2(room1);
	ASSERT_EQUALS(room1.getName(), room2.getName());
	ASSERT_EQUALS(room1.level(), room2.level());
	ASSERT_EQUALS(room1.getMaxParticipants(), room2.getMaxParticipants());
	ASSERT_EQUALS(room1.getMaxTime(), room2.getMaxTime());
	ASSERT_EQUALS(room1.getAgeLimit(), room2.getAgeLimit());
}

void assignOperatorTest() {
	ScaryRoom room1((char*) "ChanceTheWrapper", 60, 3, 6, 21, 100);
	ScaryRoom room2 = room1;
	ASSERT_EQUALS(room1.getName(), room2.getName());
	ASSERT_EQUALS(room1.level(), room2.level());
	ASSERT_EQUALS(room1.getMaxParticipants(), room2.getMaxParticipants());
	ASSERT_EQUALS(room1.getMaxTime(), room2.getMaxTime());
	ASSERT_EQUALS(room1.getAgeLimit(), room2.getAgeLimit());
}

void setNewAgeLimit() {
	ScaryRoom room((char*) "ChanceTheWrapper", 60, 3, 6, 21, 100);
	ASSERT_EQUALS(21, room.getAgeLimit());
	room.setNewAgeLimit(99);
	ASSERT_EQUALS(99, room.getAgeLimit());
}

int main_scary() {
	RUN_TEST(scaryRoomCtor);
	RUN_TEST(scaryCopyCtor);
	RUN_TEST(assignOperatorTest);
	RUN_TEST(setNewAgeLimit);
	return 0;
}

