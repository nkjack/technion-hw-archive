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
#include <cmath>
#include "../Exceptions.h"

using std::string;
using std::to_string;
using mtm::ListExceptions::ElementNotFound;
using std::cout;
using std::endl;

void addStringsToList(List<string> &list, string type, int num_of_elements) {
	if (type == "names") {
		list.insert("noam");
		list.insert("tomer");
		list.insert("adva");
		list.insert("shaul");
		list.insert("yuval");
		list.insert("samuel");
		list.insert("itai");
	} else if (type == "tan") {
		for (int i = 1; i <= num_of_elements; ++i) {
			string s = string(std::to_string(tan(i)));
			list.insert(s);
		}
	} else {
		list.insert("toyota");
		list.insert("opel");
		list.insert("mercedes");
		list.insert("bmw");
		list.insert("kia");
		list.insert("susita");
		list.insert("audi");
	}
}

class EqualTo {
private:
	int target;
	string str;
public:
	EqualTo(int i) :
			target(i), str() {
	}
	EqualTo(string str) :
			target(), str(str) {
	}

	bool operator()(const int &i) const {
		return i == target;
	}
	bool operator()(const string& i) const {
		return i == str;
	}
};

/**
 * Use to add @param num_of_elem to List<double>
 * @param func "sin" or "cos", use to make different lists
 */
void addDoublesToList(List<double> &list, int amount_of_elements, string func) {
	if (func == "sin") {
		for (int i = 1; i <= amount_of_elements; ++i) {
			list.insert(sin(i));
		}
	} else if (func == "cos") {
		for (int i = 1; i <= amount_of_elements; ++i) {
			list.insert(cos(i));
		}
	} else {
		for (int i = 1; i <= amount_of_elements; ++i) {
			list.insert(tan(i));
		}
	}
}

bool constructorTest() {
	List<char> list_char;
	ASSERT_TRUE(list_char.getSize() == 0);
	List<string> list_string;
	ASSERT_TRUE(list_string.getSize() == 0);
	ASSERT_TRUE(list_string.begin() == list_string.end());
	List<double> list_double;
	ASSERT_TRUE(list_double.getSize() == 0);
	List<int> list_int;
	ASSERT_TRUE(list_int.getSize() == 0);
	ASSERT_TRUE(list_int.begin() == list_int.end());
	return true;
}

bool copyConstructorTest() {
	List<int> list_int;
	for (int i = 0; i < 16; ++i) {
		list_int.insert(i);
	}
	List<int> list_int_cp(list_int);
	ASSERT_TRUE(list_int == list_int_cp);
	List<int>::Iterator itr2 = list_int_cp.begin();
	for (List<int>::Iterator itr1 = list_int.begin(); itr1 != list_int.end();
			++itr1) {
		ASSERT_TRUE(*itr1 == *itr2);
		++itr2;
	}

	List<string> list_string;
	addStringsToList(list_string, "other", 0);
	List<string> list_string_cp(list_string);
	ASSERT_TRUE(list_string == list_string_cp);
	List<string>::Iterator it3 = list_string_cp.begin();
	for (List<string>::Iterator it4 = list_string.begin();
			it4 != list_string.end(); ++it4) {
		ASSERT_TRUE(*it3 == *it4);
		++it3;
	}
	ASSERT_TRUE(it3 == list_string_cp.end());
	it3 = list_string_cp.begin();
	list_string_cp.remove(it3);
	it3 = list_string_cp.begin();
	ASSERT_TRUE(*it3 != *list_string.begin());
	ASSERT_TRUE(*it3 == *++list_string.begin());

	return true;
}

bool assignOperandTest() {
	List<double> list_double1;
    list_double1 = list_double1;
	addDoublesToList(list_double1, 16, "cos");
	List<double> list_double2;
	addDoublesToList(list_double2, 16, "sin");
	list_double1 = list_double2;
	ASSERT_TRUE(list_double1 == list_double2);
	addDoublesToList(list_double1, 4, "tan");
	list_double1 = list_double2;
	ASSERT_TRUE(list_double1 == list_double2);
    list_double1 = list_double1;
	ASSERT_TRUE(list_double1 == list_double1);

	return true;
}

bool beginFunctionTest() {
	List<int> list_int;
	ASSERT_TRUE(list_int.begin() == list_int.end());
	ASSERT_NO_THROW(list_int.begin());
	list_int.insert(1);
	ASSERT_TRUE(*list_int.begin() == 1);
	ASSERT_THROWS(ElementNotFound, *list_int.end());

	List<string> list_string;
	addStringsToList(list_string, "names", 0);
	string result = "noam";
	ASSERT_TRUE(*(list_string.begin()) == result);
	ASSERT_THROWS(ElementNotFound, *list_string.end());

	return true;
}

bool insertFunctionTest() {
	/**
	 * int
	 */
	List<int> list_int;
	ASSERT_TRUE(list_int.getSize() == 0);
	list_int.insert(1, list_int.end());
	ASSERT_TRUE(list_int.getSize() == 1);
	ASSERT_TRUE(*list_int.begin() == 1);

	list_int.insert(2);
	ASSERT_TRUE(list_int.getSize() == 2);
	List<int>::Iterator it = list_int.begin();
	ASSERT_TRUE(*it == 1);
	ASSERT_TRUE(*++it == 2);

	list_int.insert(3, list_int.begin());
	it = --list_int.begin();
	ASSERT_TRUE(list_int.getSize() == 3);
	it = list_int.begin();
	ASSERT_TRUE(*list_int.begin() == 3);
	ASSERT_TRUE(*++it == 1);
	ASSERT_TRUE(*++it == 2);
	ASSERT_THROWS(ElementNotFound, *++it);

	it = list_int.begin();
	for (int j = 0; j < 2; ++j) {
		++it;
	}
	list_int.insert(4, it);
	ASSERT_TRUE(list_int.getSize() == 4);
	it = list_int.begin();
	for (int j = 0; j < 2; ++j) {
		++it;
	}
	ASSERT_TRUE(*it == 4);
	ASSERT_TRUE(*++it == 2);
	ASSERT_TRUE(*--(--it) == 1);
    ASSERT_THROWS(ElementNotFound, *----it);

    /**
     * string
     */
	List<string> list_string;
	ASSERT_TRUE(list_string.getSize() == 0);
	string s1 = "noam1";
	list_string.insert("noam1", list_string.end());

	ASSERT_TRUE(list_string.getSize() == 1);
	ASSERT_TRUE(*list_string.begin() == s1);

	string s2 = "noam2";
	list_string.insert(s2);
	ASSERT_TRUE(list_string.getSize() == 2);

	string s3 = "noam3";
	list_string.insert(s3, list_string.begin());
	ASSERT_TRUE(list_string.getSize() == 3);
	ASSERT_TRUE(*list_string.begin() == s3);

	List<string>::Iterator its = list_string.begin();
	for (int j = 0; j < 2; ++j) {
		++its;
	}
	string s4 = "noam4";
	list_string.insert(s4, its);
	ASSERT_TRUE(list_string.getSize() == 4);
	its = list_string.begin();
	for (int j = 0; j < 2; ++j) {
		++its;
	}
	ASSERT_TRUE(*its == s4);
	ASSERT_TRUE(*(++its) == s2);
	ASSERT_TRUE(*--(--its) == s1);
	ASSERT_TRUE(*its++ == s1);
	ASSERT_TRUE(*its == s4);
	ASSERT_TRUE(++++its == list_string.end());
	ASSERT_TRUE(list_string.begin() != its);
	List<string> big_list;
	ASSERT_THROWS(ElementNotFound, big_list.insert("s", list_string.begin()));
	addStringsToList(big_list, "tan", 600);
	ASSERT_TRUE(big_list.getSize() == 600);
	return true;
}

bool removeFunctionTest() {
	List<int> list_int;
	ASSERT_THROWS(ElementNotFound, list_int.remove(list_int.begin()));
	for (int i = 0; i < 10; ++i) {
		list_int.insert(i);
	}
	ASSERT_TRUE(list_int.getSize() == 10);
	list_int.remove(list_int.begin());
	ASSERT_TRUE(list_int.getSize() == 9);
	ASSERT_TRUE(*list_int.begin() == 1);
	List<int> list_int2;
	ASSERT_THROWS(ElementNotFound, list_int.remove(list_int2.begin()));
	list_int2.insert(2);
	ASSERT_THROWS(ElementNotFound, list_int.remove(list_int2.begin()));

	List<int> list;
	for (int l = 0; l < 200; ++l) {
		list.insert(l);
	}
	ASSERT_TRUE(list.getSize() == 200);
	for (int l = 0; l < 200; ++l) {
		list.remove(list.begin());
	}
	ASSERT_TRUE(list.getSize() == 0);

	List<double> list_double;
	for (double j = 0.5; j < 3.4; j += 0.5) {
		list_double.insert(j);
	}
	ASSERT_TRUE(list_double.getSize() == 6);
	List<double>::Iterator itd = list_double.begin();
	for (int k = 1; k <= 3; ++k) {
		itd++;
	}
	list_double.remove(itd);
	ASSERT_TRUE(list_double.getSize() == 5);
	itd = list_double.begin();
	for (int k = 2; k <= 3; ++k) {
		itd++;
	}
	ASSERT_TRUE(*itd == 1.5);
	ASSERT_TRUE(*++itd == 2.5);

	List<string> list_string;
	addStringsToList(list_string, "tan", 500);
	ASSERT_TRUE(list_string.getSize() == 500);
	list_string.sort(std::less<string>());
	for (int m = 0; m < 500; ++m) {
		list_string.remove(list_string.begin());
	}
	ASSERT_TRUE(list_string.getSize() == 0);
	ASSERT_TRUE(list_string.begin() == list_string.end());

	return true;
}

bool equalityOperandTest() {
	List<double> list_d1;
	addDoublesToList(list_d1, 1000, "cos");
	List<double> list_d2;
	addDoublesToList(list_d2, 1000, "cos");
	ASSERT_TRUE(list_d1 == list_d2);
	ASSERT_FALSE(list_d1 != list_d2);
	list_d2.insert(2.12);
	ASSERT_TRUE(list_d1 != list_d2);
	ASSERT_FALSE(list_d1 == list_d2);

	ASSERT_TRUE(list_d1 == list_d1);

	list_d1 = list_d2;
	ASSERT_TRUE(list_d1 == list_d2);
	list_d1.remove(list_d1.begin());
	ASSERT_TRUE(list_d1 != list_d2);

	List<string> list_s1;
	ASSERT_TRUE(list_s1 == list_s1);
	addStringsToList(list_s1, "other", 0);
	List<string> list_s2;
	addStringsToList(list_s2, "other", 0);
	ASSERT_TRUE(list_s1 == list_s2);
	List<string>::Iterator it = list_s1.begin();
	for (int i = 0; i < 3; ++i) {
		++it;
	}
	list_s1.remove(it);
	ASSERT_TRUE(list_s1 != list_s2);
	it = list_s1.begin();
	int i = 0;
	for (; i < 3; ++i) {
		++it;
	}
	string s = "bmw";
	list_s1.insert(s, it);
	ASSERT_TRUE(list_s1 == list_s2);

	return true;
}

bool findFunctionTest() {
	List<int> list_int;
	for (int i = 0; i < 10; ++i) {
		list_int.insert(i);
	}
	List<int>::Iterator it = list_int.find(EqualTo(3));
	ASSERT_EQUALS(3, *it);
	it = list_int.find(EqualTo(20));
	ASSERT_TRUE(it == list_int.end());

	List<string> list_string;
	List<string>::Iterator its = list_string.find(EqualTo("str1"));
	ASSERT_TRUE(its == list_string.end());
	string s1 = "noam1";
	string s2 = "noam2";
	string s3 = "noam3";
	list_string.insert(s1);
	list_string.insert(s2);
	list_string.insert(s1);
	list_string.insert(s3);
	list_string.insert(s2);
	list_string.insert(s1);
	its = list_string.find(EqualTo(s1));
	ASSERT_TRUE(its == list_string.begin());
	its = list_string.find(EqualTo(s2));
	ASSERT_TRUE(its == ++list_string.begin());
	its = list_string.find(EqualTo(s3));
	ASSERT_TRUE(its == ++++++list_string.begin());
	its = list_string.find(EqualTo("no"));
	ASSERT_TRUE(its == list_string.end());
	list_string.remove(++list_string.begin());
	its = list_string.find(EqualTo(s2));
	ASSERT_TRUE(its == ++++++list_string.begin());
	list_string.remove(++++++list_string.begin());
	ASSERT_TRUE(list_string.find(EqualTo(s2)) == list_string.end());

	return true;
}

bool sortFunctionTest() {
	List<double> list_double;
	addDoublesToList(list_double, 500, "cos");
	list_double.sort(std::less<double>());
	List<double>::Iterator it1 = list_double.begin();
	List<double>::Iterator it2 = it1;
	it2++;
	std::less<double> lessd;
	for (int j = 0; j < list_double.getSize() - 1; ++j) {
		ASSERT_TRUE(lessd(*it1, *it2));
		++it1;
		++it2;
	}

	List<string> list_string;
	addStringsToList(list_string, "names", 0);
	list_string.sort(std::less<string>());
	List<string>::Iterator its1 = list_string.begin();
	List<string>::Iterator its2 = its1;
	its2++;
	std::less_equal<string> lesss;
	for (int j = 0; j < list_string.getSize() - 1; ++j) {
		ASSERT_TRUE(lesss(*its1, *its2));
		++its1;
		++its2;
	}

	return true;
}

bool getSizeFunctionTest() {
	List<string> list_str;
	addStringsToList(list_str, "tan", 70);
	ASSERT_TRUE(list_str.getSize() == 70);
	for (int i = 0; i < 30; ++i) {
		list_str.remove(list_str.begin());
	}
	ASSERT_TRUE(list_str.getSize() == 40);
	addStringsToList(list_str, "tan", 200);
	ASSERT_TRUE(list_str.getSize() == 240);
	List<string> list_str_2 = list_str;
	ASSERT_TRUE(list_str_2.getSize() == 240);
	for(int i=0 ; i < 10; i++){
		list_str_2.remove(list_str_2.begin());
	}
	ASSERT_TRUE(list_str_2.getSize() == 230);
	ASSERT_TRUE(list_str.getSize() == 240);
	ASSERT_FALSE(list_str == list_str_2);
	return true;
}

bool dereferenceItrOperandTest() {
	List<int> list_int;
	ASSERT_THROWS(ElementNotFound, *list_int.end());
	List<string> list_s;
	addStringsToList(list_s, "tan", 123);
	List<string>::Iterator it = list_s.begin();
	int i = 1;
	for (; it != list_s.end(); ++it) {
		ASSERT_TRUE(*it == to_string(tan(i)));
		i++;
	}
	ASSERT_THROWS(ElementNotFound, *it);
	return true;
}

bool equalityOperandItrTest() {
	List<string> list1;
	ASSERT_TRUE(list1.begin() == list1.end());
	List<string> list2;
	ASSERT_FALSE(list1.begin() == list2.end());
	ASSERT_TRUE(list1.begin() != list2.end());
	addStringsToList(list1, "tan", 15);
	addStringsToList(list2, "tan", 30);
	List<string>::Iterator it1 = list1.begin();
	List<string>::Iterator it2 = list2.begin();
	ASSERT_FALSE(it1 == it2);
	ASSERT_FALSE(list1.begin() == ++it1);
	ASSERT_FALSE(list1.end() == list2.end());
	it2 = it1;
	ASSERT_TRUE(it1 == it2);
	return true;
}


int main_list() {
	RUN_TEST(constructorTest);
	RUN_TEST(copyConstructorTest);
	RUN_TEST(assignOperandTest);
	RUN_TEST(beginFunctionTest);
	RUN_TEST(insertFunctionTest);
	RUN_TEST(removeFunctionTest);
	RUN_TEST(equalityOperandTest);
	RUN_TEST(findFunctionTest);
	RUN_TEST(sortFunctionTest);
	RUN_TEST(getSizeFunctionTest);
	RUN_TEST(dereferenceItrOperandTest);
	RUN_TEST(equalityOperandItrTest);
	return 0;
}
