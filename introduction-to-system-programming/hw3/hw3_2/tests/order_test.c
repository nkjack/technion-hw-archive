/*
 * unit_test_order.c
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
#include "../order.h"
#include "../list.h"

#define INVALID_INT -1
#define VALID_INT 1

static bool testOrderCreate() {
	OrderResult result;
	Order order = createOrder("123-12", 4, "valid@mail", 1, MATHEMATICS, 1,
			COMPUTER_SCIENCE, "valid@mail", 1, 4, &result);
	ASSERT_TEST(order != NULL);
	ASSERT_TEST(result == ORDER_SUCCESS);
	destroyOrder(order);
	order = createOrder(NULL, -1, "valid@mail", 1, MATHEMATICS, 1,
			COMPUTER_SCIENCE, "valid@mail", 1, 4, &result);
	ASSERT_TEST(result == ORDER_NULL_PARAMETER);

	order = createOrder("123-12", -1, NULL, 1, MATHEMATICS, 1,
			COMPUTER_SCIENCE, "valid@mail", 1, 4, &result);
	ASSERT_TEST(result == ORDER_NULL_PARAMETER);
	order = createOrder("123-12", -1, "valid@mail", 1, MATHEMATICS, 1,
			COMPUTER_SCIENCE, NULL, 1, 4, &result);
	ASSERT_TEST(result == ORDER_NULL_PARAMETER);
	order = createOrder("123-12", -1, "valid@mail", 1, MATHEMATICS, 1,
			COMPUTER_SCIENCE, "valid@mail", 1, 4, &result);
	ASSERT_TEST(result == ORDER_INVALID_PARAMETER);
	order = createOrder("123-12", 4, "validmail", 1, MATHEMATICS, 1,
			COMPUTER_SCIENCE, "valid@mail", 1, 4, &result);
	ASSERT_TEST(result == ORDER_INVALID_PARAMETER);
	order = createOrder("123-12", 4, "valid@mail", INVALID_INT, MATHEMATICS, 1,
			COMPUTER_SCIENCE, "valid@mail", 1, 4, &result);
	ASSERT_TEST(result == ORDER_INVALID_PARAMETER);
	order = createOrder("123-12", 4, "valid@mail", 1, UNKNOWN, 1,
			COMPUTER_SCIENCE, "valid@mail", 1, 4, &result);
	ASSERT_TEST(result == ORDER_INVALID_PARAMETER);
	order = createOrder("123-12", 4, "valid@mail", 1, INVALID_INT, 1,
			COMPUTER_SCIENCE, "valid@mail", 1, 4, &result);
	ASSERT_TEST(result == ORDER_INVALID_PARAMETER);
	order = createOrder("123-12", 4, "valid@mail", 1, MATHEMATICS, 0,
			COMPUTER_SCIENCE, "valid@mail", 1, 4, &result);
	ASSERT_TEST(result == ORDER_INVALID_PARAMETER);
	order = createOrder("123-12", 4, "valid@mail", 1, MATHEMATICS, 11,
			COMPUTER_SCIENCE, "valid@mail", 1, 4, &result);
	ASSERT_TEST(result == ORDER_INVALID_PARAMETER);
	order = createOrder("123-12", 4, "valid@mail", 1, MATHEMATICS, 1, UNKNOWN,
			"valid@mail", 1, 4, &result);
	ASSERT_TEST(result == ORDER_INVALID_PARAMETER);
	order = createOrder("123-12", 4, "valid@mail", 1, MATHEMATICS, 1,
			COMPUTER_SCIENCE, "valid@mail", 1, 5, &result);
	ASSERT_TEST(result == ORDER_INVALID_PARAMETER);
	order = createOrder("123-12", 4, "valid@mail", 1, MATHEMATICS, 1,
			COMPUTER_SCIENCE, "valid@mail", 11, 4, &result);
	ASSERT_TEST(result == ORDER_INVALID_PARAMETER);
	order = createOrder("123-25", 4, "valid@mail", 1, MATHEMATICS, 1,
			COMPUTER_SCIENCE, "valid@mail", 11, 4, &result);
	ASSERT_TEST(result == ORDER_INVALID_PARAMETER);
	return true;
}

static bool testOrderDestroy() {
	OrderResult result;
	Order order = createOrder("123-12", 4, "valid@mail", 1, MATHEMATICS, 1,
			COMPUTER_SCIENCE, "valid@mail", 1, 4, &result);
	ASSERT_TEST(order != NULL);
	ASSERT_TEST(result == ORDER_SUCCESS);
	destroyOrder(order);

	return true;
}

static bool testOrderCopyAndCompare() {
	OrderResult result;
	Order order = createOrder("123-12", 4, "valid@mail", 1, MATHEMATICS, 1,
			COMPUTER_SCIENCE, "valid@mail", 1, 4, &result);
	ASSERT_TEST(order != NULL);
	ASSERT_TEST(result == ORDER_SUCCESS);
	Order order1 = orderCopy(NULL);
	ASSERT_TEST(order1 == NULL);
	order1 = orderCopy(order);
	ASSERT_TEST(order1 != NULL);
	ASSERT_TEST(orderCompare(order1, order) == 0);
	ASSERT_TEST(orderCompareByFacultyList(order1, order) == 0);
	ASSERT_TEST(orderCompareByRoomIdList(order1, order) == 0);
	ASSERT_TEST(orderCompareByTimeList(order1, order) == 0);
	ASSERT_TEST(orderListCompareByCompany(order, "valid@mail"));
	ASSERT_TEST(orderListCompareByEscaperEmail(order, "valid@mail"));
	int key = 1;
	ASSERT_TEST(orderListCompareByRoomId(order, &key));
	destroyOrder(order1);
	destroyOrder(order);
	return true;
}

static bool testOrderGets() {
	OrderResult result;
	Order order = createOrder("123-12", 4, "valid@mail", 1, MATHEMATICS, 1,
			COMPUTER_SCIENCE, "valid@mail", 1, 4, &result);
	ASSERT_TEST(order != NULL);
	ASSERT_TEST(result == ORDER_SUCCESS);
	ASSERT_TEST(strcmp(getOrderEscaperEmail(order), "valid@mail") == 0);
	ASSERT_TEST(getOrderDay(order) == 123);
	ASSERT_TEST(getOrderHour(order) == 12);
	ASSERT_TEST(getOrderPrice(order) == 16);
	ASSERT_TEST(getOrderRoomFaculty(order));
	destroyOrder(order);
	return true;
}

static bool testListOfOrders(){
	List list = listCreate(orderCopyListFunction, freeOrderListFunction);
	ASSERT_TEST(list != NULL);
	OrderResult result;
	Order order = createOrder("123-12", 4, "valid@mail", 1, MATHEMATICS, 1,
			COMPUTER_SCIENCE, "valid@mail", 1, 4, &result);
	ASSERT_TEST(order != NULL);
	listInsertLast(list, order);
	destroyOrder(order);
	Order order1 = createOrder("123-12", 24, "valid@mail", 1, MATHEMATICS, 1,
						COMPUTER_SCIENCE, "valid@mail", 1, 4, &result);
	ASSERT_TEST(order1 != NULL);
	listInsertLast(list, order1);
	destroyOrder(order1);
	Order order2 = createOrder("123-12", 3, "valid@mail", 1, MATHEMATICS, 1,
			COMPUTER_SCIENCE, "valid@mail", 1, 4, &result);
	ASSERT_TEST(order2 != NULL);
	listInsertLast(list, order2);
	destroyOrder(order2);
	ASSERT_TEST(listGetSize(list) == 3);
	ASSERT_TEST(order2 != NULL);
	listDestroy(list);
	return true;
}
int main3(int argv, char** arc) {
	RUN_TEST(testOrderCreate);
	RUN_TEST(testOrderDestroy);
	RUN_TEST(testOrderCopyAndCompare);
	RUN_TEST(testOrderGets);
	RUN_TEST(testListOfOrders);
	return 0;
}
