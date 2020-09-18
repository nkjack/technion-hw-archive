/*
 * unit_test_escape_technion.c
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
#include "../escape_technion.h"
#include "../mtm_ex3.h"

#define INVALID_INT -1
#define VALID_INT 1

static bool testSystemCreateDestroy() {
	EscapeTechnion escapeTechnion = createEscapeTechnion();
	ASSERT_TEST(escapeTechnion != NULL);
	destroyEscapeTechnion(escapeTechnion);
	return true;
}

static bool testAddCompany() {
	MtmErrorCode result;
	EscapeTechnion escapeTechnion = createEscapeTechnion();
	ASSERT_TEST(escapeTechnion != NULL);
	result = companyAdd(escapeTechnion, "invalidemail", COMPUTER_SCIENCE);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = companyAdd(escapeTechnion, "valid@email", INVALID_INT);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = companyAdd(escapeTechnion, "valid@email", UNKNOWN);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = companyAdd(escapeTechnion, "valid@email", COMPUTER_SCIENCE);
	ASSERT_TEST(result == MTM_SUCCESS);
	Set set = getCompaniesSet(escapeTechnion);
	ASSERT_TEST(set != NULL);
	ASSERT_TEST(setGetSize(set) == 1);
	Company comp = (Company) setGetFirst(set);
	ASSERT_TEST(strcmp(getCompanyEmail(comp), "valid@email") == 0);
	ASSERT_TEST(comp != NULL);
	ASSERT_TEST(set != NULL);
	setDestroy(set);

	result = companyAdd(escapeTechnion, "valid@email", COMPUTER_SCIENCE);
	ASSERT_TEST(result == MTM_EMAIL_ALREADY_EXISTS);
	result = escaperAdd(escapeTechnion, "theking@gmail.com", MATHEMATICS, 2);
	ASSERT_TEST(result = MTM_SUCCESS);
	result = companyAdd(escapeTechnion, "theking@gmail.com", COMPUTER_SCIENCE);
	ASSERT_TEST(result == MTM_EMAIL_ALREADY_EXISTS);
	result = companyAdd(escapeTechnion, "theking@gmail.com",
			ELECTRICAL_ENGINEERING);
	ASSERT_TEST(result == MTM_EMAIL_ALREADY_EXISTS);
	destroyEscapeTechnion(escapeTechnion);
	return true;
}

static bool testRemoveCompany() {
	MtmErrorCode result;
	EscapeTechnion escapeTechnion = createEscapeTechnion();
	ASSERT_TEST(escapeTechnion != NULL);
	result = companyRemove(escapeTechnion, "validemail");
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = companyRemove(escapeTechnion, "valid@email");
	ASSERT_TEST(result == MTM_COMPANY_EMAIL_DOES_NOT_EXIST);
	result = companyAdd(escapeTechnion, "valid@email", COMPUTER_SCIENCE);
	ASSERT_TEST(result == MTM_SUCCESS);
	Set set = getCompaniesSet(escapeTechnion);
	ASSERT_TEST(set != NULL);
	ASSERT_TEST(setGetSize(set) == 1);
	Company comp = (Company) setGetFirst(set);
	ASSERT_TEST(strcmp(getCompanyEmail(comp), "valid@email") == 0);
	setDestroy(set);
	result = companyRemove(escapeTechnion, "valid1@email");
	ASSERT_TEST(result == MTM_COMPANY_EMAIL_DOES_NOT_EXIST);
	result = roomAdd(escapeTechnion, "valid@email", 1, 4, 4, "06-17", 3);
	ASSERT_TEST(result == MTM_SUCCESS);
	Set set_comps = getCompaniesSet(escapeTechnion);
	comp = (Company) setGetFirst(set_comps);
	Set set_rooms = getCopyOfAllRooms(comp);
	Room room = setGetFirst(set_rooms);
	ASSERT_TEST(set_comps != NULL);
	ASSERT_TEST(set_rooms != NULL);
	ASSERT_TEST(setGetSize(set_rooms) == 1);
	ASSERT_TEST(setGetSize(set_comps) == 1);
	ASSERT_TEST(getRoomId(room) == 1);
	setDestroy(set_comps);
	setDestroy(set_rooms);
	result = escaperAdd(escapeTechnion, "escaper@mail", COMPUTER_SCIENCE, 5);
	ASSERT_TEST(result == MTM_SUCCESS);
	Set set_escapers = getEscapersSet(escapeTechnion);
	ASSERT_TEST(set_escapers != NULL);
	ASSERT_TEST(setGetSize(set_escapers) == 1);
	Escaper escaper = setGetFirst(set_escapers);
	ASSERT_TEST(strcmp(getEscaperEmail(escaper), "escaper@mail") == 0);
	setDestroy(set_escapers);
	result = escaperOrder(escapeTechnion, "escaper@mail", COMPUTER_SCIENCE, 1,
			"0-12", 4);
	ASSERT_TEST(result == MTM_SUCCESS);
	List list_orders = getOrderList(escapeTechnion);
	ASSERT_TEST(list_orders != NULL);
	ASSERT_TEST(listGetSize(list_orders) == 1);
	Order order = listGetFirst(list_orders);
	ASSERT_TEST(strcmp(getOrderEscaperEmail(order), "escaper@mail") == 0);
	result = companyRemove(escapeTechnion, "valid@email");
	ASSERT_TEST(result == MTM_RESERVATION_EXISTS);
	listDestroy(list_orders);
	reportDay(escapeTechnion, stdout);
	result = companyRemove(escapeTechnion, "valid@email");
	ASSERT_TEST(result == MTM_SUCCESS);
	destroyEscapeTechnion(escapeTechnion);
	return true;
}

static bool testAddRoom() {
	MtmErrorCode result;
	EscapeTechnion escapeTechnion = createEscapeTechnion();
	ASSERT_TEST(escapeTechnion != NULL);
	result = companyAdd(escapeTechnion, "valid@email", COMPUTER_SCIENCE);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = roomAdd(escapeTechnion, "validemail", 1, 4, 4, "06-12", 3);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = roomAdd(escapeTechnion, "valid@email", 1, 4, 4, "06+12", 3);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = roomAdd(escapeTechnion, "valid@email", 1, 4, 4, "13-12", 3);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = roomAdd(escapeTechnion, "valid@email", 1, 4, 4, "a2-12", 3);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = roomAdd(escapeTechnion, "valid@email", -1, 4, 4, "06-12", 3);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = roomAdd(escapeTechnion, "valid@email", 1, 3, 4, "06-12", 3);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = roomAdd(escapeTechnion, "valid@email", 1, 4, -5, "06-12", 3);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = roomAdd(escapeTechnion, "valid@email", 1, 4, 4, "06-12", 11);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = roomAdd(escapeTechnion, "valid2@email", 1, 4, 4, "06-12", 3);
	ASSERT_TEST(result == MTM_COMPANY_EMAIL_DOES_NOT_EXIST);
	result = roomAdd(escapeTechnion, "valid@email", 1, 4, 4, "06-12", 3);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = roomAdd(escapeTechnion, "valid@email", 1, 8, 4, "06-17", 7);
	ASSERT_TEST(result == MTM_ID_ALREADY_EXIST);
	result = roomAdd(escapeTechnion, "valid2@email", 1, 8, 4, "06-17", 7);
	ASSERT_TEST(result == MTM_COMPANY_EMAIL_DOES_NOT_EXIST);
	destroyEscapeTechnion(escapeTechnion);
	return true;
}

static bool testRoomRemove() {
	MtmErrorCode result;
	EscapeTechnion escapeTechnion = createEscapeTechnion();
	ASSERT_TEST(escapeTechnion != NULL);
	result = companyAdd(escapeTechnion, "valid@email", COMPUTER_SCIENCE);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = roomAdd(escapeTechnion, "valid@email", 1, 4, 4, "06-12", 3);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = roomRemove(escapeTechnion, UNKNOWN, 1);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = roomRemove(escapeTechnion, INVALID_INT, 1);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = roomRemove(escapeTechnion, MATHEMATICS, 1);
	ASSERT_TEST(result == MTM_ID_DOES_NOT_EXIST);
	result = roomRemove(escapeTechnion, COMPUTER_SCIENCE, 2);
	ASSERT_TEST(result == MTM_ID_DOES_NOT_EXIST);
	result = escaperAdd(escapeTechnion, "escaper@mail", MATERIALS_ENGINEERING,
			5);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = roomRemove(escapeTechnion, COMPUTER_SCIENCE, 1);
	ASSERT_TEST(result == MTM_SUCCESS);
	Set set_comps = getCompaniesSet(escapeTechnion);
	ASSERT_TEST(set_comps != NULL);
	Company comp = setGetFirst(set_comps);
	Set set_rooms = getCopyOfAllRooms(comp);
	ASSERT_TEST(set_rooms != NULL);
	ASSERT_TEST(setGetSize(set_rooms) == 0);
	setDestroy(set_rooms);
	setDestroy(set_comps);
	result = roomAdd(escapeTechnion, "valid@email", 1, 4, 4, "06-12", 3);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "escaper@mail", COMPUTER_SCIENCE, 1,
			"0-11", 4);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = roomRemove(escapeTechnion, COMPUTER_SCIENCE, 1);
	ASSERT_TEST(result == MTM_RESERVATION_EXISTS);
	destroyEscapeTechnion(escapeTechnion);
	return true;
}

static bool testAddEscaper() {
	EscapeTechnion escapeTechnion = createEscapeTechnion(); ///initialize the system
	ASSERT_TEST(
			escaperAdd(escapeTechnion, "samueltheking", COMPUTER_SCIENCE, 5)
					== MTM_INVALID_PARAMETER); ///checks invalid parameters
	ASSERT_TEST(
			escaperAdd(escapeTechnion, "samuel@gmail", UNKNOWN, 5)
					== MTM_INVALID_PARAMETER);
	ASSERT_TEST(
			escaperAdd(escapeTechnion, "samuel@gmail", COMPUTER_SCIENCE, -1)
					== MTM_INVALID_PARAMETER);
	ASSERT_TEST(
			escaperAdd(escapeTechnion, "valid@email", COMPUTER_SCIENCE, 5)
					== MTM_SUCCESS); ///insertion succeeded
	ASSERT_TEST(
			escaperAdd(escapeTechnion, "valid@email", COMPUTER_SCIENCE, 0)
					== MTM_INVALID_PARAMETER); /// checks invalid parameter over email already exists
	ASSERT_TEST(
			escaperAdd(escapeTechnion, "valid@email", ELECTRICAL_ENGINEERING, 3)
					== MTM_EMAIL_ALREADY_EXISTS); ////check email already exists
	ASSERT_TEST(
			companyAdd(escapeTechnion, "another@valid", COMPUTER_SCIENCE)
					== MTM_SUCCESS); ///add the company to the system succeded
	ASSERT_TEST(
			escaperAdd(escapeTechnion, "another@valid", COMPUTER_SCIENCE, 3)
					== MTM_EMAIL_ALREADY_EXISTS); ///checks recognizing of other types' email
	destroyEscapeTechnion(escapeTechnion);
	return true;
}

static bool testEscaperRemove() {
	EscapeTechnion escapeTechnion = createEscapeTechnion();
	MtmErrorCode result;
	result = escaperAdd(escapeTechnion, "first@email", COMPUTER_SCIENCE, 5);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperAdd(escapeTechnion, "second@email", COMPUTER_SCIENCE, 5);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperAdd(escapeTechnion, "third@email", COMPUTER_SCIENCE, 5);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperAdd(escapeTechnion, "fourth@email", COMPUTER_SCIENCE, 5);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = companyAdd(escapeTechnion, "company@email", COMPUTER_SCIENCE);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = roomAdd(escapeTechnion, "company@email", 1, 4, 4, "06-12", 2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "first@email", COMPUTER_SCIENCE, 1,
			"0-08", 4);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "second@email", COMPUTER_SCIENCE, 1,
			"0-10", 4);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "third@email", COMPUTER_SCIENCE, 1,
			"0-09", 4);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperRemove(escapeTechnion, "invalid");
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = escaperRemove(escapeTechnion, "valid@!exist");
	ASSERT_TEST(result == MTM_CLIENT_EMAIL_DOES_NOT_EXIST);
	result = escaperRemove(escapeTechnion, "first@email");
	ASSERT_TEST(result == MTM_SUCCESS);
	Set set = getEscapersSet(escapeTechnion);
	setGetSize(set);
	setDestroy(set);
	List list = getOrderList(escapeTechnion);
	ASSERT_TEST(listGetSize(list) == 2);
	listDestroy(list);
	destroyEscapeTechnion(escapeTechnion);
	return true;
}
static bool testEscaperOrder() {
	MtmErrorCode result;
	EscapeTechnion escapeTechnion = createEscapeTechnion();
	ASSERT_TEST(escapeTechnion != NULL);
	result = companyAdd(escapeTechnion, "comp1@mail", COMPUTER_SCIENCE);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = companyAdd(escapeTechnion, "comp2@mail", COMPUTER_SCIENCE);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = companyAdd(escapeTechnion, "comp3@mail", MATHEMATICS);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperAdd(escapeTechnion, "esc1@mail", ELECTRICAL_ENGINEERING, 2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperAdd(escapeTechnion, "esc2@mail", COMPUTER_SCIENCE, 2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = roomAdd(escapeTechnion, "comp1@mail", 1, 24, 4, "12-19", 1);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = roomAdd(escapeTechnion, "comp2@mail", 2, 24, 4, "12-19", 1);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = roomAdd(escapeTechnion, "comp3@mail", 3, 24, 4, "12-19", 1);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "esc1mail", COMPUTER_SCIENCE, 1,
			"0-13", 4);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = escaperOrder(escapeTechnion, "esc1@mail", COMPUTER_SCIENCE, 3,
			"0-13", 4);
	ASSERT_TEST(result == MTM_ID_DOES_NOT_EXIST);
	result = escaperOrder(escapeTechnion, "esc1@mail", INVALID_INT, 1, "0-13",
			4);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = escaperOrder(escapeTechnion, "esc1@mail", UNKNOWN, 1, "0-13", 4);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = escaperOrder(escapeTechnion, "esc1@mail", UNKNOWN, 1, "0-13",
	INVALID_INT);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = escaperOrder(escapeTechnion, "esc1@mail", COMPUTER_SCIENCE, 1,
			"as-13", 23);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = escaperOrder(escapeTechnion, "esc1@mail", COMPUTER_SCIENCE, 1,
			"-23-13", 23);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);
	result = escaperOrder(escapeTechnion, "esc1@mail", UNKNOWN, 1, "0-13", 23);
	ASSERT_TEST(result == MTM_INVALID_PARAMETER);

	result = escaperOrder(escapeTechnion, "other@mail", COMPUTER_SCIENCE, 1,
			"0-13", 2);
	ASSERT_TEST(result == MTM_CLIENT_EMAIL_DOES_NOT_EXIST);
	result = escaperOrder(escapeTechnion, "esc1@mail", COMPUTER_SCIENCE, 3,
			"0-13", 2);
	ASSERT_TEST(result == MTM_ID_DOES_NOT_EXIST);
	result = escaperOrder(escapeTechnion, "esc1@mail", COMPUTER_SCIENCE, 1,
			"0-13", 2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "esc1@mail", COMPUTER_SCIENCE, 1,
			"0-13", 2);
	ASSERT_TEST(result == MTM_CLIENT_IN_ROOM);
	result = escaperOrder(escapeTechnion, "esc1@mail", COMPUTER_SCIENCE, 2,
			"0-13", 2);
	ASSERT_TEST(result == MTM_CLIENT_IN_ROOM);
	result = escaperOrder(escapeTechnion, "esc2@mail", COMPUTER_SCIENCE, 1,
			"0-13", 2);
	ASSERT_TEST(result == MTM_ROOM_NOT_AVAILABLE);
	destroyEscapeTechnion(escapeTechnion);
	return true;
}

static bool testEscaperRecommend() {
	EscapeTechnion escapeTechnion = createEscapeTechnion();
	ASSERT_TEST(
			escaperRecommend(escapeTechnion, "invalid", 4)
					== MTM_INVALID_PARAMETER);
	ASSERT_TEST(
			escaperRecommend(escapeTechnion, "valid@email", 4)
					== MTM_CLIENT_EMAIL_DOES_NOT_EXIST);
	ASSERT_TEST(
			escaperAdd(escapeTechnion, "valid@email", COMPUTER_SCIENCE, 2)
					== MTM_SUCCESS);
	ASSERT_TEST(
			escaperRecommend(escapeTechnion, "valid@email", 2)
					== MTM_NO_ROOMS_AVAILABLE);
	ASSERT_TEST(
			companyAdd(escapeTechnion, "comp1@email", ELECTRICAL_ENGINEERING)
					== MTM_SUCCESS);
	ASSERT_TEST(
			companyAdd(escapeTechnion, "comp2@email", BIOLOGY) == MTM_SUCCESS);
	ASSERT_TEST(
			roomAdd(escapeTechnion, "comp1@email", 1, 4, 3, "06-12", 5)
					== MTM_SUCCESS);
	ASSERT_TEST(
			roomAdd(escapeTechnion, "comp2@email", 2, 4, 3, "05-12", 5)
					== MTM_SUCCESS);
	MtmErrorCode result = escaperRecommend(escapeTechnion, "valid@email", 4);
	ASSERT_TEST(result == MTM_SUCCESS);
	List orders = getOrderList(escapeTechnion);
	Order order = (Order) listGetFirst(orders);
	ASSERT_TEST(getOrderRoomFaculty(order) == BIOLOGY);
	ASSERT_TEST(getOrderHour(order) == 5);
	listDestroy(orders);
	ASSERT_TEST(
			roomRemove(escapeTechnion, BIOLOGY, 2) == MTM_RESERVATION_EXISTS);
	reportDay(escapeTechnion, stdout); /////go to next day
	ASSERT_TEST(roomRemove(escapeTechnion, BIOLOGY, 2) == MTM_SUCCESS);
	ASSERT_TEST(
			roomRemove(escapeTechnion, ELECTRICAL_ENGINEERING, 1)
					== MTM_SUCCESS);
	result = roomAdd(escapeTechnion, "comp2@email", 1, 8, 7, "06-12", 4);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = roomAdd(escapeTechnion, "comp2@email", 2, 8, 7, "05-12", 4);
	ASSERT_TEST(result == MTM_SUCCESS);
	ASSERT_TEST(
			escaperRecommend(escapeTechnion, "valid@email", 4) == MTM_SUCCESS);
	List orders2 = getOrderList(escapeTechnion);
	Order order3 = (Order) listGetFirst(orders2);
	ASSERT_TEST(getOrderRoomFaculty(order3) == BIOLOGY);
	ASSERT_TEST(getOrderRoomId(order3) == 1);
	listDestroy(orders2);
//	destroyOrder(order);
	destroyEscapeTechnion(escapeTechnion);
	return true;
}

static bool testReportDay() {
	MtmErrorCode result;
	EscapeTechnion escapeTechnion = createEscapeTechnion();
	ASSERT_TEST(escapeTechnion != NULL);
	result = companyAdd(escapeTechnion, "comp1@mail", COMPUTER_SCIENCE);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = companyAdd(escapeTechnion, "comp2@mail", COMPUTER_SCIENCE);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = companyAdd(escapeTechnion, "comp3@mail", MATHEMATICS);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = roomAdd(escapeTechnion, "comp1@mail", 1, 24, 4, "12-19", 1);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = roomAdd(escapeTechnion, "comp2@mail", 2, 24, 4, "12-19", 1);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = roomAdd(escapeTechnion, "comp3@mail", 3, 24, 4, "12-19", 1);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperAdd(escapeTechnion, "esc1@mail", COMPUTER_SCIENCE, 2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperAdd(escapeTechnion, "esc2@mail", COMPUTER_SCIENCE, 2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperAdd(escapeTechnion, "esc3@mail", COMPUTER_SCIENCE, 2);
	ASSERT_TEST(result == MTM_SUCCESS);

	result = escaperOrder(escapeTechnion, "esc1@mail", COMPUTER_SCIENCE, 1,
			"0-13", 2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "esc2@mail", COMPUTER_SCIENCE, 2,
			"0-13", 2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "esc3@mail", MATHEMATICS, 3, "0-13",
			2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "esc1@mail", COMPUTER_SCIENCE, 1,
			"0-14", 2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "esc1@mail", COMPUTER_SCIENCE, 1,
			"1-16", 2);
	ASSERT_TEST(result == MTM_SUCCESS);
	reportDay(escapeTechnion, stdout);
	reportDay(escapeTechnion, stdout);
	destroyEscapeTechnion(escapeTechnion);
	return true;
}

static bool testReportBest() {
	MtmErrorCode result;
	EscapeTechnion escapeTechnion = createEscapeTechnion();
	ASSERT_TEST(escapeTechnion != NULL);
	result = companyAdd(escapeTechnion, "comp1@mail", COMPUTER_SCIENCE);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = companyAdd(escapeTechnion, "comp2@mail", BIOLOGY);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = companyAdd(escapeTechnion, "comp3@mail", MATHEMATICS);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = companyAdd(escapeTechnion, "comp4@mail", ELECTRICAL_ENGINEERING);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = roomAdd(escapeTechnion, "comp1@mail", 1, 24, 4, "12-19", 1);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = roomAdd(escapeTechnion, "comp2@mail", 2, 24, 4, "12-19", 1);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = roomAdd(escapeTechnion, "comp3@mail", 3, 24, 4, "12-19", 1);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = roomAdd(escapeTechnion, "comp4@mail", 4, 24, 4, "12-19", 1);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperAdd(escapeTechnion, "esc1@mail", MATERIALS_ENGINEERING, 2);
	ASSERT_TEST(result == MTM_SUCCESS);

	result = escaperOrder(escapeTechnion, "esc1@mail", COMPUTER_SCIENCE, 1,
			"0-13", 2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "esc1@mail", COMPUTER_SCIENCE, 1,
			"0-14", 2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "esc1@mail", COMPUTER_SCIENCE, 1,
			"0-15", 2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "esc1@mail", BIOLOGY, 2, "1-13", 2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "esc1@mail", BIOLOGY, 2, "1-14", 2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "esc1@mail", BIOLOGY, 2, "1-15", 2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "esc1@mail", BIOLOGY, 2, "1-16", 2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "esc1@mail", MATHEMATICS, 3, "2-13",
			2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "esc1@mail", MATHEMATICS, 3, "2-14",
			2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "esc1@mail", MATHEMATICS, 3, "2-15",
			2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "esc1@mail", MATHEMATICS, 3, "2-16",
			2);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = escaperOrder(escapeTechnion, "esc1@mail", COMPUTER_SCIENCE, 1,
			"3-15", 2);
	reportBest(escapeTechnion, stdout);
	reportDay(escapeTechnion, stdout);
	reportBest(escapeTechnion, stdout);
	reportDay(escapeTechnion, stdout);
	reportBest(escapeTechnion, stdout);
	reportDay(escapeTechnion, stdout);
	reportBest(escapeTechnion, stdout);
	reportDay(escapeTechnion, stdout);
	reportBest(escapeTechnion, stdout);
	reportDay(escapeTechnion, stdout);
	destroyEscapeTechnion(escapeTechnion);
	return true;
}

static bool courseTest() {
	MtmErrorCode result;
	EscapeTechnion escapeTechnion = createEscapeTechnion();
	ASSERT_TEST(escapeTechnion != NULL);
	result = companyAdd(escapeTechnion, "roomsinc@gmail.com", 13);
	ASSERT_TEST(result == MTM_SUCCESS);
	result = companyRemove(escapeTechnion,"roomsinc@gmail.com");
	ASSERT_TEST(result == MTM_SUCCESS);
//	result = roomAdd(escapeTechnion, "roomsinc@gmail.com",1,100,3,"06-18",7);
//	ASSERT_TEST(result == MTM_SUCCESS);
//	result = escaperAdd(escapeTechnion, "escmaster@gmail.com", 13,8);
//	ASSERT_TEST(result == MTM_SUCCESS);
//	result = escaperOrder(escapeTechnion, "escmaster@gmail.com",13,1,"0-10",3);
//	ASSERT_TEST(result == MTM_SUCCESS);
	destroyEscapeTechnion(escapeTechnion);
	return true;
}
int main5(int argv, char** arc) {
	RUN_TEST(testSystemCreateDestroy);
	RUN_TEST(testAddCompany);
	RUN_TEST(testRemoveCompany);
	RUN_TEST(testAddRoom);
	RUN_TEST(testRoomRemove);
	RUN_TEST(testAddEscaper);
	RUN_TEST(testEscaperRemove);
	RUN_TEST(testEscaperOrder);
	RUN_TEST(testEscaperRecommend);
	RUN_TEST(testReportDay);
	RUN_TEST(testReportBest);
	RUN_TEST(courseTest);
	return 0;
}
