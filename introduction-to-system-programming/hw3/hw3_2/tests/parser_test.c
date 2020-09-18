/*
 * unit_test_parser.c
 *
 *  Created on: Jun 14, 2017
 *      Author: Noam
 */

#include "test_utilities.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../parser.h"
#include "../list.h"

#define INVALID_INT -1
#define VALID_INT 1

static bool testAddCompany() {
	ParseResult result;
	char line[] = "company add valid@mail 2";
	List list1 = readCommand(line, &result);
	ASSERT_TEST(result == PARSE_ADD_COMPANY);
	ASSERT_TEST(listGetSize(list1) == 4);
	listGetFirst(list1);
	listGetNext(list1);
	char* temp = (char*) listGetNext(list1);
	ASSERT_TEST(strcmp(temp, "valid@mail") == 0);
	listDestroy(list1);
	return true;
}

static bool testRemoveCompany() {
	ParseResult result;
	char line[] = "company remove valid@mail";
	List list1 = readCommand(line, &result);
	ASSERT_TEST(result == PARSE_COMPANY_REMOVE);
	ASSERT_TEST(listGetSize(list1) == 3);
	listGetFirst(list1);
	listGetNext(list1);
	char* temp = (char*) listGetNext(list1);
	ASSERT_TEST(strcmp(temp, "valid@mail") == 0);
	listDestroy(list1);
	return true;
}

static bool testAddRoom() {
	ParseResult result;
	char line[] = "  	room add valid@mail 	12 4   4 12-19 	3";
	List list1 = readCommand(line, &result);
	ASSERT_TEST(result == PARSE_ADD_ROOM);
	ASSERT_TEST(listGetSize(list1) == 8);
	listDestroy(list1);
	return true;
}

static bool testRemoveRoom() {
	ParseResult result;
	char line[] = "  	room remove 	12  3";
	List list1 = readCommand(line, &result);
	ASSERT_TEST(result == PARSE_ROOM_REMOVE);
	ASSERT_TEST(listGetSize(list1) == 4);
	listDestroy(list1);
	return true;
}

static bool testEscaperAdd() {
	ParseResult result;
	char line[] = "  	escaper add valid@mail	12  3";
	List list1 = readCommand(line, &result);
	ASSERT_TEST(result == PARSE_ESCAPER_ADD);
	ASSERT_TEST(listGetSize(list1) == 5);
	listDestroy(list1);
	char line2[] = "      ";
	List list2 = readCommand(line2, &result);
	ASSERT_TEST(result == PARSE_EMPTY_OR_COMMENT);
	ASSERT_TEST(list2 == NULL);
	return true;
}

static bool testEscaperRemove() {
	ParseResult result;
	char line[] = "  	escaper remove   valid@mail	  ";
	List list1 = readCommand(line, &result);
	ASSERT_TEST(result == PARSE_ESCAPER_REMOVE);
	ASSERT_TEST(listGetSize(list1) == 3);
	listDestroy(list1);
	char line2[] = "#      ";
	List list2 = readCommand(line2, &result);
	ASSERT_TEST(result == PARSE_EMPTY_OR_COMMENT);
	ASSERT_TEST(list2 == NULL);
	return true;
}

static bool testEscaperOrder() {
	ParseResult result;
	char line[] = "  	escaper order   valid@mail	12 3 123-22 55  ";
	List list1 = readCommand(line, &result);
	ASSERT_TEST(result == PARSE_ESCAPER_ORDER);
	ASSERT_TEST(listGetSize(list1) == 7);
	listDestroy(list1);
	return true;
}

static bool testEscaperRecmmened() {
	ParseResult result;
	char line[] = "  	escaper recommend    valid@mail	12   ";
	List list1 = readCommand(line, &result);
	ASSERT_TEST(result == PARSE_ESCAPER_RECOMEND);
	ASSERT_TEST(listGetSize(list1) == 4);
	listDestroy(list1);
	return true;
}

static bool testReportDay() {
	ParseResult result;
	char line[] = "  	report day   ";
	List list1 = readCommand(line, &result);
	ASSERT_TEST(result == PARSE_REPORT_DAY);
	ASSERT_TEST(listGetSize(list1) == 2);
	listDestroy(list1);
	return true;
}

static bool testReportBest() {
	ParseResult result;
	char line[] = "  	report best   ";
	List list1 = readCommand(line, &result);
	ASSERT_TEST(result == PARSE_REPORT_BEST);
	ASSERT_TEST(listGetSize(list1) == 2);
	listDestroy(list1);
	return true;
}

static bool testNoCommand() {
	ParseResult result;
	char line[] = "  	report best  123 asd ";
	List list1 = readCommand(line, &result);
	ASSERT_TEST(result == PARSE_NOT_COMMAND);
	ASSERT_TEST(list1 == NULL);
	return true;
}

int main2(int argv, char** arc) {
	RUN_TEST(testAddCompany);
	RUN_TEST(testRemoveCompany);
	RUN_TEST(testAddRoom);
	RUN_TEST(testRemoveRoom);
	RUN_TEST(testEscaperAdd);
	RUN_TEST(testEscaperRemove);
	RUN_TEST(testEscaperOrder);
	RUN_TEST(testEscaperRecmmened);
	RUN_TEST(testReportDay);
	RUN_TEST(testReportBest);
	RUN_TEST(testNoCommand);

	return 0;
}
