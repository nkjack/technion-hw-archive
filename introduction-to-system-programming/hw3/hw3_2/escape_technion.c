/*
 * EscapeTechnion.c
 *
 *  Created on: May 30, 2017
 *      Author: Noam
 */

#include "escape_technion.h"
#define REGULAR_FUNC_CONST -1
#define FIRST_PLACE_ARR 0
#define INVALID_INT -1

struct escape_technion {
	Set companies;
	Set escapers;
	List orders;
	int* faculties_profit; // size of UNKNOWN
	int escapeTechnion_day;
};

/** STATIC FUNCTIONS **/
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
 * handle company result. get CompanyResult enum for input and convert it to a
 * MtmErrorCode enum.
 *
 * @param CompanyResult, the result to parse.
 * @return MtmErrorCode, the result that equivalent to the inputed.
 */
static MtmErrorCode handleCompanyResult(CompanyResult result) {
	MtmErrorCode return_result;
	assert(result != COMPANY_DEFAULT);
	switch (result) {
	case COMPANY_OUT_OF_MEMORY:
		return_result = MTM_OUT_OF_MEMORY;
		break;
	case COMPANY_NULL_PARAMETER:
		return_result = MTM_NULL_PARAMETER;
		break;
	case COMPANY_INVALID_PARAMETER:
		return_result = MTM_INVALID_PARAMETER;
		break;
	case COMPANY_ROOM_ALREADY_EXIST:
		return_result = MTM_ID_ALREADY_EXIST;
		break;
	case COMPANY_ROOM_DOES_NOT_EXIST:
		return_result = MTM_ID_DOES_NOT_EXIST;
		break;
	case COMPANY_ROOM_NOT_AVAILABLE:
		return_result = MTM_ROOM_NOT_AVAILABLE;
		break;
	default:
		return_result = MTM_SUCCESS;
		break;
	}
	return return_result;
}

/**
 * handle room result. get RoomResult enum for input and convert it to a
 * MtmErrorCode enum.
 *
 * @param RoomResult, the result to parse.
 * @return MtmErrorCode, the result that equivalent to the inputed.
 */
static MtmErrorCode handleRoomResult(RoomResult result) {
	MtmErrorCode return_result;
	assert(result != ROOM_DEFAULT);
	switch (result) {
	case ROOM_OUT_OF_MEMORY:
		return_result = MTM_OUT_OF_MEMORY;
		break;
	case ROOM_NULL_PARAMETER:
		return_result = MTM_NULL_PARAMETER;
		break;
	case ROOM_INVALID_PARAMETER:
		return_result = MTM_INVALID_PARAMETER;
		break;
	case ROOM_SUCCESS:
		return_result = MTM_SUCCESS;
		break;
	case ROOM_NOT_AVAILABLE:
		return_result = MTM_ROOM_NOT_AVAILABLE;
		break;
	case ROOM_DEFAULT:
		return_result = MTM_SUCCESS;
		break;
	}
	return return_result;
}

/**
 * handle EscaperResult. get EscaperResult enum for input and convert it to a
 * MtmErrorCode enum.
 *
 * @param EscaperResult, the result to parse.
 * @return MtmErrorCode, the result that equivalent to the inputed.
 */
static MtmErrorCode handleEscaperResult(EscaperResult result) {
	MtmErrorCode return_result;
	switch (result) {
	case ESCAPER_OUT_OF_MEMORY:
		return_result = MTM_OUT_OF_MEMORY;
		break;
	case ESCAPER_NULL_PARAMETER:
		return_result = MTM_NULL_PARAMETER;
		break;
	case ESCAPER_INVALID_PARAMETER:
		return_result = MTM_INVALID_PARAMETER;
		break;
	case ESCAPER_SUCCESS:
		return_result = MTM_SUCCESS;
		break;
	}
	return return_result;
}
/**
 * handle OrderResult. get OrderResult enum for input and convert it to a
 * MtmErrorCode enum.
 *
 * @param OrderResult, the result to parse.
 * @return MtmErrorCode, the result that equivalent to the inputed.
 */
static MtmErrorCode handleOrderResult(OrderResult result) {
	MtmErrorCode return_result;
	switch (result) {
	case ORDER_OUT_OF_MEMORY:
		return_result = MTM_OUT_OF_MEMORY;
		break;
	case ORDER_NULL_PARAMETER:
		return_result = MTM_NULL_PARAMETER;
		break;
	case ORDER_INVALID_PARAMETER:
		return_result = MTM_INVALID_PARAMETER;
		break;
	case ORDER_SUCCESS:
		return_result = MTM_SUCCESS;
		break;
	}
	return return_result;
}

/**
 * handle SetResult. get SetResult enum for input and convert it to a
 * MtmErrorCode enum.
 *
 * @param SetResult, the result to parse.
 * @return MtmErrorCode, the result that equivalent to the inputed.
 */
static MtmErrorCode convertSetResultToMtmResult(SetResult result) {
	MtmErrorCode return_result;
	switch (result) {
	case SET_NULL_ARGUMENT:
		return_result = MTM_NULL_PARAMETER;
		break;
	case SET_OUT_OF_MEMORY:
		return_result = MTM_OUT_OF_MEMORY;
		break;
	default:
		return_result = MTM_SUCCESS;
		break;
	}
	return return_result;
}
/**
 * handle ListResult. get ListResult enum for input and convert it to a
 * MtmErrorCode enum.
 *
 * @param ListResult, the result to parse.
 * @return MtmErrorCode, the result that equivalent to the inputed.
 */
static MtmErrorCode convertListResultToMtmResult(ListResult result) {
	MtmErrorCode return_result;
	switch (result) {
	case LIST_NULL_ARGUMENT:
		return_result = MTM_NULL_PARAMETER;
		break;
	case LIST_OUT_OF_MEMORY:
		return_result = MTM_OUT_OF_MEMORY;
		break;
	case LIST_SUCCESS:
		return_result = MTM_SUCCESS;
		break;
	default:
		return_result = MTM_INVALID_PARAMETER;
		break;
	}
	return return_result;
}

/**
 * This function is Used for implementing listFilter Function of List ADT.
 * This function check if a certain Company has the same faculty as the
 * ListFilterKey
 *
 * @param listElement - the company to check
 * @param listFilterKey - the faculty
 *
 * @return true if the company belongs to the same faculty like the key.
 * and false otherwise/
 */
static bool filterCompanyListIsFacultyId(ListElement company, ListFilterKey key) {
	return getCompanyFaculty((Company) company) == *(int*) key;
}

/**
 * check if id of faculty is valid. according the mtm_ex3.h standards.
 */
static bool validFaculty(TechnionFaculty faculty) {
	return (faculty < UNKNOWN && faculty >= CIVIL_ENGINEERING);
}
/**
 * check if integer of id is positive, therefore valid.
 */
static bool validId(int id) {
	return (id > 0);
}

/**
 * create a List of companies from a Set of companies/
 *
 * @param Set of companies
 * @return list of the same set of companies. NULL if Error in the way.
 */
static List createListFromSetOfCompanies(Set set_company) {
	List companies_list = listCreate(companyCopyListFunction,
			freeCompanyListFunction);
	if (!companies_list) {
		return NULL;
	}
	SET_FOREACH(Company, company, set_company)
	{
		if (listInsertFirst(companies_list, company) != LIST_SUCCESS) {
			return NULL;
		}
	}
	return companies_list;
}

/**
 * This function searches the escapeTechnion companies and Escapers. and check if
 * the given email is already been using.
 *
 * @param escapeTechnion
 * @param char* email to check
 *
 * @return true if the email is taken by other user.
 */
static bool checkIfClientEmailExist(EscapeTechnion escapeTechnion, char* email) {
	assert(escapeTechnion != NULL && email != NULL);
	SET_FOREACH(Company, company, escapeTechnion->companies)
	{
		if (strcmp(getCompanyEmail(company), email) == 0) {
			return true;
		}
	}
	SET_FOREACH(Escaper, escaper, escapeTechnion->escapers)
	{
		if (strcmp(getEscaperEmail(escaper), email) == 0) {
			return true;
		}
	}
	return false;
}
/**
 * This function get escapeTechnion and email for input and return a copy of the escaper
 * in the escapeTechnion that has this email.
 *
 * This function assume that the escaper is in the escapeTechnion.
 * @param escapeTechnion
 * @param char* email
 *
 * @return - NULL if there are problems with memory allocations. and Escaper
 * otherwise.
 */
static Escaper getEscaperFromEscapeTechnion(EscapeTechnion escapeTechnion,
		char* email) {
	assert(escapeTechnion != NULL && email != NULL);
	SET_FOREACH(Escaper, escaper, escapeTechnion->escapers)
	{
		if (strcmp(getEscaperEmail(escaper), email) == 0) {
			return escaperCopy(escaper);
		}
	}
	return NULL;
}
/**
 * This function is Used for implementing listFilter Function of List ADT.
 * This function check if a certain Order already been used, means, its day
 * is 0.
 *
 * @param listElement - the order to check
 * @param listFilterKey - Not important
 *
 * @return true if the order reached its day.
 */
static bool isOrderAtCurrentDay(ListElement order, ListFilterKey key) {
	return (getOrderDay(order) == 0);
}

/**
 * This function get escapeTechnion, company and room_id for parameters. and check
 * if the certain company has orders or a certain room inside the compant
 * has orders.
 *
 * @param escapeTechnion - the escapeTechnion to check in it.
 * @param company - check if this company has orders
 * @param room_id - the id of a room we want to check if it has orders.
 * 					if the id is -1 == REGULAR_FUNC_CONST, than the function
 * 					will ignore this parameter.
 *
 * @return bool True if there are orders. and false otherwise.
 */
static bool checkIfCompanyRoomsHaveOrders(EscapeTechnion escapeTechnion,
		Company company, int room_id) {
	if (listGetSize(escapeTechnion->orders) == 0) {
		return false;
	}
	if (room_id == REGULAR_FUNC_CONST) {
		List list_filter = listFilter(escapeTechnion->orders,
				orderListCompareByCompany,
				(ListFilterKey) getCompanyEmail(company));
		int size = listGetSize(list_filter);
		listDestroy(list_filter);
		if (size != 0) {
			return true;
		}
		return false;
	} else {
		List list_filter1 = listFilter(escapeTechnion->orders,
				orderListCompareByCompany,
				(ListFilterKey) getCompanyEmail(company));
		List list_filter2 = listFilter(list_filter1, orderListCompareByRoomId,
				(ListFilterKey) &room_id);
		listDestroy(list_filter1);
		int size = listGetSize(list_filter2) != 0;
		listDestroy(list_filter2);
		if (size != 0) {
			return true;
		}
		return false;
	}
	return false;
}

/**
 * Removing an Order from a List of orders.
 * @param List - the list to remove from
 * @param order - the order the function will remove.
 *
 * @return ListResult.
 */
static ListResult listRemove(List list, Order order) {
	LIST_FOREACH(Order, order_itr, list)
	{
		if (orderCompare(order, order_itr) == 0) {
			return listRemoveCurrent(list);
		}
	}
	return LIST_NULL_ARGUMENT;

}

/**
 * this function check if a certain escaper has orders with the same time
 * has the given new_order object
 *
 * @param escapeTechnion
 * @param Escaper - the escaper the function checks.
 * @param Order - the criteria which we search if the escaper has order that
 * 					parallel to the this order.
 *
 * @return bool True if there are, false otherwise.
 */
static MtmErrorCode escaperCheckIfOrdersInSameTime(
		EscapeTechnion escapeTechnion, Escaper escaper, Order new_order) {
	assert(escapeTechnion != NULL && escaper != NULL && new_order != NULL);
	MtmErrorCode result = MTM_SUCCESS;
	LIST_FOREACH(Order, order, escapeTechnion->orders)
	{
		if (orderCompareByTimeList(order, new_order) == 0) {
			if (strcmp(getOrderEscaperEmail(order),
					getOrderEscaperEmail(new_order)) == 0) {
				return MTM_CLIENT_IN_ROOM;
			}
			if (getOrderRoomId(order) == getOrderRoomId(new_order)
					&& getOrderRoomFaculty(order)
							== getOrderRoomFaculty(new_order)) {
				result = MTM_ROOM_NOT_AVAILABLE;
			}
		}
	}
	if (result != MTM_SUCCESS) {
		return result;
	}
	SET_FOREACH(Company, company, escapeTechnion->companies)
	{
		if (strcmp(getCompanyEmail(company), getOrderCompanyEmail(new_order))
				== 0) {
			List rooms_temp = companyGetListOfRooms(company);
			LIST_FOREACH(Room, room, rooms_temp)
			{
				if ((getOrderRoomId(new_order) == getRoomId(room))
						&& ((getRoomHourClose(room) <= getOrderHour(new_order)
								|| getRoomHourOpen(room) > getOrderHour(new_order)))) {
					listDestroy(rooms_temp);
					return MTM_ROOM_NOT_AVAILABLE;
				}
			}
			listDestroy(rooms_temp);
		}
	}
	getOrderRoomId(new_order);
	getOrderRoomFaculty(new_order);
	return result;
}

/**
 * this function get Room, Escaper , int num_ppl and calculate the formula
 * of recommend room.
 */
static int returnRecommendFormula(Room room, Escaper escaper, int num_ppl) {
	assert(room != NULL && escaper != NULL);
	int recommend_formula = ((getRoomNumPpl(room) - num_ppl)
			* (getRoomNumPpl(room) - num_ppl))
			+ ((getRoomDifficulty(room) - getEscaperSkill(escaper))
					* (getRoomDifficulty(room) - getEscaperSkill(escaper)));
	return recommend_formula;
}
/**
 * function for filtering a list of orders according to a certain faculty
 */
static bool isOrderInFaculty(ListElement order, ListFilterKey key) {
	return (getOrderRoomFaculty((Order) order) == *(int*) key);

}
/**
 * function for filtering a list of orders according to a certain room_id
 */
static bool isOrderHasRoomId(ListElement order, ListFilterKey key) {
	return (getOrderRoomId((Order) order) == *(int*) key);
}

/**
 * this function create a time String in format of day-hour.
 * @param day int
 * @param hour int
 *
 * @return char* in the above format. NULL problem with memory allocations.
 */
static char* convertIntToTimeString(int day, int hour) {
	int temp_day = day;
	int num_of_numbers = 1;
	while (temp_day != 0) {
		temp_day = temp_day / 10;
		num_of_numbers += 1;
	}
	char* time = malloc(sizeof(char) * (num_of_numbers + 4));
	if (!time) {
		return NULL;
	}
	temp_day = day;
	for (int i = 0; i < num_of_numbers; i++) {
		int x = temp_day % 10;
		time[num_of_numbers - i - 1] = '0' + x;
		temp_day = temp_day / 10;
	}
	time[num_of_numbers] = '-';
	time[num_of_numbers + 1] = '0' + (hour / 10);
	time[num_of_numbers + 2] = '0' + (hour % 10);
	time[num_of_numbers + 3] = '\0';
	return time;
}

/**
 * check if a certain escaper has an order in a particular day, hour in the
 * system.
 *
 * @param list of orders
 * @param escaper
 * @param day
 * @param hour
 *
 * @return true if he has, false otherwise
 */
static bool ifEscaperHasOrderInThisTime(List all_orders, Escaper escaper,
		int day, int hour) {
	assert(all_orders!= NULL && escaper != NULL);
	LIST_FOREACH(Order, order, all_orders)
	{
		if ((getOrderHour(order) == hour) && (getOrderDay(order) == day)) {
			if (strcmp(getEscaperEmail(escaper), getOrderEscaperEmail(order))
					== 0) {
				return true;
			}
		}
	}
	return false;
}
/**
 * this function return the soonest time that the room is available for order.
 *
 * @param escapeTechnion
 * @param Room
 * @return char* - string in the format of day-hour. days to order and hour of
 * order. if problem with memory allocations than return NULL
 */
static char* getRoomSoonnestAvailableTime(EscapeTechnion escapeTechnion,
		Room room, Escaper escaper) {
	int id = getRoomId(room);
	List list_filter = listFilter(escapeTechnion->orders, isOrderHasRoomId,
			&id);
	if (!list_filter) {
		return NULL;
	}
	TechnionFaculty faculty = getRoomFaculty(room);
	List list_filter2 = listFilter(list_filter, isOrderInFaculty, &faculty);
	listDestroy(list_filter);
	if (!list_filter2) {
		return NULL;
	}
	int open = getRoomHourOpen(room);
	int close = getRoomHourClose(room);
	int itr_day = 0;
	while (true) {
		for (int i = open; i < close; i++) {
			bool taken = false;
			LIST_FOREACH(Order, order, list_filter2)
			{
				if ((getOrderDay(order) == itr_day)
						&& (getOrderHour(order) == i)) {
					taken = true;
				}
			}
			if (ifEscaperHasOrderInThisTime(escapeTechnion->orders, escaper,
					itr_day, i)) {
				taken = true;
			}
			if (!taken) {
				listDestroy(list_filter2);
				return convertIntToTimeString(itr_day, i);
			}
		}
		itr_day += 1;
	}
	listDestroy(list_filter2);
	return NULL;
}

/**
 * add a all the rooms the the escapeTechnion contains trough the companies
 * and insert it into a single List of rooms.
 */
static MtmErrorCode addAllRoomsToList(EscapeTechnion escapeTechnion,
		List list_rooms) {
	SET_FOREACH(Company, company, escapeTechnion->companies)
	{
		List temp_list = companyGetListOfRooms(company);
		if (!temp_list) {
			listDestroy(list_rooms);
			return MTM_OUT_OF_MEMORY;
		}
		LIST_FOREACH(Room, room, temp_list)
		{

			if (listInsertLast(list_rooms, room) != LIST_SUCCESS) {
				listDestroy(temp_list);
				listDestroy(list_rooms);
				return MTM_OUT_OF_MEMORY;
			}
		}
		listDestroy(temp_list);
	}
	return MTM_SUCCESS;
}

/**
 * this function get the best recommend room according to the inputed params
 * and formula of the exercise.
 *
 * this function assume that the ListRooms size  is not 0
 */
static ListResult insertReccomendRoomsInList(List good_rooms, List list_rooms,
		Escaper escaper, int num_ppl) {
	ListResult result;
	int recommend_formula = INVALID_INT;
	TechnionFaculty best_faculty = UNKNOWN;
	int best_room_id = INVALID_INT;
	int best_fac_diff = INVALID_INT;
	TechnionFaculty escaper_faculty = getEscaperFaculty(escaper);
	LIST_FOREACH(Room, room, list_rooms)
	{
		int temp_result = returnRecommendFormula(room, escaper, num_ppl);
		if (recommend_formula == INVALID_INT
				|| temp_result < recommend_formula) {
			recommend_formula = temp_result;
			best_faculty = getRoomFaculty(room);
			best_room_id = getRoomId(room);
			best_fac_diff = abs(best_faculty - escaper_faculty);
		} else if (temp_result == recommend_formula) {
			TechnionFaculty temp_faculty = getRoomFaculty(room);
			int temp_diff = abs(temp_faculty - escaper_faculty);
			if (best_fac_diff == INVALID_INT || temp_diff < best_fac_diff) {
				best_fac_diff = temp_diff;
				best_faculty = temp_faculty;
				best_room_id = getRoomId(room);

			} else if (temp_diff == best_fac_diff) {
				if (temp_faculty < best_faculty) {
					best_faculty = temp_faculty;
					best_room_id = getRoomId(room);
				} else if (temp_faculty == best_faculty) {
					int temp_room_id = getRoomId(room);
					if (best_room_id == INVALID_INT
							|| temp_room_id < best_room_id) {
						best_room_id = temp_room_id;
					}
				}
			}
		}
	}
	LIST_FOREACH(Room, room, list_rooms)
	{
		int temp_room_id = getRoomId(room);
		TechnionFaculty temp_room_faculty = getRoomFaculty(room);
		if (temp_room_id == best_room_id && temp_room_faculty == best_faculty) {
			result = listInsertLast(good_rooms, room);
			if (result != LIST_SUCCESS) {
				return result;
			}
		}
	}
	return LIST_SUCCESS;
}

/**
 * a function to check if char* work_hrs is according to the HW3 standard
 */
static bool checkValidWorkHrs(char* work_hrs) {
	if (strlen(work_hrs) != 5) {
		return false;
	}
	if (work_hrs[0] < '0' || work_hrs[0] > '9') {
		return false;
	}
	if (work_hrs[1] < '0' || work_hrs[1] > '9') {
		return false;
	}
	if (work_hrs[3] < '0' || work_hrs[3] > '9') {
		return false;
	}
	if (work_hrs[4] < '0' || work_hrs[4] > '9') {
		return false;
	}
	if (work_hrs[2] != '-') {
		return false;
	}
	int x1 = work_hrs[0] - '0';
	int x2 = work_hrs[1] - '0';
	int y1 = work_hrs[3] - '0';
	int y2 = work_hrs[4] - '0';
	int open = x1;
	open = open * 10;
	open = open + x2;
	int close = y1;
	close = close * 10;
	close = close + y2;
	return open < close;
}

/**
 * check if difficulty level is between 1 and 10
 * @param int difficulty_level to check
 * @return true if valid, false otherwise
 */
static bool checkValidDifficultLevel(int difficult_level) {
	return (difficult_level > 0 && difficult_level <= 10);
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
 * check if the price is according to the HW3 standard
 */
static bool checkValidPrice(int price) {
	return ((price % 4 == 0) && (price > 0));
}
/**
 * check if a given char* time of order is according to the HW3 standard
 */
static bool checkOrderTime(char* time) {
	int len = strlen(time);
	int index_comma = INVALID_INT;
	int amount_comma = 0;
	if (len < 3) {
		return false;
	} else if (len == 3) {
		if (time[FIRST_PLACE_ARR] == '-') {
			return false;
		}
	}
	for (int i = 0; i < strlen(time); i++) {
		if (time[i] == '-') {
			amount_comma++;
			index_comma = i;
		}
	}
	if ((amount_comma != 1) || (index_comma < (len - 3))
			|| (index_comma == (len - 1))) {
		return false;
	}
	for (int i = 0; i < index_comma; i++) {
		if (time[i] < '0' || time[i] > '9') {
			return false;
		}
	}
	int h2 = INVALID_INT;
	int h1 = FIRST_PLACE_ARR;
	if (index_comma == len - 3) {
		if ((time[len - 1] < '0' || time[len - 1] > '9')
				|| ((time[len - 2] < '0' || time[len - 2] > '9'))) {
			return false;
		}
		h2 = time[len - 1] - '0';
		h1 = time[len - 2] - '0';
	} else if (index_comma == len - 2) {
		if ((time[len - 1] < '0') || (time[len - 1] > '9')) {
			return false;
		}
		h2 = time[len - 1] - '0';
	} else {
		return false;
	}
	int hour = (h1 * 10) + h2;
	return (hour < 24 && hour >= 0);
}
/**
 * function for readability. get LIST,LIST,ESCAPER and destroy all of them.
 *
 */
static void destroyTwoListAndEscaper(List list1, List list2, Escaper escaper) {
	if (list1 != NULL) {
		listDestroy(list1);
	}
	if (list2 != NULL) {
		listDestroy(list2);
	}
	if (escaper != NULL) {
		destroyEscaper(escaper);
	}
}

/**
 * Check if the email is valid, meaning has only One '@'
 * @param char* email
 * @return true if valid, false otherwise
 */
/** IMPLEMENT HEADER **/
EscapeTechnion createEscapeTechnion() {
	EscapeTechnion escapeTechnion = malloc(sizeof(*escapeTechnion));
	if (!escapeTechnion) {
		return NULL;
	}
	escapeTechnion->companies = setCreate(companyCopySetFunction,
			freeCompanySetFunction, companyCompareEmails);
	if (escapeTechnion->companies == NULL) {
		return NULL;
	}
	escapeTechnion->escapers = setCreate(escaperCopySetFunction,
			freeEscaperSetFunction, escaperCompare);
	if (escapeTechnion->escapers == NULL) {
		setDestroy(escapeTechnion->companies);
		free(escapeTechnion);
		return NULL;
	}
	escapeTechnion->orders = listCreate(orderCopyListFunction,
			freeOrderListFunction);
	if (escapeTechnion->orders == NULL) {
		setDestroy(escapeTechnion->companies);
		setDestroy(escapeTechnion->escapers);
		free(escapeTechnion);
	}
	int* new_arr = malloc(sizeof(int) * UNKNOWN);
	escapeTechnion->faculties_profit = new_arr;
	if (!escapeTechnion->faculties_profit) {
		setDestroy(escapeTechnion->companies);
		setDestroy(escapeTechnion->escapers);
		listDestroy(escapeTechnion->orders);
		free(escapeTechnion);
		return NULL;
	}
	for (int i = 0; i < UNKNOWN; i++) {
		escapeTechnion->faculties_profit[i] = 0;
	}
	escapeTechnion->escapeTechnion_day = 0;
	return escapeTechnion;
}

void destroyEscapeTechnion(EscapeTechnion escapeTechnion) {
	if (escapeTechnion == NULL) {
		return;
	}
	setDestroy(escapeTechnion->companies);
	setDestroy(escapeTechnion->escapers);
	listDestroy(escapeTechnion->orders);
	free(escapeTechnion->faculties_profit);
	free(escapeTechnion);
}

MtmErrorCode companyAdd(EscapeTechnion escapeTechnion, char* email,
		TechnionFaculty faculty) {
	if (!escapeTechnion || !email) {
		return MTM_NULL_PARAMETER;
	}
	if (!ifValidEmail(email) || !validFaculty(faculty)) {
		return MTM_INVALID_PARAMETER;
	}
	if (checkIfClientEmailExist(escapeTechnion, email)) {
		return MTM_EMAIL_ALREADY_EXISTS;
	}
	CompanyResult company_result = COMPANY_DEFAULT;
	Company company_to_add = createCompany(email, faculty, &company_result);
	if (!company_to_add) {
		return handleCompanyResult(company_result);
	}
	SetResult set_result = setAdd(escapeTechnion->companies, company_to_add);
	destroyCompany(company_to_add);
	return convertSetResultToMtmResult(set_result);
}

MtmErrorCode companyRemove(EscapeTechnion escapeTechnion, char* email) {
	if (!escapeTechnion || !email) {
		return MTM_NULL_PARAMETER;
	}
	if (!ifValidEmail(email)) {
		return MTM_INVALID_PARAMETER;
	}
	SET_FOREACH(Company, company, escapeTechnion->companies)
	{
		if (strcmp(getCompanyEmail(company), email) == 0) {
			if (!checkIfCompanyRoomsHaveOrders(escapeTechnion, company,
			REGULAR_FUNC_CONST)) {
				SetResult s_result = setRemove(escapeTechnion->companies,
						company);
				return convertSetResultToMtmResult(s_result);
			}
			return MTM_RESERVATION_EXISTS;
		}
	}
	return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
}
MtmErrorCode roomAdd(EscapeTechnion escapeTechnion, char* email, int id,
		int price, int num_ppl, char* working_hrs, int difficulty) {
	if (!escapeTechnion || !email || !working_hrs)
		return MTM_NULL_PARAMETER;
	if (!ifValidEmail(email) || !checkValidWorkHrs(working_hrs)
			|| !checkValidPrice(price) || !checkValidDifficultLevel(difficulty)
			|| !validId(id) || !validId(num_ppl)) {
		return MTM_INVALID_PARAMETER;
	}
	SET_FOREACH(Company, company, escapeTechnion->companies)
	{
		if (strcmp(getCompanyEmail(company), email) == 0) {
			List company_escapeTechnion_list = createListFromSetOfCompanies(
					escapeTechnion->companies);
			if (!company_escapeTechnion_list) {
				return MTM_OUT_OF_MEMORY;
			}
			int current_company_faculty = getCompanyFaculty(company);
			List filtered_company_list = listFilter(company_escapeTechnion_list,
					filterCompanyListIsFacultyId, &current_company_faculty);
			listDestroy(company_escapeTechnion_list);
			LIST_FOREACH(Company, companyFiltered, filtered_company_list)
			{
				if (checkCompanyHasRoomWithId(companyFiltered, id)) {
					listDestroy(filtered_company_list);
					return MTM_ID_ALREADY_EXIST;
				}
			}
			listDestroy(filtered_company_list);
			RoomResult result = ROOM_DEFAULT;
			Room new_room = createRoom(id, price, num_ppl, working_hrs,
					difficulty, current_company_faculty,
					getCompanyEmail(company), &result);
			if (!new_room)
				return MTM_OUT_OF_MEMORY;
			if (result != ROOM_SUCCESS) {
				return (handleRoomResult(result));
			}
			CompanyResult c_result = addRoomToCompany(company, new_room);
			destroyRoom(new_room);
			return handleCompanyResult(c_result);
		}
	}
	return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
}

MtmErrorCode roomRemove(EscapeTechnion escapeTechnion, TechnionFaculty faculty,
		int id) {
	assert(escapeTechnion);
	if (!validFaculty(faculty) || !validId(id))
		return MTM_INVALID_PARAMETER;
	SET_FOREACH(Company,company,escapeTechnion->companies)
	{
		if (getCompanyFaculty(company) == faculty) {
			if (checkCompanyHasRoomWithId(company, id)) {
				if (!checkIfCompanyRoomsHaveOrders(escapeTechnion, company,
						id)) {
					CompanyResult c_res = removeRoomFromCompany(company, id);
					return handleCompanyResult(c_res);
				}
				return MTM_RESERVATION_EXISTS;
			}
		}
	}
	return MTM_ID_DOES_NOT_EXIST;
}

MtmErrorCode escaperAdd(EscapeTechnion escapeTechnion, char *email,
		TechnionFaculty faculty, int skill_level) {
	assert(escapeTechnion);
	if (!email) {
		return MTM_NULL_PARAMETER;
	}
	if (!ifValidEmail(email) || !checkValidSkillLevel(skill_level)
			|| !validFaculty(faculty)) {
		return MTM_INVALID_PARAMETER;
	}
	SET_FOREACH(Escaper,escaper,escapeTechnion->escapers)
	{
		if (strcmp(getEscaperEmail(escaper), email) == 0) {
			return MTM_EMAIL_ALREADY_EXISTS;
		}
	}
	SET_FOREACH(Company,company,escapeTechnion->companies)
	{
		if (strcmp(getCompanyEmail(company), email) == 0) {
			return MTM_EMAIL_ALREADY_EXISTS;
		}
	}
	EscaperResult result = ESCAPER_SUCCESS;
	Escaper escaper_to_add = createEscaper(email, faculty, skill_level,
			&result);
	if (result != ESCAPER_SUCCESS) {
		return (handleEscaperResult(result));
	}
	SetResult result2 = setAdd(escapeTechnion->escapers, escaper_to_add);
	destroyEscaper(escaper_to_add);
	return convertSetResultToMtmResult(result2);
}

MtmErrorCode escaperRemove(EscapeTechnion escapeTechnion, char *email) {
	assert(escapeTechnion);
	if (!email)
		return MTM_NULL_PARAMETER;
	if (!ifValidEmail(email))
		return MTM_INVALID_PARAMETER;

	SET_FOREACH(Escaper,escaper,escapeTechnion->escapers)
	{
		if (strcmp(getEscaperEmail(escaper), email) == 0) {
			List list_filter = listFilter(escapeTechnion->orders,
					orderListCompareByEscaperEmail, (ListFilterKey) email);
			LIST_FOREACH(Order, order, list_filter)
			{
				ListResult l_result = listRemove(escapeTechnion->orders, order);
				if (l_result != LIST_SUCCESS) {
					return convertListResultToMtmResult(l_result);
				}
			}
			listDestroy(list_filter);
			SetResult result = setRemove(escapeTechnion->escapers, escaper);
			if (result != SET_SUCCESS) {
				return convertSetResultToMtmResult(result);
			}
			return MTM_SUCCESS;
		}
	}
	return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
}

MtmErrorCode escaperOrder(EscapeTechnion escapeTechnion, char* email,
		TechnionFaculty faculty, int id, char* time, int num_ppl) {
	assert(escapeTechnion != NULL);
	if (!email || !time) {
		return MTM_NULL_PARAMETER;
	}
	if (!ifValidEmail(email) || !checkOrderTime(time)
			|| !validFaculty(faculty) || id < 0 || num_ppl < 0) {
		return MTM_INVALID_PARAMETER;
	}
	OrderResult o_result;
	SET_FOREACH(Escaper, escaper, escapeTechnion->escapers)
	{
		if (strcmp(getEscaperEmail(escaper), email) == 0) {
			SET_FOREACH(Company, company, escapeTechnion->companies)
			{
				if (getCompanyFaculty(company) == faculty) {
					if (checkCompanyHasRoomWithId(company, id)) {
						Order new_order = createOrder(time, num_ppl, email, id,
								faculty, getEscaperSkill(escaper),
								getEscaperFaculty(escaper),
								getCompanyEmail(company),
								getRoomDifficultyFromCompany(company, id),
								getRoomPriceFromCompany(company, id),
								&o_result);
						if (!new_order) {
							return handleOrderResult(o_result);
						}
						MtmErrorCode result = escaperCheckIfOrdersInSameTime(
								escapeTechnion, escaper, new_order);
						if (result != MTM_SUCCESS) {
							destroyOrder(new_order);
							return result;
						}
						ListResult l_result;
						l_result = listInsertFirst(escapeTechnion->orders,
								new_order);
						destroyOrder(new_order);
						return convertListResultToMtmResult(l_result);
					}
				}
			}
			return MTM_ID_DOES_NOT_EXIST;
		}
	}
	return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
}

MtmErrorCode escaperRecommend(EscapeTechnion escapeTechnion, char* email,
		int num_ppl) {
	assert(escapeTechnion != NULL);
	if (!email) {
		return MTM_NULL_PARAMETER;
	}
	if (!ifValidEmail(email) || !validId(num_ppl)) {
		return MTM_INVALID_PARAMETER;
	}
	if (!checkIfClientEmailExist(escapeTechnion, email)) {
		return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
	}
	Escaper escaper = getEscaperFromEscapeTechnion(escapeTechnion, email);
	if (!escaper) {
		return MTM_OUT_OF_MEMORY;
	}
	List list_rooms = listCreate(roomCopyListFunction, freeRoomListFunction);
	if (!list_rooms) {
		destroyTwoListAndEscaper(NULL, NULL, escaper);
		return MTM_OUT_OF_MEMORY;
	}
	MtmErrorCode m_result = addAllRoomsToList(escapeTechnion, list_rooms);
	if (m_result != MTM_SUCCESS) {
		destroyTwoListAndEscaper(list_rooms, NULL, escaper);
		return m_result;
	}
	if (listGetSize(list_rooms) == 0) {
		destroyTwoListAndEscaper(list_rooms, NULL, escaper);
		return MTM_NO_ROOMS_AVAILABLE;
	}
	List good_rooms = listCreate(roomCopyListFunction, freeRoomListFunction);
	if (!good_rooms) {
		destroyTwoListAndEscaper(list_rooms, NULL, escaper);
		return MTM_OUT_OF_MEMORY;
	}
	ListResult l_result = insertReccomendRoomsInList(good_rooms, list_rooms,
			escaper, num_ppl);
	if (l_result != LIST_SUCCESS) {
		destroyTwoListAndEscaper(list_rooms, good_rooms, escaper);
		return convertListResultToMtmResult(l_result);
	}
	if (listGetSize(good_rooms) != 1) {
		return MTM_NO_ROOMS_AVAILABLE;
	}
	Room best_room = listGetFirst(good_rooms);
	char* best_time_of_order = getRoomSoonnestAvailableTime(escapeTechnion,
			best_room, escaper);
	if (!best_time_of_order) {
		destroyTwoListAndEscaper(list_rooms, good_rooms, escaper);
		return MTM_OUT_OF_MEMORY;
	}
	OrderResult o_result = ORDER_SUCCESS;
	Order order_to_insert = createOrder(best_time_of_order, num_ppl,
			getEscaperEmail(escaper), getRoomId(best_room),
			getRoomFaculty(best_room), getEscaperSkill(escaper),
			getEscaperFaculty(escaper), getRoomCompanyEmail(best_room),
			getRoomDifficulty(best_room), getRoomPrice(best_room), &o_result);
	free(best_time_of_order);
	if (o_result != ORDER_SUCCESS) {
		destroyTwoListAndEscaper(list_rooms, good_rooms, escaper);
		return handleOrderResult(o_result);
	}
	l_result = listInsertLast(escapeTechnion->orders, order_to_insert);
	destroyOrder(order_to_insert);
	destroyTwoListAndEscaper(list_rooms, good_rooms, escaper);
	return convertListResultToMtmResult(l_result);
}

MtmErrorCode reportDay(EscapeTechnion escapeTechnion, FILE* outputChannel) {
	if (outputChannel == NULL) {
		return MTM_NULL_PARAMETER;
	}
	List list_filter_time = listFilter(escapeTechnion->orders,
			isOrderAtCurrentDay,
			NULL);
	mtmPrintDayHeader(outputChannel, escapeTechnion->escapeTechnion_day,
			listGetSize(list_filter_time));
	listSort(list_filter_time, orderCompareByTimeFacultyRoomList);
	LIST_FOREACH(Order, order, list_filter_time)
	{
		printOrder(order, outputChannel);
		escapeTechnion->faculties_profit[getOrderRoomFaculty(order)] +=
				getOrderPrice(order);
		ListResult l_result = listRemove(escapeTechnion->orders, order);
		if (l_result != LIST_SUCCESS) {
			listDestroy(list_filter_time);
			return MTM_OUT_OF_MEMORY;
		}
	}
	listDestroy(list_filter_time);
	mtmPrintDayFooter(outputChannel, escapeTechnion->escapeTechnion_day);
	escapeTechnion->escapeTechnion_day += 1;
	LIST_FOREACH(Order, order, escapeTechnion->orders)
	{
		reportOrderDay(order);
	}
	return MTM_SUCCESS;
}

MtmErrorCode reportBest(EscapeTechnion escapeTechnion, FILE* outputChannel) {
	if (outputChannel == NULL) {
		return MTM_NULL_PARAMETER;
	}
	int sum_profit = escapeTechnion->faculties_profit[FIRST_PLACE_ARR];
	int max_profit = escapeTechnion->faculties_profit[FIRST_PLACE_ARR];
	int max_profit_itr = FIRST_PLACE_ARR;
	for (int i = FIRST_PLACE_ARR + 1; i < UNKNOWN; i++) {
		if (escapeTechnion->faculties_profit[i] > max_profit) {
			max_profit = escapeTechnion->faculties_profit[i];
			max_profit_itr = i;
		}
		sum_profit += escapeTechnion->faculties_profit[i];
	}
	int second_max_profit = INVALID_INT;
	int second_max_profit_itr = INVALID_INT;
	for (int i = FIRST_PLACE_ARR; i < UNKNOWN; i++) {
		if (escapeTechnion->faculties_profit[i] > second_max_profit
				&& escapeTechnion->faculties_profit[i] <= max_profit
				&& (i != max_profit_itr)) {
			second_max_profit = escapeTechnion->faculties_profit[i];
			second_max_profit_itr = i;
		}
	}
	int third_max_profit = INVALID_INT;
	int third_max_profit_itr = INVALID_INT;
	for (int i = FIRST_PLACE_ARR; i < UNKNOWN; i++) {
		if (escapeTechnion->faculties_profit[i] > third_max_profit
				&& escapeTechnion->faculties_profit[i] <= second_max_profit
				&& (i != max_profit_itr) && (i != second_max_profit_itr)) {
			third_max_profit = escapeTechnion->faculties_profit[i];
			third_max_profit_itr = i;
		}
	}
	mtmPrintFacultiesHeader(outputChannel, UNKNOWN,
			escapeTechnion->escapeTechnion_day, sum_profit);
	mtmPrintFaculty(outputChannel, max_profit_itr, max_profit);
	mtmPrintFaculty(outputChannel, second_max_profit_itr, second_max_profit);
	mtmPrintFaculty(outputChannel, third_max_profit_itr, third_max_profit);
	mtmPrintFacultiesFooter(outputChannel);
	return MTM_SUCCESS;
}

int getEscapeTechnionDay(EscapeTechnion escapeTechnion) {
	assert(escapeTechnion);
	return escapeTechnion->escapeTechnion_day;
}

Set getCompaniesSet(EscapeTechnion escapeTechnion) {
	if (!escapeTechnion) {
		return NULL;
	}
	Set set = setCopy(escapeTechnion->companies);
	return set;
}
Set getEscapersSet(EscapeTechnion escapeTechnion) {
	if (!escapeTechnion) {
		return NULL;
	}
	Set set = setCopy(escapeTechnion->escapers);
	return set;
}
List getOrderList(EscapeTechnion escapeTechnion) {
	if (!escapeTechnion) {
		return NULL;
	}
	List list = listCopy(escapeTechnion->orders);
	return list;
}
