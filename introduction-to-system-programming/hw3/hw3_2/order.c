/*
 * Order.c
 *
 *  Created on: May 30, 2017
 *      Author: Noam
 */

#include "order.h"
#define SEVENTY_FIVE_PERCENTAGE 0.75
#define EXPONENT 10
#define INVALID_INT -1
#define FIRST_PLACE_ARR 0
struct order {
	int day;
	int hour;
	char* time;
	char* customer_email;
	char* company_email;
	int id_of_room_in_faculty; //id of room in faculty
	TechnionFaculty room_faculty;
	TechnionFaculty client_faculty;
	int skill_client;
	int difficulty;
	int num_ppl;
	int price;
};

/** STATIC FUNCTIONS **/

/**
 * This function convert the input of char* time, to ints of hour and day
 * @param Order the order to insert the given params into
 * @param char* time - the string to parse
 *
 * @return OrderResult
 * 			ORDER_OUT_OF_MEMORY if there are problems with memory allocations
 * 			ORDER_SUCCESS  otherwise
 */
static OrderResult convertTimeToInt(Order order, char* time) {
	int len = strlen(time);
	int day = 0;
	int i = 0;
	while (time[i] >= '0' && time[i] <= '9') {
		day = EXPONENT * day + (time[i] - '0');
		i++;
	}
	int x1 = FIRST_PLACE_ARR;
	int x2 = FIRST_PLACE_ARR;
	if (time[len - 3] == '-') {
		x1 = time[i + 1] - '0';
		x2 = time[i + 2] - '0';
	}
	else{
		x2 = time[i + 1] - '0';
	}
	int hour = (x1 * 10) + x2;
	order->hour = hour;
	order->day = day;
	return ORDER_SUCCESS;
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
 * check if order Time is in the right structure of day-hour.
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
	}
	int hour = h1 * 10 + h2;
	return (hour < 24 && hour >= 0);
}
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
 * check if an integer is a positive number. return true if yes. false otherwise.
 */
static bool positiveNumber(int num) {
	return (num > 0);
}

/**
 * check if id of faculty is valid. according the mtm_ex3.h standards.
 */
static bool validFaculty(TechnionFaculty faculty) {
	return (faculty < UNKNOWN && faculty >= CIVIL_ENGINEERING);
}

/**
 * check if id of skill is valid. according the mtm_ex3.h standards.
 */
static bool validSkillLevel(int skill) {
	return (skill < 11 && skill >= 1);
}

/**
 * check if id of price is valid. modulu of 4
 */
static bool validPriceOrder(int price) {
	return price % 4 == 0;
}
/**
 * This function get customer_email, company_email as params, and initialize
 * if to the right fields in the inputed Order object.
 *
 * @param Order the order to initialize his fields
 * @param char* customer email
 * @param char* company email
 *
 * @return OrderResult. ORDER_OUT_OF_MEMORY if problems with memory allocations
 * and ORDER_SUCCESS otherwise.
 */
static OrderResult intializeEmails(Order order, char* customer_email,
		char* comp_email) {
	order->customer_email = stringDuplicate(customer_email);
	if (order->customer_email == NULL) {
		free(order);
		return ORDER_OUT_OF_MEMORY;
	}
	order->company_email = stringDuplicate(comp_email);
	if (order->company_email == NULL) {
		destroyOrder(order);
		return ORDER_OUT_OF_MEMORY;
	}
	return ORDER_SUCCESS;
}
/** IMPLEMENT HEADER FILE **/

Order createOrder(char* time, int num_ppl, char* customer_email,
		int id_of_room_in_faculty, TechnionFaculty room_faculty,
		int skill_client, TechnionFaculty client_faculty, char* company_email,
		int difficulty, int price, OrderResult *result) {
	assert(result);
	if (!time || !customer_email || !company_email) {
		*result = ORDER_NULL_PARAMETER;
		return NULL;
	}
	if (!ifValidEmail(customer_email) || !ifValidEmail(company_email)
			|| !positiveNumber(num_ppl) || !positiveNumber(skill_client)
			|| !positiveNumber(difficulty) || !validFaculty(room_faculty)
			|| !validFaculty(client_faculty) || !positiveNumber(price)
			|| !positiveNumber(id_of_room_in_faculty)
			|| !validSkillLevel(skill_client) || !validPriceOrder(price)
			|| !validSkillLevel(difficulty) || !checkOrderTime(time)) {
		*result = ORDER_INVALID_PARAMETER;
		return NULL;
	}
	Order order = malloc(sizeof(*order));
	if (!order) {
		*result = ORDER_OUT_OF_MEMORY;
		return NULL;
	}
	if (convertTimeToInt(order, time) != ORDER_SUCCESS) {
		*result = ORDER_OUT_OF_MEMORY;
		free(order);
		return NULL;
	}
	*result = intializeEmails(order, customer_email, company_email);
	if (*result != ORDER_SUCCESS) {
		return NULL;
	}
	order->time = stringDuplicate(time);
	if (!order->time) {
		destroyOrder(order);
		*result = ORDER_OUT_OF_MEMORY;
		return NULL;
	}
	order->num_ppl = num_ppl;
	order->id_of_room_in_faculty = id_of_room_in_faculty;
	order->room_faculty = room_faculty;
	order->client_faculty = client_faculty;
	order->skill_client = skill_client;
	order->difficulty = difficulty;
	order->price = price;
	*result = ORDER_SUCCESS;
	return order;
}

void destroyOrder(Order order) {
	if (order == NULL) {
		return;
	}
	free(order->customer_email);
	free(order->company_email);
	free(order->time);
	free(order);
}

Order orderCopy(Order order) {
	if (order == NULL) {
		return NULL;
	}
	OrderResult result;
	Order order_new = createOrder(order->time, order->num_ppl,
			order->customer_email, order->id_of_room_in_faculty,
			order->room_faculty, order->skill_client, order->client_faculty,
			order->company_email, order->difficulty, order->price, &result);
	return order_new;
}
ListElement orderCopyListFunction(ListElement order) {
	return (ListElement) orderCopy((Order) order);
}
SetElement orderCopySetFunction(SetElement order) {
	return orderCopy((Order) order);
}

int orderCompareByTimeList(ListElement order_1, ListElement order_2) {
	assert(order_1 != NULL && order_2 != NULL);
	if (((Order) order_1)->day == ((Order) order_2)->day) {
		return ((Order) order_1)->hour - ((Order) order_2)->hour;
	} else {
		return ((Order) order_1)->day - ((Order) order_2)->day;
	}
}
int orderCompareByFacultyList(ListElement order_1, ListElement order_2) {
	assert(order_1 != NULL && order_2 != NULL);
	return ((Order) order_1)->room_faculty - ((Order) order_2)->room_faculty;
}

int orderCompareByTimeFacultyRoomList(ListElement order_1, ListElement order_2) {
	assert(order_1 != NULL && order_2 != NULL);
	if (((Order) order_1)->day == ((Order) order_2)->day) {
		if (((Order) order_1)->hour == ((Order) order_2)->hour) {
			if (((Order) order_1)->room_faculty
					== ((Order) order_2)->room_faculty) {
				return ((Order) order_1)->id_of_room_in_faculty
						- ((Order) order_2)->id_of_room_in_faculty;
			} else {
				return ((Order) order_1)->room_faculty
						- ((Order) order_2)->room_faculty;
			}
		} else {
			return ((Order) order_1)->hour - ((Order) order_2)->hour;
		}
	} else {
		return ((Order) order_1)->day - ((Order) order_2)->day;
	}
}

int orderCompareByRoomIdList(ListElement order_1, ListElement order_2) {
	assert(order_1 != NULL && order_2 != NULL);
	return ((Order) order_1)->id_of_room_in_faculty
			- ((Order) order_2)->id_of_room_in_faculty;
}

int orderCompare(Order order_1, Order order_2) {
	if ((strcmp(order_1->customer_email, order_2->customer_email) == 0)
			&& (order_1->day == order_2->day)
			&& (order_1->hour == order_2->hour)
			&& (order_1->id_of_room_in_faculty == order_2->id_of_room_in_faculty)
			&& (order_1->room_faculty == order_2->room_faculty)) {
		return 0;
	}
	return 1;
}

bool orderListCompareByCompany(ListElement listElement,
		ListFilterKey comp_email) {
	if (!listElement) {
		return false;
	}
	return (strcmp(((Order) listElement)->company_email, (char*) comp_email)
			== 0);
}

bool orderListCompareByRoomId(ListElement listElement, ListFilterKey room_id) {
	return ((Order) listElement)->id_of_room_in_faculty == *(int*) room_id;
}

bool orderListCompareByEscaperEmail(ListElement listElement,
		ListFilterKey escaper_email) {
	return strcmp(((Order) listElement)->customer_email, (char*) escaper_email)
			== 0;
}

char* getOrderEscaperEmail(Order order) {
	if (!order) {
		return NULL;
	}
	return order->customer_email;
}

char* getOrderCompanyEmail(Order order) {
	if (!order) {
		return NULL;
	}
	return order->company_email;
}

void freeOrderListFunction(ListElement order) {
	destroyOrder((Order) order);
}

void freeOrderSetFunction(SetElement order) {
	destroyOrder((Order) order);
}

int getOrderHour(Order order) {
	assert(order != NULL);
	return order->hour;
}
int getOrderDay(Order order) {
	assert(order != NULL);
	return order->day;
}

int getOrderRoomId(Order order) {
	assert(order != NULL);
	return order->id_of_room_in_faculty;
}
void printOrder(Order order, FILE* outputChannel) {
	mtmPrintOrder(outputChannel, order->customer_email, order->skill_client,
			order->client_faculty, order->company_email, order->room_faculty,
			order->id_of_room_in_faculty, order->hour, order->difficulty,
			order->num_ppl, getOrderPrice(order));
}

TechnionFaculty getOrderRoomFaculty(Order order) {
	assert(order != NULL);
	return order->room_faculty;
}

int getOrderPrice(Order order) {
	assert(order != NULL);
	if (order->client_faculty == order->room_faculty) {
		return (SEVENTY_FIVE_PERCENTAGE) * (order->price) * (order->num_ppl);
	}
	return order->price * (order->num_ppl);
}

void reportOrderDay(Order order) {
	assert(order);
	order->day -= 1;
	free(order->time);
	order->time = convertIntToTimeString(order->day, order->hour);
}

int getOrderNumPeople(Order order) {
	assert(order != NULL);
	return order->num_ppl;
}
