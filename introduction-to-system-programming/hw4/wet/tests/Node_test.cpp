/*
 * list_test.cpp
 *
 *  Created on: Jun 24, 2017
 *      Author: Noam
 */
#include "../mtmtest.h"
#include <assert.h>
#include "../list.h"
#include <iostream>
#include <string>

using std::string;

void nodeTestInt() {
	Node<int> node_int1(23);
	Node<int> node_int2(59);
	ASSERT_EQUALS(23, *node_int1);
	ASSERT_EQUALS(59, *node_int2);
	ASSERT_FALSE(node_int1 == node_int2);
	node_int1 = node_int2;
	ASSERT_EQUALS(59, *node_int1);
	ASSERT_EQUALS(59, *node_int2);
	ASSERT_TRUE(node_int1 == node_int2);
}

void nodeTestString(){
	Node<string> node_str1("noam");
	Node<string> node_str2("a");
	Node<string> node_str3("meleh");
	ASSERT_EQUALS("noam", *node_str1);
	ASSERT_FALSE(node_str1 == node_str2);
	node_str3 = node_str1;
	ASSERT_TRUE(node_str1 == node_str3);
	ASSERT_TRUE(node_str3 == node_str1);
	ASSERT_EQUALS("noam",*node_str3);

	Node<string> node_null;
	ASSERT_FALSE(node_str1 == node_null);
}

int main_node() {
	RUN_TEST(nodeTestInt);
	RUN_TEST(nodeTestString);
	return 0;
}



