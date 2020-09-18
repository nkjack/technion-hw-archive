/*
 * Room.c
 *
 *  Created on: May 30, 2017
 *      Author: Noam
 */

#include "room.h"

struct room {
	int id;
	int price;
	int num_ppl;
	char* work_hrs; //[TIME_STR_LEN];
	int hour_open;
	int hour_close;
	int difficulty; // 1-10
	TechnionFaculty faculty_of_room;
	char* company_email;
//	List orders;
};

/** STATIC FUNCTIONS **/

/**
 * this function take Room object and char* working hours for params,
 * parse the string of working hours into integer of open and integer of close.
 * And intialize the right fields in room.
 *
 * @param room the room we set the hours into
 * @param char* work_hrs the string of opening and closing hour
 *
 */
static void convertWorkHrsToInts(Room room, char* work_hrs) {
	int x1 = work_hrs[0] - '0';
	int x2 = work_hrs[1] - '0';
	int y1 = work_hrs[3] - '0';
	int y2 = work_hrs[4] - '0';
	int open = x1;
	open = open * 10;
	open = open + x2;
	int close = y1;
	close = close * 10;
	close = close + y2;
	room->hour_close = close;
	room->hour_open = open;
}

/**
 * This function check if the char* work_hrs that given for input is valid
 * according to the stanrd of the HW3
 */
static bool checkValidWorkHrs(char* work_hrs) {
	if (strlen(work_hrs) != 5) {
		return false;
	}
	if (work_hrs[0] < '0' || work_hrs[0] > '9') {
		return false;
	}
	if (work_hrs[1] < '0' || work_hrs[1] > '9') {
		return false;
	}
	if (work_hrs[3] < '0' || work_hrs[3] > '9') {
		return false;
	}
	if (work_hrs[4] < '0' || work_hrs[4] > '9') {
		return false;
	}
	if (work_hrs[2] != '-') {
		return false;
	}
	int x1 = work_hrs[0] - '0';
	int x2 = work_hrs[1] - '0';
	int y1 = work_hrs[3] - '0';
	int y2 = work_hrs[4] - '0';
	int open = x1;
	open = open * 10;
	open = open + x2;
	int close = y1;
	close = close * 10;
	close = close + y2;

	if (open < 0 || open > 24 || close < 0 || close > 24){
		return false;
	}
	return open < close;
}
/**
 * Duplicate a string and return it.
 * @param char* str, a string to duplicate
 * @return char* a copy of the inputed string
 */
static char* stringDuplicate(const char* str) {
	char* copy = malloc(strlen(str) + 1);
	return copy ? strcpy(copy, str) : NULL;
}

/**
 * check if difficulty level is between 1 and 10
 * @param int difficulty_level to check
 * @return true if valid, false otherwise
 */
static bool checkValidDifficultLevel(int difficult_level) {
	return (difficult_level > 0 && difficult_level <= 10);
}

/**
 * check if a certain room has valid working hourse. means opening hour before
 * closing hour.
 */
static bool checkWorkingHours(Room room) {
	return getRoomHourOpen(room) < getRoomHourClose(room);
}

/**
 * check if id of faculty is valid. according the mtm_ex3.h standards.
 */
static bool validFaculty(TechnionFaculty faculty) {
	return (faculty < UNKNOWN && faculty >= CIVIL_ENGINEERING);
}
/**
 * Check if the email is valid, meaning has only One '@'
 * @param char* email
 * @return true if valid, false otherwise
 */
static bool ifValidEmail(char* email) {
	assert(email != NULL);
	int counter = 0;
	for (int i = 0; i < strlen(email); i++) {
		if (email[i] == '@') {
			counter++;
		}
	}
	return (counter == 1);
}

/** IMPLEMENT HEADER **/
Room createRoom(int id, int price, int num_ppl, char* work_hr, int difficulty,
		TechnionFaculty faculty, char* company_email, RoomResult *result) {
	assert(result);
	if (!work_hr || !company_email){
		*result = ROOM_NULL_PARAMETER;
		return NULL;
	}
	Room room = malloc(sizeof(*room));
	if (!room) {
		*result = ROOM_OUT_OF_MEMORY;
		return NULL;
	}
	convertWorkHrsToInts(room, work_hr); //TODO-check working hrs
	if ((price % 4 != 0) || (id <= 0) || (price <= 0) || (num_ppl <= 0)
			|| !checkValidDifficultLevel(difficulty) || !checkWorkingHours(room)
			|| !validFaculty(faculty) || !checkValidWorkHrs(work_hr)
			|| !ifValidEmail(company_email) || (strlen(work_hr) != 5)) {
		free(room);
		*result = ROOM_INVALID_PARAMETER;
		return NULL;
	}
	room->company_email = stringDuplicate(company_email);
	if (!room->company_email) {
		free(room);
	}
	room->difficulty = difficulty;
	room->id = id;
	room->num_ppl = num_ppl;
	room->price = price;
	room->faculty_of_room = faculty;
	assert(strlen(work_hr) == (TIME_LEN));
	room->work_hrs = stringDuplicate(work_hr);
	if (!room->work_hrs) {
		result = ROOM_OUT_OF_MEMORY;
		free(room->company_email);
		free(room);
		return NULL;
	}
	*result = ROOM_SUCCESS;
	return room;
}
void destroyRoom(Room room) {
	if (room != NULL) {
		free(room->work_hrs);
		free(room->company_email);
		free(room);
	}
}

void freeRoomSetFunction(SetElement room) {
	destroyRoom((Room) room);
}

void freeRoomListFunction(ListElement room) {
	destroyRoom((Room) room);
}

Room roomCopy(Room room) {
	if (!room){
		return NULL;
	}
	RoomResult r_result = ROOM_DEFAULT;
	Room copy_room = createRoom(room->id, room->price, room->num_ppl,
			room->work_hrs, room->difficulty, room->faculty_of_room,
			room->company_email, &r_result);
	return copy_room;
}

SetElement roomCopySetFunction(SetElement room) {
	assert(room != NULL);
	return roomCopy((Room) room);
}

ListElement roomCopyListFunction(ListElement room) {
	assert(room != NULL);
	return roomCopy((Room) room);
}

int roomCompareById(Room room_1, Room room_2) {
	assert(room_1 != NULL && room_2 != NULL);
	return room_2->id - room_1->id;
}

int roomCompareByIdSetFunction(SetElement room1, SetElement room2) {
	return roomCompareById((Room) room1, (Room) room2);
}

bool compareRooms(Room room1, Room room2) {
	return ((strcmp(room1->company_email, room2->company_email) == 0)
			&& (room1->difficulty == room2->difficulty)
			&& (room1->faculty_of_room == room2->faculty_of_room)
			&& (room1->hour_close == room2->hour_close)
			&& (room1->hour_open == room2->hour_open)
			&& (room1->id == room2->id) && (room1->num_ppl == room2->num_ppl)
			&& (room1->price == room2->price));
}

int getRoomId(Room room) {
	assert(room);
	return room->id;
}

int getRoomHourOpen(Room room) {
	assert(room);
	return room->hour_open;
}
int getRoomHourClose(Room room) {
	assert(room);
	return room->hour_close;
}
int getRoomNumPpl(Room room) {
	assert(room);
	return room->num_ppl;
}
int getRoomPrice(Room room) {
	assert(room);
	return room->price;
}
int getRoomDifficulty(Room room) {
	assert(room);
	return room->difficulty;
}
TechnionFaculty getRoomFaculty(Room room) {
	assert(room);
	return room->faculty_of_room;
}

char* getRoomCompanyEmail(Room room) {
	assert(room);
	return room->company_email;
}
