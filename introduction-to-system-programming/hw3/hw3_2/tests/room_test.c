/*
 * unit_test_room.c
 *
 *  Created on: Jun 12, 2017
 *      Author: Noam
 */

/*
 * uni_tests_escaper_technion.c
 *
 *  Created on: Jun 12, 2017
 *      Author: Noam
 */
#include "test_utilities.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../mtm_ex3.h"
#include "../room.h"

#define INVALID_INT -1
#define VALID_INT 1

static bool testRoomCreate() {
	RoomResult result;
	Room room = createRoom(1, 4, 4, "06-12", 3, COMPUTER_SCIENCE,
			"valid@email.com", &result);
	ASSERT_TEST(room != NULL);
	ASSERT_TEST(result == ROOM_SUCCESS);
	destroyRoom(room);
	room = createRoom(1, 5, 4, NULL, 3, COMPUTER_SCIENCE, "valid@email.com",
			&result);
	ASSERT_TEST(result == ROOM_NULL_PARAMETER);
	room = createRoom(1, 5, 4, "06-12", 3, COMPUTER_SCIENCE, NULL,
			&result);
	ASSERT_TEST(result == ROOM_NULL_PARAMETER);
	room = createRoom(1, 5, 4, "06-12", 3, COMPUTER_SCIENCE, "valid@email.com",
			&result);
	ASSERT_TEST(result == ROOM_INVALID_PARAMETER);
	destroyRoom(room);
	room = createRoom(1, -4, 4, "06-12", 3, COMPUTER_SCIENCE, "valid@email.com",
			&result);
	ASSERT_TEST(result == ROOM_INVALID_PARAMETER);
	destroyRoom(room);
	room = createRoom(1, 4, -1, "06-12", 3, COMPUTER_SCIENCE, "valid@email.com",
			&result);
	ASSERT_TEST(result == ROOM_INVALID_PARAMETER);
	destroyRoom(room);
	room = createRoom(1, 4, 4, "6-12", 3, COMPUTER_SCIENCE, "valid@email.com",
			&result);
	ASSERT_TEST(result == ROOM_INVALID_PARAMETER);
	destroyRoom(room);
	room = createRoom(-1, 4, 4, "06-12", 3, COMPUTER_SCIENCE, "valid@email.com",
			&result);
	ASSERT_TEST(result == ROOM_INVALID_PARAMETER);
	destroyRoom(room);
	room = createRoom(1, 4, 4, "06-12", 3, -1, "valid@email.com", &result);
	ASSERT_TEST(result == ROOM_INVALID_PARAMETER);
	destroyRoom(room);
	room = createRoom(1, 4, 4, "06-12", 3, UNKNOWN, "valid@email.com", &result);
	ASSERT_TEST(result == ROOM_INVALID_PARAMETER);
	destroyRoom(room);
	room = createRoom(1, 4, 4, "06-12", 3, COMPUTER_SCIENCE, "valid1email.com",
			&result);
	ASSERT_TEST(result == ROOM_INVALID_PARAMETER);
	destroyRoom(room);
	return true;
}

static bool testRoomDestroy() {
	RoomResult result;
	Room room = createRoom(1, 4, 4, "06-12", 3, COMPUTER_SCIENCE,
			"valid@email.com", &result);
	ASSERT_TEST(room != NULL);
	ASSERT_TEST(result == ROOM_SUCCESS);
	destroyRoom(room);
	return true;
}

static bool testRoomCopy() {
	RoomResult result;
	Room room = createRoom(1, 4, 4, "06-12", 3, COMPUTER_SCIENCE,
			"valid@email.com", &result);
	ASSERT_TEST(room != NULL);
	Room room1 = roomCopy(NULL);
	ASSERT_TEST(room1 == NULL);
	room1 = roomCopy(room);
	ASSERT_TEST(room1 != NULL);
	ASSERT_TEST(strcmp(getRoomCompanyEmail(room1), "valid@email.com") == 0);
	ASSERT_TEST(getRoomId(room1) == 1);
	destroyRoom(room1);
	ASSERT_TEST(room != NULL);
	destroyRoom(room);
	return true;
}

static bool testCompares() {
	RoomResult result;
	Room room = createRoom(1, 4, 4, "06-12", 3, COMPUTER_SCIENCE,
			"valid@email.com", &result);
	ASSERT_TEST(result == ROOM_SUCCESS);
	Room room1 = roomCopy(room);
	ASSERT_TEST(roomCompareById(room, room1) == 0);
	ASSERT_TEST(compareRooms(room, room1));
	destroyRoom(room1);
	room1 = createRoom(2, 4, 4, "06-12", 3, COMPUTER_SCIENCE, "valid@email.com",
			&result);
	ASSERT_TEST(result == ROOM_SUCCESS);
	ASSERT_TEST(roomCompareById(room, room1) > 0);
	destroyRoom(room1);
	room1 = createRoom(1, 4, 4, "06-12", 3, MECHANICAL_ENGINEERING,
			"valid@email.com", &result);
	ASSERT_TEST(!compareRooms(room, room1));
	destroyRoom(room1);
	room1 = createRoom(1, 4, 4, "06-13", 3, COMPUTER_SCIENCE, "valid@email.com",
			&result);
	ASSERT_TEST(!compareRooms(room, room1));
	destroyRoom(room1);
	room1 = createRoom(1, 4, 4, "06-12", 4, COMPUTER_SCIENCE, "valid@email.com",
			&result);
	ASSERT_TEST(!compareRooms(room, room1));
	destroyRoom(room1);
	room1 = createRoom(1, 4, 4, "06-12", 3, COMPUTER_SCIENCE,
			"vali1d@email.com", &result);
	ASSERT_TEST(!compareRooms(room, room1));
	destroyRoom(room);
	destroyRoom(room1);
	return true;
}

static bool testRoomGets() {
	RoomResult result;
	Room room = createRoom(1, 4, 4, "06-12", 3, COMPUTER_SCIENCE,
			"valid@email.com", &result);
	ASSERT_TEST(result == ROOM_SUCCESS);
	ASSERT_TEST(strcmp(getRoomCompanyEmail(room), "valid@email.com") == 0);
	ASSERT_TEST(getRoomDifficulty(room) == 3);
	ASSERT_TEST(getRoomFaculty(room) == COMPUTER_SCIENCE);
	ASSERT_TEST(getRoomHourClose(room) == 12);
	ASSERT_TEST(getRoomHourOpen(room) == 6);
	ASSERT_TEST(getRoomId(room) == 1);
	ASSERT_TEST(getRoomPrice(room) == 4);
	destroyRoom(room);
	return true;
}
int main1(int argv, char** arc) {
	RUN_TEST(testRoomCreate);
	RUN_TEST(testRoomDestroy);
	RUN_TEST(testRoomCopy);
	RUN_TEST(testCompares);
	RUN_TEST(testRoomGets);
	return 0;
}

