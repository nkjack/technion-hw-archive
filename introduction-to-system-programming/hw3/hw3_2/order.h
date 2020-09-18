/*
 * Order.h
 *
 *  Created on: May 30, 2017
 *      Author: Noam
 */

#ifndef ORDER_H_
#define ORDER_H_

#include "mtm_ex3.h"
#include "list.h"
#include "set.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct order *Order;

/**
 * This type defines all errors for the order.
 */
typedef enum {
	ORDER_OUT_OF_MEMORY, // You should exit program after this error
	ORDER_NULL_PARAMETER,
	ORDER_INVALID_PARAMETER,
	ORDER_SUCCESS,
} OrderResult;

/**
 * create an order which contains time of reservation, number of people, email
 * and the escaper who did the order.
 *
 * @param time char* with only 5 chars
 * @param num_ppl int number of people - positive number
 * @param email email of the customer
 * @param id of the room in faculty
 * @param faculty of the room
 * @param skill level of client
 * @param faculty of client
 * @param company email
 * @param difficulty of room
 * @param price of order
 * @param OrderResult - the param to return.
 *
 * @return Order or NULL if there are problems with memory allocations or bad
 * input params.
 */
Order createOrder(char* time, int num_ppl, char* customer_email,
		int id_of_room_in_faculty, TechnionFaculty room_faculty,
		int skill_client, TechnionFaculty client_faculty, char* company_email,
		int difficulty, int price, OrderResult *result);

/**
 * Destroy the order, and free all allocated memory
 *
 * @param order to destroy
 * @return void
 */
void destroyOrder(Order order);

/**
 * free function of order to implement List. using the destroyOrder function.
 */
void freeOrderListFunction(ListElement order);
/**
 * free function of order to implement Set. using the destroyOrder function.
 */
void freeOrderSetFunction(SetElement order);
/**
 * return a copy of the order that was input.
 *
 * @param order the order to take the values from
 * @return Order object, or NULL if problem with memory arises.
 */
Order orderCopy(Order order);

/**
 * copy function for implementing List. using orderCopy function
 */
ListElement orderCopyListFunction(ListElement order);

/**
 * copy function for implementing Set. using orderCopy function
 */
SetElement orderCopySetFunction(SetElement order);
/**
 * compare between to elements of Order. the comparison is by the time of the
 * order. This compare function will help to sort the list of orders in the
 * system.
 *
 * @param order_1
 * @param order_2
 *
 * return int > 0 if the time of order_2 is larger than order_1
 * 			== 0 if the time is the same
 * 		    < 0 if the time of order_1 is larger than order_2
 */
int orderCompareByTimeList(ListElement order_1, ListElement order_2);
/**
 * compare between to elements of Order. the comparison is by the faculty id.
 * This compare function will help to sort the list of orders in the
 * system by size of the faculty id.
 *
 * @param order_1
 * @param order_2
 *
 * return int > 0 if the faculty id of order_2 is larger than order_1
 * 			== 0 if the faculty id is the same
 * 		    < 0 if the faculty id of order_1 is larger than order_2
 */
int orderCompareByFacultyList(ListElement order_1, ListElement order_2);
/**
 * compare between to elements of Order. the comparison is by the room id.
 * This compare function will help to sort the list of orders in the
 * system by size of the room id.
 *
 * @param order_1
 * @param order_2
 *
 * return int > 0 if the room id of order_2 is larger than order_1
 * 			== 0 if the room id is the same
 * 		    < 0 if the room id of order_1 is larger than order_2
 */
int orderCompareByRoomIdList(ListElement order_1, ListElement order_2);

/**
 * This function Compare orders by its uniqe elements in order to distinct
 * between different orders.
 * The comparison is by the email_customer, reservation time, room id, room
 * faculty.
 *
 * @param order_1
 * @param order_2
 *
 * @return 0 if orders are the same, and 1 if different.
 */
int orderCompare(Order order_1, Order order_2);

int orderCompareByTimeFacultyRoomList(ListElement order_1, ListElement order_2);
/**
 * get the email of a Order from the struct.
 *
 * @param order struct
 * @return NULL if parameter is wrong or problem with memory allocations,
 * the copy of the order's email if otherwise.
 */
char* getOrderEscaperEmail(Order order);

/**
 * This function get Order as parameter and return the hour of the order
 * reservation.
 */
int getOrderHour(Order order);
/**
 * This function get Order as parameter and return the day of the order
 * reservation
 */
int getOrderDay(Order order);

/**
 * This function get Order as parameter and return the faculty of the room order
 * reservation
 */
TechnionFaculty getOrderRoomFaculty(Order order);

/**
 * This function get Order as parameter and return the price of the room order
 * reservation
 */
int getOrderPrice(Order order);


/**
 * This function get Order as parameter and return the id of the room order
 * reservation
 */
int getOrderRoomId(Order order);

/**
 * This function get Order as parameter and return the number of people of the room order
 * reservation
 */
int getOrderNumPeople(Order order);
/**
 * This function get Order as parameter and return the company email order
 * reservation
 */
char* getOrderCompanyEmail(Order order);

/**
 * This function is Used for implementing listFilter Function of List ADT.
 * This function check if a certain order has the same email has the
 * ListFilterKey
 *
 * @param listElement - the order to check
 * @param listFilterKey - the company email
 *
 * @return true if the order has the same company email like the key. and false
 * otherwise
 */
bool orderListCompareByCompany(ListElement listElement,
		ListFilterKey comp_email);
/**
 * This function is Used for implementing listFilter Function of List ADT.
 * This function check if a certain order has the same room_id has the
 * ListFilterKey
 *
 * @param listElement - the order to check
 * @param listFilterKey - the room_id to check
 *
 * @return true if the order has the same room id like the key. and false
 * otherwise
 */
bool orderListCompareByRoomId(ListElement listElement, ListFilterKey room_id);

/**
 * This function is Used for implementing listFilter Function of List ADT.
 * This function check if a certain order has the same escaper email has the
 * ListFilterKey
 *
 * @param listElement - the order to check
 * @param listFilterKey - the escaper email to check
 *
 * @return true if the order has the same escaper email like the key. and false
 * otherwise
 */
bool orderListCompareByEscaperEmail(ListElement listElement,
		ListFilterKey escaper_email);

/**
 * This function get Order and OutputChannel as parameters. and print it
 * according to the mtm_ex3.h function of printing order.
 */
void printOrder(Order order, FILE* outputChannel);

/**
 * this function decrease a day in the given order, and change the order time
 * string.
 */
void reportOrderDay(Order order);
#endif /* ORDER_H_ */
