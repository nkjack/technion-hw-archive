#include "test_utilities.h"
#include "list_mtm1.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

static ListElement copyString(ListElement str) {
	assert(str);
	char* copy = malloc(strlen(str) + 1);
	return copy != NULL ? strcpy(copy, str) : NULL;
}

static void freeString(ListElement str) {
	free(str);
}

static ListElement copyInt(ListElement num) {
	assert(num);
	int* copy = malloc(sizeof(num));
	if (!copy) {
		return NULL;
	}
	copy = (int*) num;
	return copy;
}

static void freeInt(ListElement num) {
	free(num);
}

static bool isLongerThan(ListElement element, ListFilterKey number) {
	char* string = element;
	return strlen(string) > *(int*) number;
}

//static int closerTo(ListElement num1, ListElement num2) {
//	int distance1 = *(int*) num1 - 0;
//	int distance2 = *(int*) num2 - 0;
//	return distance1 - distance2;
//}

static bool isSmaller(ListElement element1, ListElement element2) {
	if (*(int*) element2 < *(int*) element1) {
		return true;
	}
	return false;
}

static void printListInt(List listOfStrings) {
	LIST_FOREACH(int*, integer, listOfStrings)
	{
		printf("%d ", *integer);
	}
}

static void printListStr(List listOfStrings) {
	LIST_FOREACH(char*, str, listOfStrings)
	{
		printf("%s ", str);
	}
}

static bool testListCreate() {
	ASSERT_TEST(listCreate(NULL,NULL) == NULL);
	ASSERT_TEST(listCreate(NULL,NULL) == NULL);
	ASSERT_TEST(listCreate(copyString,NULL) == NULL);
	ASSERT_TEST(listCreate(NULL,freeString) == NULL);

	return true;
}
static bool testListFilter() {
	char* a[5] = { "aaa", "bbb", "NI", "hello mister fish", "I" };
	List list = listCreate(copyString, freeString);
	for (int i = 0; i < 5; ++i) {
		listInsertFirst(list, a[i]);
	}
	int key = 5;
	List filtered = listFilter(list, isLongerThan, &key);
	ASSERT_TEST(listGetSize(filtered) == 1);
	ASSERT_TEST(strcmp(listGetFirst(filtered), a[3]) == 0);
	listDestroy(list);
	listDestroy(filtered);
	return true;
}
static bool testListCopy() {
	char* a[5] = { "noam", "is", "the", "king", "1234" };
	List list = listCreate(copyString, freeString);
	for (int i = 0; i < 5; ++i) {
		listInsertLast(list, a[i]);
	}
	List copy_list = listCopy(list);
	ASSERT_TEST(listGetSize(copy_list) == 5);
	return true;
}

static bool testListGetSize() {
	char* a[5] = { "aaa", "bbb", "NI", "hello mister fish", "I" };
	List list = listCreate(copyString, freeString);
	for (int i = 0; i < 5; ++i) {
		listInsertFirst(list, a[i]);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	listDestroy(list);
	return true;
}

static bool testListGetFirst() {
	char* a[5] = { "aaa", "bbb", "NI", "hello mister fish", "I" };
	List list = listCreate(copyString, freeString);
	for (int i = 0; i < 5; ++i) {
		listInsertLast(list, a[i]);
	}
	char* str = listGetFirst(list);
	ASSERT_TEST(strcmp(str, "aaa") == 0);
	return true;
}

static bool testListGetNext() {
	char* a[5] = { "aaa", "bbb", "NI", "hello mister fish", "I" };
	List list = listCreate(copyString, freeString);
	for (int i = 0; i < 5; ++i) {
		listInsertLast(list, a[i]);
	}
	char* str = (char*) listGetFirst(list);
	ASSERT_TEST(strcmp(str, "aaa") == 0);
	str = listGetNext(list);
	ASSERT_TEST(strcmp(str, "bbb") == 0);
	str = listGetNext(list);
	ASSERT_TEST(strcmp(str, "NI") == 0);
	str = listGetNext(list);
	ASSERT_TEST(strcmp(str, "hello mister fish") == 0);
	str = listGetNext(list);
	ASSERT_TEST(strcmp(str, "I") == 0);
	str = listGetNext(list);
	ASSERT_TEST(str == NULL);
	str = listGetNext(list);
	ASSERT_TEST(str == NULL);
	return true;
}

static bool testListInsertFirst() {
	char* a[5] = { "aaa", "bbb", "NI", "hello mister fish", "I" };
	List list = listCreate(copyString, freeString);
	for (int i = 4; i >= 0; --i) {
		listInsertFirst(list, a[i]);
	}
	char* str = listGetFirst(list);
	ASSERT_TEST(strcmp(str, "aaa") == 0);
	return true;
}

static bool testListInsertLast() {
	char* a[5] = { "aaa", "bbb", "NI", "hello mister fish", "I" };
	List list = listCreate(copyString, freeString);
	for (int i = 0; i < 5; ++i) {
		listInsertLast(list, a[i]);
	}
	char* str = listGetFirst(list);
	ASSERT_TEST(strcmp(str, "aaa") == 0);
	return true;
}

static bool testListInsertBeforeCurrent() {
	char* a[5] = { "aaa", "bbb", "NI", "hello mister fish", "I" };
	List list = listCreate(copyString, freeString);
	for (int i = 0; i < 5; ++i) {
		listInsertLast(list, a[i]);
	}
	char* str = listGetFirst(list);
	str = listGetNext(list);
	str = listGetNext(list);
	ASSERT_TEST(strcmp(str, "NI") == 0);
	listInsertBeforeCurrent(list, "Oora");
	str = listGetCurrent(list);
	ASSERT_TEST(strcmp(str, "NI") == 0);
	str = listGetFirst(list);
	str = listGetNext(list);
	str = listGetNext(list);
	ASSERT_TEST(strcmp(str, "Oora") == 0);
	return true;
}

static bool testListInsertAfterCurrent() {
	char* a[5] = { "aaa", "bbb", "NI", "hello mister fish", "I" };
	List list = listCreate(copyString, freeString);
	for (int i = 0; i < 5; ++i) {
		listInsertLast(list, a[i]);
	}
	ListResult result;
	result = listInsertBeforeCurrent(list, "Oora");
	ASSERT_TEST(result == LIST_INVALID_CURRENT);
	char* str = listGetFirst(list);
	str = listGetNext(list);
	str = listGetNext(list);
	ASSERT_TEST(strcmp(str, "NI") == 0);
	listInsertAfterCurrent(list, "Oora");
	str = listGetCurrent(list);
	ASSERT_TEST(strcmp(str, "NI") == 0);
	str = listGetNext(list);
	ASSERT_TEST(strcmp(str, "Oora") == 0);
	return true;
}

static bool testListRemoveCurrent() {
	char* a[5] = { "aaa", "bbb", "NI", "hello mister fish", "I" };
	List list = listCreate(copyString, freeString);
	for (int i = 0; i < 5; ++i) {
		listInsertLast(list, a[i]);
	}
	char* str = listGetFirst(list);
	str = listGetNext(list);
	str = listGetNext(list);
	ASSERT_TEST(strcmp(str, "NI") == 0);
	ListResult result = listRemoveCurrent(list);
	ASSERT_TEST(result == LIST_SUCCESS);
	ASSERT_TEST(listGetSize(list) == 4);
	str = listGetFirst(list);
	str = listGetNext(list);
	str = listGetNext(list);
	ASSERT_TEST(strcmp(str, "hello mister fish") == 0);
	return true;
}

static bool testListSort() {
	int a[10] = { 1, 5, 2, 8, 56, 9, 3, 3, 2, 10 };
	List list = listCreate(copyInt, freeInt);
	for (int i = 0; i < 10; ++i) {
		listInsertLast(list, &(a[i]));
	}
	printListInt(list);
	printf("\n");
	listSort(list, isSmaller);
	printListInt(list);
	printf("\n");
	return true;
}

static bool testListClear() {
	char* a[5] = { "aaa", "bbb", "NI", "hello mister fish", "I" };
	List list = listCreate(copyString, freeString);
	for (int i = 0; i < 5; ++i) {
		listInsertLast(list, a[i]);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	listClear(list);
	ASSERT_TEST(listGetSize(list) == 0);
	ASSERT_TEST(listGetFirst(list) == NULL);
	return true;
}

static bool testListDestroy() {
	char* a[5] = { "aaa", "bbb", "NI", "hello mister fish", "I" };
	List list = listCreate(copyString, freeString);
	for (int i = 0; i < 5; ++i) {
		listInsertLast(list, a[i]);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	listDestroy(list);
	ASSERT_TEST(list == NULL);
	return true;
}

int main1(int argv, char** arc) {
	RUN_TEST(testListCreate);
	RUN_TEST(testListFilter);
	RUN_TEST(testListCopy);
	RUN_TEST(testListGetSize);
	RUN_TEST(testListGetFirst);
	RUN_TEST(testListGetNext);
	RUN_TEST(testListInsertFirst);
	RUN_TEST(testListInsertLast);
	RUN_TEST(testListInsertBeforeCurrent);
	RUN_TEST(testListInsertAfterCurrent);
	RUN_TEST(testListRemoveCurrent);
	RUN_TEST(testListSort);
	RUN_TEST(testListClear);
	RUN_TEST(testListDestroy);
	return 0;
}

