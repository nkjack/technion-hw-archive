/*
 * Escaper.h
 *
 *  Created on: May 30, 2017
 *      Author: Noam
 */

#ifndef ESCAPER_H_
#define ESCAPER_H_

#include "order.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "mtm_ex3.h"
#include "list.h"
#include "set.h"


typedef struct escaper *Escaper;

/**
 * This type defines all errors for the escaper.
 */
typedef enum {
	ESCAPER_OUT_OF_MEMORY, // You should exit program after this error
	ESCAPER_NULL_PARAMETER,
	ESCAPER_INVALID_PARAMETER,
	ESCAPER_SUCCESS,
} EscaperResult;

/**
 * create Escaper, take email, faculty and skill level for input and return
 * the Escaper struct.
 *
 * @param email the email of the user
 * @param faculty_id the TechnionFaculty enum from mtm_ex3.h
 * @param skill_level the skill level of the user, number from 1 to 10.
 *
 * @return Escaper with those sets of variables
 */
Escaper createEscaper(char* email, TechnionFaculty faculty_id, int skill_level,
		EscaperResult *result);

/**
 * destroy the escaper, free all necessary memory
 *
 * @param escaper to free
 * @return void
 */
void destroyEscaper(Escaper escaper);

/**
 * free Escaper function for implemnting Set. using the destroyEscaper function.
 */
void freeEscaperSetFunction(SetElement element);

/**
 * copy escaper. create a new Escaper with the same values as the Escaper from
 * the input. this function use the createEscaper function to create the
 * new Escaper.
 *
 * @param escaper the object to copy the values from
 * @return escaper with the same values as the inputed, or NULL if some memory
 * allocations happened.
 */
Escaper escaperCopy(Escaper escaper);

/**
 * copy escaper for implementing Set. using the escaperCopy function.
 */
SetElement escaperCopySetFunction(SetElement escaper);

/**
 * This function use the strcmp from the stdlib library. It uses the function
 * on the emails of the escaper. Means, it compares the emails of the first
 * escaper to the email of the second one.
 *
 * @param escaper_1 first escaper
 * @param escaper_2 second escaper
 *
 * @return int according to the strcmp function.
 */
int escaperCompare(SetElement escaper_1, SetElement escaper_2);

/**
 * get the email of a escaper from the struct.
 *
 * @param escaper struct
 * @return NULL if parameter is wrong or problem with memory allocations,
 * the copy of the escaper's email if otherwise.
 */
char* getEscaperEmail(Escaper escaper);

/**
 * This function get Escaper object for input and return its skill level.
 *
 * @param Escaper
 * @return int, the escaper skill level.
 */
int getEscaperSkill(Escaper escaper);

/**
 * This function get Escaper object for input and return the faculty he
 * belongs to.
 *
 * @param Escaper
 * @return TechnionFaculty, the faculty id that the escaper belongs to.
 */
TechnionFaculty getEscaperFaculty(Escaper escaper);

#endif /* ESCAPER_H_ */
