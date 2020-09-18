/*
 * Company.c
 *
 *  Created on: May 30, 2017
 *      Author: Noam
 */

#include "company.h"
#define REGULAR_FUNC_CONST -1

struct company {
	Set rooms;
	TechnionFaculty faculty_id;
	char* email;
};

/** STATIC FUNCTIONS **/
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
 * check if working hourse of a room is valid. means open is lower than close.
 * @param room object
 * @return true if valid, false otherwise
 */
static bool checkWorkingHours(Room room) {
	return getRoomHourOpen(room) < getRoomHourClose(room);
}
/**
 * check if id of faculty is valid. according the mtm_ex3.h standards.
 */
static bool ifValidFaculty(TechnionFaculty faculty) {
	return (faculty < UNKNOWN && faculty >= CIVIL_ENGINEERING);
}

/**
 * this function get company and Set of rooms for input, and add each room
 * in the set to the company set of rooms.
 * @param company
 * @param rooms
 * @return True if the procces was clean, false if problem with
 * 	memory allocations.
 */
static bool addSetOfRooms(Company company, Set rooms) {
	SET_FOREACH(Room, room, rooms)
	{
		if (setAdd(company->rooms, room)!= SET_SUCCESS){
			setDestroy(company->rooms);
			return false;
		}
//		addRoomToCompany(company, roomCopy(room));
	}
	return true;
}
/** IMPLEMENT HEADER **/
Company createCompany(char* email, TechnionFaculty faculty,
		CompanyResult* company_result) {
	assert(company_result);
	if (!email){
		*company_result = COMPANY_NULL_PARAMETER;
		return NULL;
	}
	if (!ifValidEmail(email) || !ifValidFaculty(faculty)) {
		*company_result = COMPANY_INVALID_PARAMETER;
		return NULL;
	}
	Company company = malloc(sizeof(*company));
	if (company == NULL) {
		*company_result = COMPANY_OUT_OF_MEMORY;
		return NULL;
	}
	company->email = stringDuplicate(email);
	if (!company->email) {
		*company_result = COMPANY_OUT_OF_MEMORY;
		free(company);
		return NULL;
	}
	company->faculty_id = faculty;
	company->rooms = setCreate(roomCopySetFunction, freeRoomSetFunction,
			roomCompareByIdSetFunction);
	if (!company->rooms) {
		*company_result = COMPANY_OUT_OF_MEMORY;
		free(company->email);
		free(company);
		return NULL;
	}
	*company_result = COMPANY_SUCCESS;
	return company;
}

void destroyCompany(Company company) {
	if (company != NULL) {
		free(company->email);
		setDestroy(company->rooms);
		free(company);
	}
}

Company companyCopy(Company company) {
	CompanyResult result = COMPANY_SUCCESS;
	if (company == NULL) {
		return NULL;
	}
	Company new_company = createCompany(company->email, company->faculty_id,
			&result);
	if (new_company == NULL) {
		return NULL;
	}
	if (!addSetOfRooms(new_company, company->rooms)){
		destroyCompany(new_company);
		return NULL;
	}
//	new_company->rooms = setCopy(company->rooms);
	return new_company;
}
SetElement companyCopySetFunction(SetElement company) {
	assert(company != NULL);
	return companyCopy((Company) company);
}

ListElement companyCopyListFunction(ListElement company) {
	assert(company != NULL);
	return companyCopy((Company) company);

}

int companyCompareEmails(SetElement company_1, SetElement company_2) {
	assert(company_1 && company_2);
	return strcmp(((Company) company_1)->email, ((Company) company_2)->email);
}

int companyCompareFaculties(SetElement company_1, SetElement company_2) {
	assert(company_1 && company_2);
	return ((Company) company_1)->faculty_id - ((Company) company_2)->faculty_id;
}

CompanyResult addRoomToCompany(Company company, Room room) {
	if (!company || !room) {
		return COMPANY_NULL_PARAMETER;
	}
	if ((getRoomId(room) <= 0) || (getRoomNumPpl(room) <= 0)
			|| (getRoomPrice(room) % 4 != 0) || (getRoomPrice(room) <= 0)
			|| (!checkValidDifficultLevel(getRoomDifficulty(room)))
			|| (!checkWorkingHours(room))
			|| (strcmp(getRoomCompanyEmail(room), company->email) != 0)) {
		return COMPANY_INVALID_PARAMETER;
	}
	SetResult set_result = setAdd(company->rooms, room);
	if (set_result == SET_NULL_ARGUMENT) {
		return COMPANY_NULL_PARAMETER;
	} else if (set_result == SET_OUT_OF_MEMORY) {
		return COMPANY_OUT_OF_MEMORY;
	} else if (set_result == SET_ITEM_ALREADY_EXISTS) {
		return COMPANY_ROOM_ALREADY_EXIST;
	}
	return COMPANY_SUCCESS;
}

CompanyResult removeRoomFromCompany(Company company, int id) {
	if (!company) {
		return COMPANY_NULL_PARAMETER;
	}
	SET_FOREACH(Room, room, company->rooms)
	{
		if (getRoomId(room) == id) {
			SetResult set_result = setRemove(company->rooms, room);
			if (set_result == SET_NULL_ARGUMENT) {
				return COMPANY_NULL_PARAMETER;
			} else if (set_result == SET_ITEM_DOES_NOT_EXIST) {
				return COMPANY_ROOM_DOES_NOT_EXIST;
			}
			return COMPANY_SUCCESS;
		}
	}
	return COMPANY_ROOM_DOES_NOT_EXIST;
}

char* getCompanyEmail(Company company) {
	if (!company) {
		return NULL;
	}
	return company->email;
}

TechnionFaculty getCompanyFaculty(Company company) {
	if (!company) {
		return UNKNOWN;
	}
	int fac_id = company->faculty_id;
	return fac_id;
}

void freeCompanySetFunction(SetElement company) {
	destroyCompany((Company) company);
}
void freeCompanyListFunction(ListElement company) {
	destroyCompany((Company) (company));
}

bool checkCompanyHasRoomWithId(Company company, int id) {
	assert(company != NULL);
	SET_FOREACH(Room, room, company->rooms)
	{
		if (getRoomId(room) == id) {
			return true;
		}
	}
	return false;
}

int getRoomDifficultyFromCompany(Company company, int room_id) {
	assert(company != NULL);
	SET_FOREACH(Room, room, company->rooms)
	{
		if (getRoomId(room) == room_id) {
			return getRoomDifficulty(room);
		}
	}
	return REGULAR_FUNC_CONST;
}

int getRoomPriceFromCompany(Company company, int room_id) {
	assert(company != NULL);
	SET_FOREACH(Room, room, company->rooms)
	{
		if (getRoomId(room) == room_id) {
			return getRoomPrice(room);
		}
	}
	return REGULAR_FUNC_CONST;
}

List companyGetListOfRooms(Company company) {
	if (!company) {
		return NULL;
	}
	List list_rooms = listCreate(roomCopyListFunction, freeRoomListFunction);
	if (list_rooms == NULL) {
		return NULL;
	}
	SET_FOREACH(Room, room, company->rooms)
	{
		if (listInsertLast(list_rooms, room) != LIST_SUCCESS) {
			listDestroy(list_rooms);
			return NULL;
		}
	}
	return list_rooms;
}

Set getCopyOfAllRooms(Company company) {
	if (!company) {
		return NULL;
	}
	return setCopy(company->rooms);
}

int companyGetSizeOfRooms(Company company) {
	assert(company);
	return setGetSize(company->rooms);
}

