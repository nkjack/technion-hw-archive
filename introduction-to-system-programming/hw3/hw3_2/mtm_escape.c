/*
 * MtmEscape.c
 *
 *  Created on: Jun 11, 2017
 *      Author: Noam
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mtm_ex3.h"
#include "parser.h"
#include "escape_technion.h"

#define RETURN_VALUE 0

/**
 * this function get a list of commands that fits the company add command
 * and execute companyAdd function in escape technion according to the params
 * in the list.
 *
 * @param escapeTechnion the system
 * @param list list of strings with the commands
 *
 * @return MtmErrorCode according to companyAdd function
 */
static MtmErrorCode addCompanyExecute(EscapeTechnion escapeTechnion, List list) {
	int pos = 0;
	char* email;
	int faculty;
	LIST_FOREACH(char*, str, list)
	{
		if (pos == 2) {
			email = str;
		} else if (pos == 3) {
			faculty = atoi(str);
		}
		pos += 1;
	}
	return (companyAdd(escapeTechnion, email, faculty));
}
/**
 * this function get a list of commands that fits the company remove command
 * and execute companyRemove function in escape technion according to the params
 * in the list.
 *
 * @param escapeTechnion the system
 * @param list list of strings with the commands
 *
 * @return MtmErrorCode according to companyRemove function
 */
static MtmErrorCode removeCompanyExecute(EscapeTechnion escapeTechnion,
		List list) {
	int pos = 0;
	char* email;
	LIST_FOREACH(char*,str,list)
	{
		if (pos == 2) {
			email = str;
		}
		pos++;
	}
	return companyRemove(escapeTechnion, email);
}
/**
 * this function get a list of commands that fits the room add command
 * and execute roomAdd function in escape technion according to the params
 * in the list.
 *
 * @param escapeTechnion the system
 * @param list list of strings with the commands
 *
 * @return MtmErrorCode according to roomAdd function
 */
static MtmErrorCode addRoomExecute(EscapeTechnion escapeTechnion, List list) {
	int pos = 0;
	char* email;
	int id;
	int price;
	int num_ppl;
	char* working_hrs;
	int difficulty;
	LIST_FOREACH(char*,param,list)
	{
		switch (pos) {
		case 0:
			break;
		case 1:
			break;
		case 2:
			email = param;
			break;
		case 3:
			id = atoi(param);
			break;
		case 4:
			price = atoi(param);
			break;
		case 5:
			num_ppl = atoi(param);
			break;
		case 6:
			working_hrs = param;
			break;
		case 7:
			difficulty = atoi(param);
			break;
		}
		pos++;
	}
	return roomAdd(escapeTechnion, email, id, price, num_ppl, working_hrs,
			difficulty);
}
/**
 * this function get a list of commands that fits the room remove command
 * and execute roomRemove function in escape technion according to the params
 * in the list.
 *
 * @param escapeTechnion the system
 * @param list list of strings with the commands
 *
 * @return MtmErrorCode according to roomRemove function
 */
static MtmErrorCode removeRoomExecute(EscapeTechnion escapeTechnion, List list) {
	int pos = 0;
	int faculty;
	int id;
	LIST_FOREACH(char*,str,list)
	{
		if (pos == 2) {
			faculty = atoi(str);
		}
		if (pos == 3) {
			id = atoi(str);
		}
		pos++;
	}
	return roomRemove(escapeTechnion, faculty, id);

}
/**
 * this function get a list of commands that fits the remove escaper command
 * and execute escaperRemove function in escape technion according to the params
 * in the list.
 *
 * @param escapeTechnion the system
 * @param list list of strings with the commands
 *
 * @return MtmErrorCode according to escaperRemove function
 */
static MtmErrorCode removeEscaperExecute(EscapeTechnion escapeTechnion,
		List list) {
	char* email;
	int pos = 0;
	LIST_FOREACH(char*,str,list)
	{
		if (pos == 2) {
			email = str;
		}
		pos++;
	}
	MtmErrorCode result =  escaperRemove(escapeTechnion, email);
	return result;
}

/**
 * this function get a list of commands that fits the escaper order command
 * and execute escaperOrder function in escape technion according to the params
 * in the list.
 *
 * @param escapeTechnion the system
 * @param list list of strings with the commands
 *
 * @return MtmErrorCode according to escaperOrder function
 */
static MtmErrorCode escaperOrderExecute(EscapeTechnion escapeTechnion,
		List list) {
	int pos = 0;
	char* email;
	int id;
	int faculty;
	int num_ppl;
	char* time;
	LIST_FOREACH(char*,str,list)
	{
		if (pos == 2) {
			email = str;
		}
		if (pos == 3) {
			faculty = atoi(str);
		}
		if (pos == 4) {
			id = atoi(str);
		}
		if (pos == 5) {
			time = str;
		}
		if (pos == 6) {
			num_ppl = atoi(str);
		}
		pos++;
	}
	return escaperOrder(escapeTechnion, email, faculty, id, time, num_ppl);

}
/**
 * this function get a list of commands that fits the escaper add command
 * and execute escaperAdd function in escape technion according to the params
 * in the list.
 *
 * @param escapeTechnion the system
 * @param list list of strings with the commands
 *
 * @return MtmErrorCode according to escaperAdd function
 */
static MtmErrorCode escaperAddExecute(EscapeTechnion escapeTechnion, List list) {
	int pos = 0;
	char *email;
	int faculty;
	int skl;
	LIST_FOREACH(char*,param,list)
	{
		if (pos == 2) {
			email = param;
		} else if (pos == 3) {
			faculty = atoi(param);
		} else if (pos == 4) {
			skl = atoi(param);
		}
		pos++;
	}
	return escaperAdd(escapeTechnion, email, faculty, skl);
}
/**
 * this function get a list of commands that fits the escaper recommend command
 * and execute escaperRecommend function in escape technion according to the params
 * in the list.
 *
 * @param escapeTechnion the system
 * @param list list of strings with the commands
 *
 * @return MtmErrorCode according to escaperRecommend function
 */
static MtmErrorCode escaperReccomendExecute(EscapeTechnion escapeTechnion,
		List list) {
	int pos = 0;
	char *email;
	int num_ppl;
	LIST_FOREACH(char*,param,list)
	{
		if (pos == 2) {
			email = param;
		}
		if (pos == 3) {
			num_ppl = atoi(param);
		}
		pos++;
	}
	return escaperRecommend(escapeTechnion, email, num_ppl);
}

/**
 * this function get a list of commands that fits the report day command
 * and execute reportDay function in escape technion according to the params
 * in the list.
 *
 * @param escapeTechnion the system
 * @param list list of strings with the commands
 *
 * @return MtmErrorCode according to reportDay function
 */
static MtmErrorCode reportDayExecute(EscapeTechnion escapeTechnion, List list,
		FILE* output) {
	return reportDay(escapeTechnion, output);
}
/**
 * this function get a list of commands that fits the report best command
 * and execute reportBest function in escape technion according to the params
 * in the list.
 *
 * @param escapeTechnion the system
 * @param list list of strings with the commands
 *
 * @return MtmErrorCode according to reportBest function
 */
static MtmErrorCode reportBestExecute(EscapeTechnion escapeTechnion, List list,
		FILE* output) {
	return reportBest(escapeTechnion, output);
}
/**
 * this function handle the the ParserResult by calling the right function
 * that equals to the ParserResult.
 */
static MtmErrorCode mainExecuteCommand(EscapeTechnion system, List list,
		ParseResult result, FILE* input, FILE* output) {
	switch (result) {
	case PARSE_ADD_COMPANY:
		return addCompanyExecute(system, list);
	case PARSE_COMPANY_REMOVE:
		return removeCompanyExecute(system, list);
	case PARSE_ADD_ROOM:
		return addRoomExecute(system, list);
	case PARSE_ROOM_REMOVE:
		return removeRoomExecute(system, list);
	case PARSE_ESCAPER_ADD:
		return escaperAddExecute(system, list);
	case PARSE_ESCAPER_REMOVE:
		return removeEscaperExecute(system, list);
	case PARSE_ESCAPER_ORDER:
		return escaperOrderExecute(system, list);
	case PARSE_ESCAPER_RECOMEND:
		return escaperReccomendExecute(system, list);
	case PARSE_REPORT_DAY:
		return reportDayExecute(system, list, output);
	case PARSE_REPORT_BEST:
		return reportBestExecute(system, list, output);
	default:
		return MTM_OUT_OF_MEMORY;
	}
}

/**
 * initialize Input File according to the standrd of the HW3
 */
static FILE* initInputFile(int argc, char** argv, MtmErrorCode *result) {
	if (argc == 1) {
		return stdin;
	} else if (argc == 3) {
		if (strcmp(argv[1], "-o") == 0) {
			if (strcmp(argv[2], "-i") == 0) {
				*result = MTM_INVALID_COMMAND_LINE_PARAMETERS;
				return NULL;
			}
			*result = MTM_SUCCESS;
			return stdin;
		} else if (strcmp(argv[1], "-i") == 0) {
			if (strcmp(argv[2], "-o") == 0) {
				*result = MTM_INVALID_COMMAND_LINE_PARAMETERS;
				return NULL;
			}
			*result = MTM_SUCCESS;
			return fopen(argv[2], "r");
		}
	} else if (argc == 5) {
		if ((strcmp(argv[1], "-o") == 0) && (strcmp(argv[3], "-i") == 0)) {
			*result = MTM_SUCCESS;
			return fopen(argv[4], "r");
		} else if ((strcmp(argv[1], "-i") == 0)
				&& (strcmp(argv[3], "-o") == 0)) {
			*result = MTM_SUCCESS;
			return fopen(argv[2], "r");
		}
	}
	*result = MTM_INVALID_COMMAND_LINE_PARAMETERS;
	return NULL;
}
/**
 * initialize Input File according to the standrd of the HW3
 */
static FILE* initOutputFile(int argc, char** argv, MtmErrorCode *result) {
	if (argc == 1) {
		return stdout;
	} else if (argc == 3) {
		if (strcmp(argv[1], "-i") == 0) {
			if (strcmp(argv[2], "-o") == 0) {
				*result = MTM_INVALID_COMMAND_LINE_PARAMETERS;
				return NULL;
			}
			*result = MTM_SUCCESS;
			return stdout;
		} else if (strcmp(argv[1], "-o") == 0) {
			if (strcmp(argv[2], "-i") == 0) {
				*result = MTM_INVALID_COMMAND_LINE_PARAMETERS;
				return NULL;
			}
			*result = MTM_SUCCESS;
			return fopen(argv[2], "w");
		}
	} else if (argc == 5) {
		if ((strcmp(argv[1], "-o") == 0) && (strcmp(argv[3], "-i") == 0)) {
			*result = MTM_SUCCESS;
			return fopen(argv[2], "w");
		} else if ((strcmp(argv[1], "-i") == 0)
				&& (strcmp(argv[3], "-o") == 0)) {
			*result = MTM_SUCCESS;
			return fopen(argv[4], "w");
		}
	}
	*result = MTM_INVALID_COMMAND_LINE_PARAMETERS;
	return NULL;
}

/**
 * this function close The input and output channels and destroy the
 * escapeTechnion system
 */
static void closeChannels(EscapeTechnion system, FILE* input, FILE* output) {
	if (input != stdin) {
		fclose(input);
	}
	if (input != stdout) {
		fclose(output);
	}
	destroyEscapeTechnion(system);
}
/**
 * this function get input and output FILE*, read the input, means the command
 * of the user to the the EscaperTechnion, parse the commands, and execute
 * the function of Escape technion with that fits the command.
 *
 *
 */
static int startParser(EscapeTechnion system, FILE* input, FILE* output) {
	assert(system != NULL);
	char buffer[MAX_LEN];
	while (fgets(buffer, MAX_LEN, input) != NULL) {
		ParseResult result;
		List list = readCommand(buffer, &result);
		if (result == PARSE_EMPTY_OR_COMMENT){
			continue;
		}
		else if (result != PARSE_NOT_COMMAND) {
			MtmErrorCode mtm_error_code = mainExecuteCommand(system, list,
					result, input, output);
			listDestroy(list);
			if (mtm_error_code != MTM_SUCCESS) {
				mtmPrintErrorMessage(stderr, mtm_error_code);
			}
		}

	}
	closeChannels(system, input, output);
	return RETURN_VALUE;
}

int main(int argc, char** argv) {
	 setvbuf (stdout, NULL, _IONBF, 0);
	MtmErrorCode result = MTM_SUCCESS;
	EscapeTechnion system = createEscapeTechnion();
	if (!system) {
		mtmPrintErrorMessage(stderr, MTM_OUT_OF_MEMORY);
		return RETURN_VALUE;
	}
	FILE* input = initInputFile(argc, argv, &result);
	if (result == MTM_INVALID_COMMAND_LINE_PARAMETERS) {
		mtmPrintErrorMessage(stderr, MTM_INVALID_COMMAND_LINE_PARAMETERS);
		destroyEscapeTechnion(system);
		return RETURN_VALUE;

	} else if (!input) {
		mtmPrintErrorMessage(stderr, MTM_CANNOT_OPEN_FILE);
		destroyEscapeTechnion(system);
		return RETURN_VALUE;
	}

	FILE* output = initOutputFile(argc, argv, &result);
	if (result == MTM_INVALID_COMMAND_LINE_PARAMETERS) {
		fclose(input);
		mtmPrintErrorMessage(stderr, MTM_INVALID_COMMAND_LINE_PARAMETERS);
		destroyEscapeTechnion(system);
		return RETURN_VALUE;
	} else if (!output) {
		fclose(input);
		mtmPrintErrorMessage(stderr, MTM_CANNOT_OPEN_FILE);
		destroyEscapeTechnion(system);
		return RETURN_VALUE;
	}
	return startParser(system, input, output);
}

