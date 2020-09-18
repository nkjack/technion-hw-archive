/*
 * Escaper.c
 *
 *  Created on: May 30, 2017
 *      Author: Noam
 */

#include "escaper.h"

struct escaper {
	char* email;
	TechnionFaculty faculty_id;
	int skill_level;
//	List orders;
};

/*static functions*/
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
 * check if skill level is between 1 and 10
 * @param int skill_level to check
 * @return true if valid, false otherwise
 */
static bool checkValidSkillLevel(int skill_level) {
	return (skill_level > 0 && skill_level <= 10);
}
/**
 * check if id of faculty is valid. according the mtm_ex3.h standards.
 */
static bool validFaculty(TechnionFaculty faculty) {
	return (faculty < UNKNOWN && faculty >= CIVIL_ENGINEERING);
}
/**
 * IMPLEMENTING HEADER
 */
Escaper createEscaper(char* email, TechnionFaculty faculty_id, int skill_level,
		EscaperResult *result) {
	assert(result);
	if (!email) {
		*result = ESCAPER_NULL_PARAMETER;
		return NULL;
	}
	if ((!ifValidEmail(email)) || (!checkValidSkillLevel(skill_level))
			|| !(validFaculty(faculty_id))) {
		*result = ESCAPER_INVALID_PARAMETER;
		return NULL;
	}
	Escaper escaper = malloc(sizeof(*escaper));
	if (escaper == NULL) {
		*result = ESCAPER_OUT_OF_MEMORY;
		return NULL;
	}
	escaper->email = stringDuplicate(email);
	if (!escaper->email) {
		*result = ESCAPER_OUT_OF_MEMORY;
		free(escaper);
		return NULL;
	}
	escaper->faculty_id = faculty_id;
	escaper->skill_level = skill_level;
	*result = ESCAPER_SUCCESS;
	return escaper;
}

void destroyEscaper(Escaper escaper) {
	if (escaper != NULL) {
		free(escaper->email);
		free(escaper);
	}
}

Escaper escaperCopy(Escaper escaper) {
	if (escaper == NULL) {
		return NULL;
	}
	EscaperResult result;
	Escaper copy_escaper = createEscaper(escaper->email, escaper->faculty_id,
			escaper->skill_level, &result);
	return copy_escaper;
}

SetElement escaperCopySetFunction(SetElement escaper) {
	assert(escaper != NULL);
	return escaperCopy((Escaper) escaper);;
}

int escaperCompare(SetElement escaper_1, SetElement escaper_2) {
	assert(escaper_1 && escaper_2);
	return strcmp(((Escaper) escaper_1)->email, ((Escaper) escaper_2)->email);
}

char* getEscaperEmail(Escaper escaper) {
	if (!escaper) {
		return NULL;
	}
	return escaper->email;
}

void freeEscaperSetFunction(SetElement element) {
	destroyEscaper((Escaper) element);
}

int getEscaperSkill(Escaper escaper) {
	assert(escaper != NULL);
	return escaper->skill_level;
}

TechnionFaculty getEscaperFaculty(Escaper escaper) {
	assert(escaper != NULL);
	return escaper->faculty_id;
}
