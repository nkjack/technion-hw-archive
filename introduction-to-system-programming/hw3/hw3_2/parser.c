/*
 * parser.c
 *
 *  Created on: Jun 11, 2017
 *      Author: Noam
 */

#include "parser.h"
#define DELIMITER " \t\n"

static void freeString(void* str) {
	free(str);
}
static void* copyString(void* str) {
	char* newStr = malloc(sizeof(*newStr) * (strlen((char*) str) + 1));
	strcpy(newStr, (char*) str);
	return newStr;
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
 * this function handle a list of string that represnt an entire mtm_escape
 * command.
 *
 * according to the first string - main command and second string - second
 * command, the function return the List that represent the command
 * and give for outPut the right ParseResult.
 *
 * if list doesn't represnt a valid command, than the function destroy the
 * list and return NULL also the ParseResult will be PARSE_NOT_COMMAND
 */
static List handleListCommand(List list, ParseResult *result) {
	char* main_command = (char*) listGetFirst(list);
	char* sub_command = (char*) listGetNext(list);
	if (strcmp(main_command, "company") == 0) {
		if (strcmp(sub_command, "add") == 0) {
			if (listGetSize(list) == 4) {
				*result = PARSE_ADD_COMPANY;
				return list;
			}
		} else if (strcmp(sub_command, "remove") == 0) {
			if (listGetSize(list) == 3) {
				*result = PARSE_COMPANY_REMOVE;
				return list;
			}
		}
	} else if (strcmp(main_command, "room") == 0) {
		if (strcmp(sub_command, "add") == 0) {
			if (listGetSize(list) == 8) {
				*result = PARSE_ADD_ROOM;
				return list;
			}
		} else if (strcmp(sub_command, "remove") == 0) {
			if (listGetSize(list) == 4) {
				*result = PARSE_ROOM_REMOVE;
				return list;
			}
		}
	} else if (strcmp(main_command, "escaper") == 0) {
		if (strcmp(sub_command, "add") == 0) {
			if (listGetSize(list) == 5) {
				*result = PARSE_ESCAPER_ADD;
				return list;
			}
		} else if (strcmp(sub_command, "remove") == 0) {
			if (listGetSize(list) == 3) {
				*result = PARSE_ESCAPER_REMOVE;
				return list;
			}
		} else if (strcmp(sub_command, "order") == 0) {
			if (listGetSize(list) == 7) {
				*result = PARSE_ESCAPER_ORDER;
				return list;
			}
		} else if (strcmp(sub_command, "recommend") == 0) {
			if (listGetSize(list) == 4) {
				*result = PARSE_ESCAPER_RECOMEND;
				return list;
			}
		}
	} else if (strcmp(main_command, "report") == 0) {
		if (strcmp(sub_command, "day") == 0) {
			if (listGetSize(list) == 2) {
				*result = PARSE_REPORT_DAY;
				return list;
			}
		} else if (strcmp(sub_command, "best") == 0) {
			if (listGetSize(list) == 2) {
				*result = PARSE_REPORT_BEST;
				return list;
			}
		}
	}
	*result = PARSE_NOT_COMMAND;
	listDestroy(list);
	return NULL;
}

/**
 * IMPLEMENT HEADER
 */
List readCommand(char* line, ParseResult *result) {
	char * pch;
	pch = strtok(line, DELIMITER);
	List arg_list = listCreate(copyString, freeString);
	if (!arg_list) {
		*result = PARSE_OUT_OF_MEMORY;
		return NULL;
	}
	if (pch == NULL) {
		listDestroy(arg_list);
		*result = PARSE_EMPTY_OR_COMMENT; // empty command
		return NULL;
	}
	while (pch != NULL) {
		char* strcopy = stringDuplicate(pch);
		if (!strcopy) {
			listDestroy(arg_list);
			*result = PARSE_OUT_OF_MEMORY;
			return NULL;
		}
		if (listInsertLast(arg_list, strcopy) != LIST_SUCCESS) {
			free(strcopy);
			listDestroy(arg_list);
			*result = PARSE_OUT_OF_MEMORY;
			return NULL;
		}
		free(strcopy);
		pch = strtok(NULL, DELIMITER);
	}
	if (listGetSize(arg_list) == 0
			|| ((char*) listGetFirst(arg_list))[0] == '#') {
		listDestroy(arg_list);
		*result = PARSE_EMPTY_OR_COMMENT;
		return NULL;
	}
	return handleListCommand(arg_list, result);
}

