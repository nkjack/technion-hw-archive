/*
 * unit_test_escaper.c
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
#include "../escaper.h"

#define INVALID_INT -1
#define VALID_INT 1

static bool testEscaperCreate() {
	EscaperResult result;
	Escaper escaper = createEscaper("valid@mail", COMPUTER_SCIENCE, 1, &result);
	ASSERT_TEST(escaper != NULL);
	ASSERT_TEST(result == ESCAPER_SUCCESS);
	destroyEscaper(escaper);
	escaper = createEscaper(NULL, COMPUTER_SCIENCE, 1, &result);
	ASSERT_TEST(result == ESCAPER_NULL_PARAMETER);
	escaper = createEscaper("validmail", COMPUTER_SCIENCE, 1, &result);
	ASSERT_TEST(result == ESCAPER_INVALID_PARAMETER);
	escaper = createEscaper("valid@mail", INVALID_INT, 1, &result);
	ASSERT_TEST(result == ESCAPER_INVALID_PARAMETER);
	escaper = createEscaper("valid@mail", COMPUTER_SCIENCE, 0, &result);
	ASSERT_TEST(result == ESCAPER_INVALID_PARAMETER);
	escaper = createEscaper("valid@mail", COMPUTER_SCIENCE, 11, &result);
	ASSERT_TEST(result == ESCAPER_INVALID_PARAMETER);
	destroyEscaper(escaper);
	return true;
}

static bool testRoomDestroy() {
	EscaperResult result;
	Escaper escaper = createEscaper("valid@mail", COMPUTER_SCIENCE, 1, &result);
	ASSERT_TEST(escaper != NULL);
	ASSERT_TEST(result == ESCAPER_SUCCESS);
	destroyEscaper(escaper);
	return true;
}

static bool testRoomCopyAndCompare() {
	EscaperResult result;
	Escaper escaper = createEscaper("valid@mail", COMPUTER_SCIENCE, 1, &result);
	ASSERT_TEST(escaper != NULL);
	ASSERT_TEST(result == ESCAPER_SUCCESS);
	Escaper escaper1 = escaperCopy(NULL);
	ASSERT_TEST(escaper1 == NULL);
	escaper1 = escaperCopy(escaper);
	ASSERT_TEST(escaper1 != NULL);
	ASSERT_TEST(escaperCompare(escaper, escaper1) == 0);
	destroyEscaper(escaper);
	escaper = createEscaper("valid_diff@mail", COMPUTER_SCIENCE, 1, &result);
	ASSERT_TEST(escaperCompare(escaper, escaper1) != 0);
	destroyEscaper(escaper);
	destroyEscaper(escaper1);
	return true;
}

static bool testEscaperGets() {
	EscaperResult result;
	Escaper escaper = createEscaper("valid@mail", COMPUTER_SCIENCE, 1, &result);
	ASSERT_TEST(escaper != NULL);
	ASSERT_TEST(result == ESCAPER_SUCCESS);
	ASSERT_TEST(strcmp(getEscaperEmail(escaper), "valid@mail") == 0);
	ASSERT_TEST(getEscaperFaculty(escaper) == COMPUTER_SCIENCE);
	ASSERT_TEST(getEscaperSkill(escaper) == 1);
	destroyEscaper(escaper);
	return true;
}
int main4(int argv, char** arc) {
	RUN_TEST(testEscaperCreate);
	RUN_TEST(testRoomDestroy);
	RUN_TEST(testRoomCopyAndCompare);
	RUN_TEST(testEscaperGets);
	return 0;
}
