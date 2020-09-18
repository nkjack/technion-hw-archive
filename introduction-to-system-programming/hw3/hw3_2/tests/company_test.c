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
#include "../company.h"
#include "../room.h"

#define INVALID_INT -1
#define VALID_INT 1

static int roomCompareList(ListElement room_1, ListElement room_2) {
	assert(room_1 != NULL && room_2 != NULL);
	return getRoomId((Room)room_1) - getRoomId((Room)room_2);
}

static bool testCompanyCreate() {
	CompanyResult result;
	Company comp1 = createCompany(NULL,1,&result);
	ASSERT_TEST(comp1 == NULL);
	ASSERT_TEST(result == COMPANY_NULL_PARAMETER);
	Company comp2 = createCompany("invalid_email",INVALID_INT,&result);
	ASSERT_TEST(comp2 == NULL);
	ASSERT_TEST(result == COMPANY_INVALID_PARAMETER);
	Company comp3 = createCompany("valid@email",INVALID_INT,&result);
	ASSERT_TEST(comp3 == NULL);
	ASSERT_TEST(result == COMPANY_INVALID_PARAMETER);
	Company comp4 = createCompany("invalid_@@@email",VALID_INT,&result);
	ASSERT_TEST(comp4 == NULL);
	ASSERT_TEST(result == COMPANY_INVALID_PARAMETER);
	Company comp5 = createCompany("valid@email",UNKNOWN,&result);
	ASSERT_TEST(comp5 == NULL);
	ASSERT_TEST(result == COMPANY_INVALID_PARAMETER);
	Company comp6 = createCompany("valid@email", VALID_INT, &result);
	ASSERT_TEST(comp6 != NULL);
	ASSERT_TEST(result == COMPANY_SUCCESS);
	destroyCompany(comp6);
	return true;
}

static bool testCompanyDestroy() {
	CompanyResult result;
	Company comp  = createCompany("valid@email", VALID_INT, &result);
	ASSERT_TEST(comp != NULL);
	ASSERT_TEST(result == COMPANY_SUCCESS);
	destroyCompany(comp);
	return true;
}

static bool testCompanyCopy() {
	CompanyResult result;
	Company comp = createCompany("valid@email", COMPUTER_SCIENCE, &result);
	Company comp1 = companyCopy(NULL);
	ASSERT_TEST(comp1 == NULL);
	comp1 = companyCopy(comp);
	ASSERT_TEST(comp1 != NULL);
	ASSERT_TEST(strcmp(getCompanyEmail(comp1), "valid@email") == 0);
	ASSERT_TEST(getCompanyFaculty(comp1) == COMPUTER_SCIENCE);
	destroyCompany(comp1);
	ASSERT_TEST(comp != NULL);
	RoomResult r_result;
	Room room = createRoom(1, 12, 3, "06-12", 5, COMPUTER_SCIENCE,
			"valid@email", &r_result);
	ASSERT_TEST(room != NULL);
	ASSERT_TEST(r_result == ROOM_SUCCESS);
	addRoomToCompany(comp, room);
	destroyRoom(room);
	Company comp2 = companyCopy(comp);
	ASSERT_TEST(comp2 != NULL);
	ASSERT_TEST(strcmp(getCompanyEmail(comp2), "valid@email") == 0);
	ASSERT_TEST(getCompanyFaculty(comp2) == COMPUTER_SCIENCE);
	Set rooms_comp1 = getCopyOfAllRooms(comp2);
	Set rooms_comp = getCopyOfAllRooms(comp);
	Room room1 = setGetFirst(rooms_comp1);
	Room room2 = setGetFirst(rooms_comp);
	ASSERT_TEST(compareRooms(room1, room2));

	destroyCompany(comp);
	destroyCompany(comp2);
	setDestroy(rooms_comp1);
	setDestroy(rooms_comp);
	return true;
}

static bool testCompanyCompareEmails() {
	CompanyResult result;
	Company comp = createCompany("valid@email", COMPUTER_SCIENCE, &result);
	ASSERT_TEST(result == COMPANY_SUCCESS);
	Company comp1 = companyCopy(comp);
	ASSERT_TEST(result == COMPANY_SUCCESS);
	ASSERT_TEST(companyCompareEmails(comp, comp1) == 0);
	destroyCompany(comp1);
	Company comp2 = createCompany("valid2@email", COMPUTER_SCIENCE, &result);
	ASSERT_TEST(result == COMPANY_SUCCESS);
	ASSERT_TEST(companyCompareEmails(comp, comp2) != 0);
	destroyCompany(comp2);
	destroyCompany(comp);
	return true;
}

static bool testCompanyCompareFaculties() {
	CompanyResult result;
	Company comp = createCompany("valid@email", COMPUTER_SCIENCE, &result);
	ASSERT_TEST(result == COMPANY_SUCCESS);
	Company comp1 = companyCopy(comp);
	ASSERT_TEST(result == COMPANY_SUCCESS);
	ASSERT_TEST(companyCompareFaculties(comp, comp1) == 0);
	destroyCompany(comp1);
	Company comp2 = createCompany("valid@email", MATHEMATICS, &result);
	ASSERT_TEST(result == COMPANY_SUCCESS);
	ASSERT_TEST(companyCompareFaculties(comp, comp2) != 0);
	destroyCompany(comp2);
	destroyCompany(comp);
	return true;
}

static bool testAddRoomToCompany() {
	CompanyResult result;
	Company comp = createCompany("valid@email", COMPUTER_SCIENCE, &result);
	ASSERT_TEST(result == COMPANY_SUCCESS);
	result = addRoomToCompany(NULL, NULL);
	ASSERT_TEST(result == COMPANY_NULL_PARAMETER);
	result = addRoomToCompany(comp, NULL);
	ASSERT_TEST(result == COMPANY_NULL_PARAMETER);
	RoomResult r_result;
	Room room = createRoom(1, 12, 3, "06-12", 5, COMPUTER_SCIENCE,
			"valid@email", &r_result);
	ASSERT_TEST(r_result == ROOM_SUCCESS);
	result = addRoomToCompany(NULL, room);
	ASSERT_TEST(result == COMPANY_NULL_PARAMETER);
	result = addRoomToCompany(comp, room);
	ASSERT_TEST(result == COMPANY_SUCCESS);
	result = addRoomToCompany(comp, room);
	ASSERT_TEST(result == COMPANY_ROOM_ALREADY_EXIST);
	ASSERT_TEST(companyGetSizeOfRooms(comp) == 1);
	destroyCompany(comp);
	destroyRoom(room);
	return true;
}

static bool testRemoveRoomFromCompany() {
	CompanyResult result;
	Company comp = createCompany("valid@email", COMPUTER_SCIENCE, &result);
	ASSERT_TEST(result == COMPANY_SUCCESS);
	result = removeRoomFromCompany(NULL, 12);
	ASSERT_TEST(result == COMPANY_NULL_PARAMETER);
	result = removeRoomFromCompany(comp, 12);
	RoomResult r_result;
	Room room = createRoom(1, 12, 3, "06-12", 5, COMPUTER_SCIENCE,
			"valid@email", &r_result);
	ASSERT_TEST(r_result == ROOM_SUCCESS);
	result = addRoomToCompany(comp, room);
	ASSERT_TEST(result == COMPANY_SUCCESS);
	ASSERT_TEST(companyGetSizeOfRooms(comp) == 1);
	result = removeRoomFromCompany(comp, 1);
	ASSERT_TEST(result == COMPANY_SUCCESS);
	ASSERT_TEST(companyGetSizeOfRooms(comp) == 0);
	ASSERT_TEST(room != NULL);
	result = removeRoomFromCompany(comp, 1);
	ASSERT_TEST(result = COMPANY_ROOM_DOES_NOT_EXIST);

	destroyRoom(room);
	destroyCompany(comp);
	return true;
}

static bool testAllCompanyGets() {
	//getCompanyEmail
	CompanyResult result;
	Company comp = createCompany("valid@email", COMPUTER_SCIENCE, &result);
	ASSERT_TEST(result == COMPANY_SUCCESS);
	ASSERT_TEST(strcmp(getCompanyEmail(comp), "valid@email") == 0);
	ASSERT_TEST(strcmp(getCompanyEmail(comp), "valid1@email") != 0);
	//getCompanyFaculty
	ASSERT_TEST(getCompanyFaculty(comp) == COMPUTER_SCIENCE);
	RoomResult r_result;
	Room room = createRoom(1, 12, 3, "06-12", 5, COMPUTER_SCIENCE,
			"valid@email", &r_result);
	ASSERT_TEST(r_result == ROOM_SUCCESS);
	result = addRoomToCompany(comp, room);
	ASSERT_TEST(result == COMPANY_SUCCESS);
	int price = getRoomPriceFromCompany(comp, 1);
	ASSERT_TEST(price == 12);
	price = getRoomPriceFromCompany(comp, 3);
	ASSERT_TEST(price == INVALID_INT);
	int diff = getRoomDifficultyFromCompany(comp, 1);
	ASSERT_TEST(diff == 5);
	diff = getRoomDifficultyFromCompany(comp, 3);
	ASSERT_TEST(diff = INVALID_INT);
	int rooms_size = companyGetSizeOfRooms(comp);
	ASSERT_TEST(rooms_size == 1);

	Room room1 = createRoom(2, 12, 3, "06-12", 5, COMPUTER_SCIENCE,
			"valid1@email", &r_result);
	Room room2 = createRoom(3, 12, 3, "06-12", 5, COMPUTER_SCIENCE,
			"valid@email", &r_result);
	Room room3 = createRoom(3, 12, 3, "06-12", 5, COMPUTER_SCIENCE,
			"valid@email", &r_result);
	ASSERT_TEST(addRoomToCompany(comp, room1) == COMPANY_INVALID_PARAMETER);
	ASSERT_TEST(addRoomToCompany(comp, room2) == COMPANY_SUCCESS);
	ASSERT_TEST(addRoomToCompany(comp, room3) == COMPANY_ROOM_ALREADY_EXIST);
	ASSERT_TEST(companyGetSizeOfRooms(comp) == 2);
	List list = companyGetListOfRooms(comp);
	listSort(list,roomCompareList);
	ASSERT_TEST(list != NULL);
	ASSERT_TEST(getRoomId((Room )listGetFirst(list)) == 1);
	ASSERT_TEST(getRoomId((Room )listGetNext(list)) == 3);
	ASSERT_TEST(listGetNext(list) == NULL);
	listDestroy(list);
	ASSERT_TEST(companyGetSizeOfRooms(comp) == 2);
	removeRoomFromCompany(comp, 1);
	ASSERT_TEST(companyGetSizeOfRooms(comp) == 1);
	destroyRoom(room);
	destroyRoom(room1);
	destroyRoom(room2);
	destroyRoom(room3);
	destroyCompany(comp);
	return true;
}

static bool testCheckCompanyHasRoomWithId() {
	CompanyResult result;
	Company comp = createCompany("valid@email", COMPUTER_SCIENCE, &result);
	ASSERT_TEST(result == COMPANY_SUCCESS);
	RoomResult r_result;
	Room room1 = createRoom(1, 12, 3, "06-12", 5, COMPUTER_SCIENCE,
			"valid@email", &r_result);
	Room room2 = createRoom(2, 12, 3, "06-12", 5, COMPUTER_SCIENCE,
			"valid@email", &r_result);
	Room room3 = createRoom(3, 12, 3, "06-12", 5, COMPUTER_SCIENCE,
			"valid@email", &r_result);
	ASSERT_TEST(addRoomToCompany(comp, room1) == COMPANY_SUCCESS);
	ASSERT_TEST(addRoomToCompany(comp, room2) == COMPANY_SUCCESS);
	ASSERT_TEST(addRoomToCompany(comp, room3) == COMPANY_SUCCESS);
	ASSERT_TEST(checkCompanyHasRoomWithId(comp,1));
	ASSERT_TEST(checkCompanyHasRoomWithId(comp,2));
	ASSERT_TEST(checkCompanyHasRoomWithId(comp,3));
	ASSERT_TEST(!checkCompanyHasRoomWithId(comp,4));
	destroyCompany(comp);
	destroyRoom(room1);
	destroyRoom(room2);
	destroyRoom(room3);
	return true;
}

int main6(int argv, char** arc) {
	RUN_TEST(testCompanyCreate);
	RUN_TEST(testCompanyDestroy);
	RUN_TEST(testCompanyCopy);
	RUN_TEST(testCompanyCompareEmails);
	RUN_TEST(testCompanyCompareFaculties);
	RUN_TEST(testAddRoomToCompany);
	RUN_TEST(testRemoveRoomFromCompany);
	RUN_TEST(testAllCompanyGets);
	RUN_TEST(testCheckCompanyHasRoomWithId);

	return 0;
}
