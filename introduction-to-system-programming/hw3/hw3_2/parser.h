/*
 * parser.h
 *
 *  Created on: Jun 13, 2017
 *      Author: Noam
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "mtm_ex3.h"

/**
 * This type defines all errors for the order.
 */
typedef enum {
	PARSE_ADD_COMPANY,
	PARSE_COMPANY_REMOVE,
	PARSE_ADD_ROOM,
	PARSE_ROOM_REMOVE,
	PARSE_ESCAPER_ADD,
	PARSE_ESCAPER_REMOVE,
	PARSE_ESCAPER_ORDER,
	PARSE_ESCAPER_RECOMEND,
	PARSE_REPORT_DAY,
	PARSE_REPORT_BEST,
	PARSE_EMPTY_OR_COMMENT,
	PARSE_OUT_OF_MEMORY, // You should exit program after this error
	PARSE_SUCCESS,
	PARSE_NOT_COMMAND,
} ParseResult;

/**
 * this function get a char* line "command from the user of mtm_escape".
 * with the given the function parse each word into a list of strings
 * that together represent the entire commant
 *
 * @param char* line - the command
 * @param ParseResult* - the output result according to the command validity
 *
 * @return - List of char* that contains all the command.
 * if the command is empty or a comment that it returns NULL
 */
List readCommand(char* line, ParseResult *result);

#endif /* PARSER_H_ */
