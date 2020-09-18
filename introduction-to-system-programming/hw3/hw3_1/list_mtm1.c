/*
 * list_mtm1.c
 *
 *  Created on: May 20, 2017
 *      Author: Noam
 */
#include <stdlib.h>
#include "list_mtm1.h"
#include <assert.h>
#include <stdbool.h>

typedef struct list_node* Node;

struct list_node {
	ListElement l_element;
	Node next;
};

struct list_t {
	Node list_head;
	int itr_position;
	Node itr_node;
	int size;
	CopyListElement copy_func;
	FreeListElement free_func;
	CompareListElements compare_func;
};

/**
 * STATIC FUNCTIONS
 */

/**
 * add element to the end of the linked list, if a problem of memory allocating
 * will arise, than this function will destroy all the list.
 *
 * @param list The list to add the element into the end of it
 * @param element The element to add into the end of the list
 *
 * @return
 * 		LIST_OUT_OF_MEMORY - if problem with malloc
 *		LIST_SUCCESS - if the element added successfully
 */
static ListResult addLastOrDestroy(List list, ListElement element) {
	ListResult result = listInsertLast(list, element);
	if (result == LIST_OUT_OF_MEMORY) {
		listDestroy(list);
	}
	return result;
}

/**
 * Add an entire list to another list from the end.
 *
 * @param new_list The list which the function will add the elements into.
 * @param list the list which the function will take it elements and add it
 * 		into the new_list/
 *
 * @return
 * 		LIST_OUT_OF_MEMORY - if problem with malloc
 *		LIST_SUCCESS - if the elements added successfully
 */
static ListResult addAllLastOrDestroy(List new_list, List list) {
	Node current = list->list_head->next;
	while (current != NULL) {
		if (addLastOrDestroy(new_list, current->l_element)
				== LIST_OUT_OF_MEMORY) {
			return LIST_OUT_OF_MEMORY;
		}
		current = current->next;
	}
	return LIST_SUCCESS;
}

/**
 * create a new Node in order to insert it to the List datatype.
 *
 * @param element The element which to assign in to the Node.
 * @return
 * NUll - if any problem such as allocate memory
 * Node - with the assigned element.
 */
static Node createNode(ListElement element) {
	Node node = malloc(sizeof(*node));
	if (!node) {
		return NULL;
	}
	node->l_element = element;
	node->next = NULL;
	return node;
}

/**
 * swap the value of the ListElement inside the nodes in the places place_1
 * and place_2 from the list of the input.
 *
 * @param list The list which the function will fine the 2 Nodes in the places.
 * @param node_1 the first node which the function change its value.
 * @param node_2 the second node which the function change its value.
 */
static void swapNodes(List list, Node node_1, Node node_2) {
	assert(list != NULL);
	assert(node_1 != NULL && node_2 != NULL);
	ListElement temp = node_1->l_element;
	node_1->l_element = node_2->l_element;
	node_2->l_element = temp;
}
/**
 * IMPLEMENT OF LIST_MTM1.H FUNCTIONS
 */
List listCreate(CopyListElement copyElement, FreeListElement freeElement) {
	if (!copyElement || !freeElement) {
		return NULL;
	}
	List list = malloc(sizeof(*list));
	if (list == NULL) {
		return NULL;
	}
//	list->list_head = createNode(NULL);
//	if (list->list_head == NULL) {
//		free(list);
//		return NULL;
//	}
	Node head_dummy = createNode(NULL);
	list->list_head = head_dummy;
	list->itr_position = 0;
	list->itr_node = NULL;
	list->size = 0;
	list->copy_func = copyElement;
	list->free_func = freeElement;
	return list;
}

List listCopy(List list) {
	if (!list) {
		return NULL;
	}
	assert(list->copy_func && list->free_func);
	List new_list = listCreate(list->copy_func, list->free_func);
	if (addAllLastOrDestroy(new_list, list) == LIST_OUT_OF_MEMORY) {
		return NULL;
	}
	new_list->itr_position = list->itr_position;
	Node new_itr = new_list->list_head;
	for (int i = 0; i < new_list->itr_position; i++) {
		new_itr = new_itr->next;
	}
	new_list->itr_node = new_itr;
	new_list->size = list->size;
	return new_list;
}
int listGetSize(List list) {
	if (!list) {
		return -1;
	}
	return list->size;
}
ListElement listGetFirst(List list) {
	if (!list) {
		return NULL;
	}
	if (list->list_head->next == NULL) {
		return NULL;
	}
	list->itr_position = 1;
	list->itr_node = list->list_head->next;
	return list->itr_node->l_element;
}
ListElement listGetNext(List list) {
	if (!list) {
		return NULL;
	}
	if (list->itr_node == NULL) {
		return NULL;
	}
	list->itr_node = list->itr_node->next;
	list->itr_position += 1;
	if (list->itr_node == NULL) {
		list->itr_position = 0;
		return NULL;
	}
	return list->itr_node->l_element;
}
ListElement listGetCurrent(List list) {
	if (!list) {
		return NULL;
	}
	if (list->itr_node == NULL) {
		return NULL;
	}
	assert(list->itr_node != NULL);
	return list->itr_node->l_element;
}

ListResult listInsertFirst(List list, ListElement element) {
	if (!list) {
		return LIST_NULL_ARGUMENT;
	}
	assert(element);
	ListElement new_element = list->copy_func(element);
	if (!new_element) {
		return LIST_OUT_OF_MEMORY;
	}
	Node node_to_add = createNode(new_element);
	if (!node_to_add) {
		return LIST_OUT_OF_MEMORY;
	}
	Node current_nodes = list->list_head->next;
	node_to_add->next = current_nodes;
	list->list_head->next = node_to_add;
	list->size += 1;
	if (list->itr_node != NULL) {
		list->itr_position += 1;
	}
	return LIST_SUCCESS;
}
ListResult listInsertLast(List list, ListElement element) {
	if (!list) {
		return LIST_NULL_ARGUMENT;
	}
	assert(element != NULL);
	ListElement new_element = list->copy_func(element);
	if (!new_element) {
		return LIST_OUT_OF_MEMORY;
	}
	Node current = list->list_head;
	Node node_to_add = createNode(new_element);
	if (!node_to_add) {
		return LIST_OUT_OF_MEMORY;
	}
	if (!current->next) {
		list->list_head->next = node_to_add;
	} else {
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = node_to_add;
	}
	list->size += 1;
	return LIST_SUCCESS;
}
ListResult listInsertBeforeCurrent(List list, ListElement element) {
	if (!list) {
		return LIST_NULL_ARGUMENT;
	}
	if (!list->itr_node) {
		return LIST_INVALID_CURRENT;
	}
	if (list->itr_position == 1) {
		ListResult result = listInsertFirst(list, element);
		return result;
	}
	Node before_current_node = list->list_head->next;
	Node current_node = before_current_node->next;
	assert(current_node != NULL && before_current_node != NULL);
	for (int i = 2; i < list->itr_position; i++) {
		current_node = current_node->next;
		before_current_node = before_current_node->next;
	}
	assert(current_node != NULL && before_current_node != NULL);
	Node new_node = createNode(element);
	if (!new_node) {
		return LIST_OUT_OF_MEMORY;
	}
	new_node->next = current_node;
	before_current_node->next = new_node;
	list->itr_position += 1;
	list->size += 1;
	return LIST_SUCCESS;
}
ListResult listInsertAfterCurrent(List list, ListElement element) {
	if (!list) {
		return LIST_NULL_ARGUMENT;
	}
	if (!list->itr_node) {
		return LIST_INVALID_CURRENT;
	}
	if (list->itr_position == list->size) {
		return listInsertLast(list, element);
	}
	Node current_node = list->list_head->next;
	Node after_current_node = current_node->next;
	assert(current_node != NULL && after_current_node != NULL);
	for (int i = 1; i < list->itr_position; i++) {
		current_node = current_node->next;
		after_current_node = after_current_node->next;
	}
	assert(current_node != NULL && after_current_node != NULL);
	Node new_node = createNode(element);
	if (!new_node) {
		return LIST_OUT_OF_MEMORY;
	}
	new_node->next = after_current_node;
	current_node->next = new_node;
	list->size += 1;
	return LIST_SUCCESS;
}
ListResult listRemoveCurrent(List list) {
	if (!list) {
		return LIST_NULL_ARGUMENT;
	}
	if (!list->itr_node) {
		return LIST_INVALID_CURRENT;
	}

	Node ptr_node = list->list_head;
	for (int i = 1; i < list->itr_position; i++) {
		ptr_node = ptr_node->next;
	}
	ptr_node->next = list->itr_node->next;
	list->free_func(list->itr_node->l_element);
	free(list->itr_node);
	list->itr_node = NULL;
	list->itr_position = 0;
	list->size -= 1;
	return LIST_SUCCESS;
}
ListResult listSort(List list, CompareListElements compareElement) {
	if (!list || !compareElement) {
		return LIST_NULL_ARGUMENT;
	}
	if (list->size < 2) {
		return LIST_SUCCESS;
	}
	Node node_i = list->list_head->next;
	Node node_j = list->list_head->next;
	for (int i = 1; i < list->size; i++) {
		node_j = node_i->next;
		for (int j = i; j < list->size; j++) {
			if (compareElement(node_i->l_element, node_j->l_element) > 0) {
				swapNodes(list, node_i, node_j);
			}
			node_j = node_j->next;
		}
		node_i = node_i->next;
	}
	Node itr_ptr = list->list_head;
	for (int i = 0; i < list->itr_position; i++) {
		itr_ptr = itr_ptr->next;
	}
	list->itr_node = itr_ptr;
	return LIST_SUCCESS;
}
List listFilter(List list, FilterListElement filterElement, ListFilterKey key) {
	if (!list || !filterElement) {
		return NULL;
	}
	List filter_list = listCreate(list->copy_func, list->free_func);
	for (Node ptr = list->list_head; ptr != NULL; ptr = ptr->next) {
		if (ptr->l_element != NULL && filterElement(ptr->l_element, key)) {
			ListResult result = listInsertLast(filter_list, ptr->l_element);
			if (result != LIST_SUCCESS) {
				listDestroy(filter_list); //TODO
				return NULL;
			}
		}
	}
	return filter_list;
}
ListResult listClear(List list) {
	if (!list){
		return LIST_NULL_ARGUMENT;
	}
	if (!list->list_head->next){
		return LIST_SUCCESS;
	}
	Node node_to_free = list->list_head->next;
	for (Node ptr = node_to_free->next ; ptr != NULL; ptr = ptr->next) {
		list->free_func(node_to_free->l_element);
		free(node_to_free);
		node_to_free = ptr;
	}
	list->itr_position = 0;
	list->size = 0;
	list->itr_node = NULL;
	list->list_head->next = NULL;
	return LIST_SUCCESS;
}

void listDestroy(List list) {
	if (!list) {
		return;
	}
	ListResult result = listClear(list);
	assert(result == LIST_SUCCESS);
	free(list->list_head);
	free(list);//
}

