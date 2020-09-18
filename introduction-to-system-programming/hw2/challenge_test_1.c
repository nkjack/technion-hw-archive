/*
 * challenge_test_1.c
 *
 *  Created on: May 6, 2017
 *      Author: Noam
 */

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#include "challenge.h"

#define ASSERT(test_number, test_condition)  \
   if (!(test_condition)) {printf("\nTEST %s FAILED", test_number); } \
   else printf("\nTEST %s OK", test_number);

int goon(int argc, char **argv) {
	Challenge *ch = malloc(sizeof(Challenge));
	ASSERT("1.1", ch != NULL)
	Result r = OK;

	r = init_challenge(ch, 2, "noam_test", Medium);

	ASSERT("1.2", r == OK);

	return 0;
}

