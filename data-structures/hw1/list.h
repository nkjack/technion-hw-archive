/*
 * list.h
 *
 *  Created on: Jun 21, 2017
 *      Author: Noam
 */

#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include <assert.h>

using mtm::ListExceptions::ElementNotFound;

template<class T> class List;

template<class T>
class List;
/**
 * NODE CLASS ***********************************************
 */
template<class T>
class Node {
private:
	T data;
	Node<T>* next;
	Node<T>* prev;
	friend class List<T>;
public:
	/**
	 * Node Constructor, initialize data with its default constructor, and set
	 * next and prev into nullptr.
	 */
	Node();
	/**
	 * Node Constructor, get T element for input, and set into data. next and
	 * prev set to nullptr
	 */
	Node(T element);
	/**
	 * Copy Constructor, get node for input, and copy its data, while setting
	 * next and prev to points the same pointers as the inputed node.
	 *
	 * @param node : the node to copy
	 */
	Node(const Node& node);
	~Node() = default;
	/**
	 * Assignment operator. copy the data itself and assign the next and prev
	 * to point the same pointers that the inputed node is,
	 *
	 * @param node : the node to assign
	 */
	Node<T>& operator=(const Node<T>& node);
	/**
	 * Operator ==, is checking if the inputed node is equal to the current one.
	 * Two nodes are equal if their data are equal.
	 */
	bool operator==(const Node<T>& node) const;
	/**
	 * Dereference operator. return a copy of the data of the node.
	 */
	const T operator*() const;
};

/**
 * LIST CLASS *********************************************
 */
template<class T>
class List {
public:
	/**
	 * Default Constructor for the list. Create two pointers of Dummy Nodes,
	 * First node and Last Node. Those Nodes are useful in-order to implement
	 * the list and are not visible to the user. Moreover, the constructor set
	 * the size of the list to 0.
	 */
	List();
	/**
	 * Copy constructor for the List. Create a new List, and insert a copy of
	 * each element from the inputed list to the current list.
	 */
	List(const List& list);
	/**
	 * The Destructor clear the list, deleting all of the nodes that allocated.
	 * Also the destructor delete the First_node and Last_node, the dummies
	 * nodes.
	 */
	~List();
	/**
	 * Assigning operator, get List for input. This operator overloading clear
	 * the current list, and insert a copy of all the elements of the inputed
	 * list. It also updated the size of the list.
	 */
	List<T>& operator=(const List<T>& list);
	/**
	 * check if the two lists are equal. Two lists are equal if they have the
	 * same elements in the same order, and the list are in the same size.
	 */
	bool operator==(const List<T>& list) const;
	bool operator!=(const List<T>& list) const;

	/**
	 * Iterator of the list. each iterator is uniqe to each list.
	 */
	class Iterator;
	/**
	 * 	Return a iterator of the list to the first node of the list. If the
	 * 	list is empty a end() iterator will return.
	 */
	Iterator begin() const;
	/**
	 * Return a iterator of the list to the end of the list. The iterator that
	 * returns is not pointing to any node of the elements in the list.
	 */
	Iterator end() const;

	/**
	 * This function get data and iterator for input, and insert a new node
	 * to the list before the inputed iterator, with the inputed data.
	 * If the iterator is end(), than the new node will insert to the end of
	 * the list.
	 *
	 * @param data - the data to initialize the new node with
	 * @param iterator - the iterator to indicate the position of the list where
	 * 			the new node will be inserted.
	 * @throws - ListException::ElementNotFound if the iterator is pointing
	 * 				to another List.
	 */
	void insert(const T& data, Iterator iterator);
	/**
	 * This function insert a new Node with the inputed data to the end of the
	 * list. This function uses the insert function above with the Iterator
	 * of the end() of the list.
	 */
	void insert(const T& data);
	/**
	 * This function get iterator for input and remove the node that the iterator
	 * point on from the list.
	 *
	 * @throws ListException::ElementNotFound - if the iterator is of other list
	 * or the iterator is not pointing into an element inside the list.
	 */
	void remove(Iterator iterator);

	/**
	 * This function Finds a node inside the list according to a Function Object
	 * Predicate. The first Node of the list that returns true to the Predicate
	 * function will be returned as an iterator.
	 *
	 * If no element returns true with predicate, than the function will return
	 * end()
	 */
	template<class Predicate>
	Iterator find(const Predicate& predicate);

	/**
	 * This function Sort the list according to the Compare function object
	 * that is getting for input.
	 *
	 * This sort function uses a simple bubble sort.
	 */
	template<class Compare>
	void sort(const Compare& compare);
	/**
	 * return the size of the list.
	 */
	int getSize();

private:
	int size;
	Node<T> *first_node;
	Node<T> *last_node;
	void clear();
	void swap(Node<T>* node_1, Node<T>* node_2);
};

/**
 * ITERATOR CLASS *********************************************
 */
template<class T>
class List<T>::Iterator {
	Node<T>* ptr;
	const List<T>* list;
	friend class List<T> ;
	/**
	 * constructor for the Iterator. this constructor gets pointer to node,
	 * and pointer to a const list.
	 *
	 * @param node* - the node that the iterator point into.
	 * @param list* - the list which the iterator belongs to
	 */
	Iterator(Node<T>* node, const List<T>* list) {
		ptr = node;
		this->list = list;
	}
public:
	/**
	 * Copy Constructor, get Iterator for input and set the ptr of the iterator
	 * to point into the same node, and also the pointer to the list to point
	 * into the same list.
	 *
	 * @param other - the iterator which the function copies its variables.
	 */
	Iterator(const Iterator& other) {
		ptr = other.ptr;
		list = other.list;
	}
	/** no allocating in the iterator*/
	~Iterator() = default;
	/** assign pointers to each others*/
	Iterator& operator=(const Iterator&) = default;

	/**
	 * dereference operator will return the data of the node that the iterator
	 * is pointing to.
	 * @throws ListException::ElementNotFound - if the iterator is pointing
	 * to the end of the list.
	 */
	T& operator*();
	/**
	 * The ++ operator can't advance the iterator if it points to the last
	 * element of the list.
	 */
	Iterator& operator++();
	Iterator operator++(int);
	/**
	 * This -- operator can't decrease the iterator if is points to the first
	 * element of the list.
	 */
	Iterator& operator--();
	Iterator operator--(int);
	/**
	 * Two Iterators are equal if they points to the same Nodes of the Same list.
	 */
	bool operator==(const Iterator& iterator) const {
		return ptr == iterator.ptr;
	}
	bool operator!=(const Iterator& iterator) const {
		return ptr != iterator.ptr;
	}
};

/**
 * NODE IMPLEMENTATION ####################################
 */

template<class T>
Node<T>::Node() :
		data(T()), next(nullptr), prev(nullptr) {
}
template<class T>
Node<T>::Node(T element) {
	data = element;
	next = nullptr;
	prev = nullptr;
}

template<class T>
Node<T>::Node(const Node<T>& node) :
		next(node.next), prev(node.prev), data(node.data) {
}

template<class T>
Node<T>& Node<T>::operator=(const Node<T>& node) {
	if (this == &node) {
		return *this;
	}
	data = node.data;
	next = node.next;
	prev = node.prev;
	return *this;
}
template<class T>
const T Node<T>::operator*() const {
	return data;
}
template<class T>
bool Node<T>::operator==(const Node<T>& node) const {
	return node.data == this->data;
}

/**
 * ITERATOR IMPLEMENTATION #######################################
 */

template<class T>
T& List<T>::Iterator::operator*() {
	if (ptr == list->first_node || ptr == list->last_node) {
		throw ElementNotFound();
	}
	return ptr->data;
}
template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
	if (ptr == list->last_node) {
		return *this;
	}
	ptr = ptr->next;
	return *this;
}
template<class T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
	Iterator result = *this;
	++*this;
	return result;
}
template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator--() {
	if (ptr == list->first_node) {
		return *this;
	}
	ptr = ptr->prev;
	return *this;
}
template<class T>
typename List<T>::Iterator List<T>::Iterator::operator--(int) {
	Iterator result = *this;
	--*this;
	return result;
}

/**
 * LIST IMPLEMENTATION
 */
/**
 * Public section
 */
template<class T>
List<T>::List() :
		size(0) {
	last_node = new Node<T>();
	first_node = new Node<T>();
	first_node->next = last_node;
	last_node->prev = first_node;
}

template<class T>
List<T>::List(const List& list) :
		size(0) {
	last_node = new Node<T>();
	first_node = new Node<T>();
	first_node->next = last_node;
	last_node->prev = first_node;
	for (List<T>::Iterator i = list.begin(); i != list.end(); ++i) {
		insert(*i);
	}

}
template<class T>
List<T>::~List() {
	clear();
	delete first_node;
	delete last_node;
}
template<class T>
List<T>& List<T>::operator=(const List<T>& list) {
	if (this == &list) {
		return *this;
	}
	clear();
	for (typename List<T>::Iterator i = list.begin(); i != list.end(); ++i) {
		insert(*i);
	}
	size = list.size;
	return *this;
}

template<class T>
typename List<T>::Iterator List<T>::begin() const {
	if (size == 0) {
		return end();
	}
	return List<T>::Iterator(first_node->next, this);
}
template<class T>
typename List<T>::Iterator List<T>::end() const {
	return List<T>::Iterator(last_node, this);
}
template<class T>
void List<T>::insert(const T& data, Iterator iterator) {
	if (iterator.list != this) {
		throw ElementNotFound();
	}
	Node<T>* temp_prev = iterator.ptr;
	temp_prev = temp_prev->prev;

	Node<T>* new_node = new Node<T>(data);
	new_node->next = iterator.ptr;
	new_node->prev = temp_prev;

	temp_prev->next = new_node;
	Node<T>* new_itr = iterator.ptr;
	new_itr->prev = new_node;
	iterator = end();
	size++;
}

template<class T>
void List<T>::insert(const T& data) {
	List<T>::Iterator itr = end();
	insert(data, itr);
}

template<class T>
void List<T>::remove(Iterator iterator) {
	if (size == 0 || iterator == end() || iterator.list != this) {
		throw ElementNotFound();
	}
	Node<T>* temp = iterator.ptr;
	Node<T>* temp_prev = temp->prev;
	Node<T>* temp_next = temp->next;
	temp_prev->next = temp_next;
	temp_next->prev = temp_prev;
	delete temp;
	size--;
}

template<class T>
template<class Predicate>
typename List<T>::Iterator List<T>::find(const Predicate& predicate) {
	for (typename List<T>::Iterator i = this->begin(); i != this->end(); i++) {
		if (predicate(*i)) {
			return i;
		}
	}
	return end();
}

template<class T>
template<typename Compare>
void List<T>::sort(const Compare& compare) {
	for (List<T>::Iterator i = begin(); i != end(); i++) {
		for (List<T>::Iterator j = i; j != end(); j++) {
			if (!compare(*i, *j)) {
				swap(i.ptr, j.ptr);
			}
		}
	}
}
template<class T>
int List<T>::getSize() {
	return size;
}

/**
 * Private Section
 */
template<class T>
void List<T>::clear() {
	List<T>::Iterator iterator = begin();
	while (size != 0) {
		remove(iterator);
		iterator = begin();
	}
}

template<class T>
void List<T>::swap(Node<T>* node_1, Node<T>* node_2) {
	assert(node_1 != nullptr && node_2 != nullptr);
	T temp = node_1->data;
	node_1->data = node_2->data;
	node_2->data = temp;
}

template<class T>
bool List<T>::operator==(const List& list) const {
	List<T>::Iterator itr_1 = begin();
	List<T>::Iterator itr_2 = list.begin();
	if (size != list.size) {
		return false;
	}
	while ((itr_1 != end()) || (itr_2 != list.end())) {
		if (*itr_1 != *itr_2) {
			return false;
		}
		itr_1++;
		itr_2++;
	}
	return true;
}
template<class T>
bool List<T>::operator!=(const List& list) const {
	return !(*this == list);
}

#endif /* LIST_H_ */
