/*
 * enigma_test.cpp
 *
 *  Created on: Jun 21, 2017
 *      Author: Noam
 */

#include "../mtmtest.h"
#include <assert.h>
#include "../Enigma.h"
#include <set>

using namespace mtm::escaperoom;
using mtm::escaperoom::Enigma;
using std::set;
using std::to_string;
void addStringsToSet(std::set<string>& set, int num_elements) {
	for (int i = 0; i < num_elements; i++) {
		set.insert(to_string(i));
	}
}

void enigmaConstructor() {
	set<string> set;
	addStringsToSet(set, 5);
	ASSERT_NO_THROW(Enigma("scary_enigma", EASY_ENIGMA, 5, set));
	Enigma enigma("scary_enigma", MEDIUM_ENIGMA, 5, set);
	Enigma enigma_2(enigma);
	ASSERT_EQUALS("scary_enigma", enigma_2.getName());
	ASSERT_EQUALS(MEDIUM_ENIGMA, enigma_2.getDifficulty());
	ASSERT_TRUE(enigma_2.areEqualyComplex(enigma));

	Enigma enigma_3 = enigma;
	ASSERT_EQUALS(enigma.getName(), enigma_3.getName());
	ASSERT_EQUALS(enigma.getDifficulty(), enigma_3.getDifficulty());
	ASSERT_TRUE(enigma_2.areEqualyComplex(enigma));
}

void enigmaOperatorsTests() {
	set<string> set11, set12, set13, set21;
	addStringsToSet(set11, 1);
	addStringsToSet(set12, 2);
	addStringsToSet(set13, 3);
	addStringsToSet(set21, 3);

	Enigma enigma_11("enigma1", EASY_ENIGMA, 1, set11);
	Enigma enigma_12("enigma1", EASY_ENIGMA, 2, set12);
	Enigma enigma_13("enigma1", MEDIUM_ENIGMA, 3, set13);
	Enigma enigma_21("enigma2", EASY_ENIGMA, 3, set21);
	ASSERT_TRUE(enigma_11 == enigma_12);
	ASSERT_FALSE(enigma_11 == enigma_13);
	ASSERT_FALSE(enigma_11 == enigma_21);
	ASSERT_TRUE(enigma_13 > enigma_11);
	ASSERT_TRUE(enigma_13 > enigma_21);
	ASSERT_TRUE(enigma_11 < enigma_13);
	ASSERT_TRUE(enigma_21 < enigma_13);
	ASSERT_TRUE(enigma_11 != enigma_21);
	ASSERT_TRUE(enigma_11 != enigma_13);
}

void getterTests() {
	set<string> set;
	addStringsToSet(set, 1);
	Enigma enigma("enigma1", EASY_ENIGMA, 1, set);
	ASSERT_EQUALS("enigma1", enigma.getName());
	ASSERT_EQUALS(EASY_ENIGMA, enigma.getDifficulty());
}

void areEqualyComplexTest() {
	set<string> set1, set2, set3, set4;
	addStringsToSet(set1, 2);
	addStringsToSet(set2, 2);
	addStringsToSet(set3, 2);
	addStringsToSet(set4, 4);
	Enigma enigma_1("enigma1", EASY_ENIGMA, 2, set1);
	Enigma enigma_2("enigma2", EASY_ENIGMA, 2, set2);
	Enigma enigma_3("enigma3", HARD_ENIGMA, 2, set3);
	Enigma enigma_4("enigma4", HARD_ENIGMA, 4, set4);
	ASSERT_TRUE(enigma_1.areEqualyComplex(enigma_2));
	ASSERT_FALSE(enigma_1.areEqualyComplex(enigma_3));
	ASSERT_FALSE(enigma_3.areEqualyComplex(enigma_4));
	ASSERT_FALSE(enigma_2.areEqualyComplex(enigma_4));
}

void addElementTest() {
	Enigma enigma("enigma1", EASY_ENIGMA);
	ASSERT_THROWS(EnigmaNoElementsException, enigma.removeElement("noam"));
	enigma.addElement("1");
	enigma.addElement("2");
	enigma.addElement("3");
	enigma.addElement("4");
	enigma.addElement("5");
	ASSERT_THROWS(EnigmaElementNotFoundException, enigma.removeElement("noam"));
	set<string> set_elements = enigma.getAllElement();
	set<string>::iterator itr = set_elements.begin();
	ASSERT_TRUE(*itr == "1");
	itr++;
	ASSERT_TRUE(*itr == "2");
	itr++;
	ASSERT_TRUE(*itr == "3");
	itr++;
	ASSERT_TRUE(*itr == "4");
	itr++;
	ASSERT_TRUE(*itr == "5");
	itr++;
	ASSERT_TRUE(itr == set_elements.end());

}
int main_enigma() {
	RUN_TEST(enigmaConstructor);
	RUN_TEST(enigmaOperatorsTests);
	RUN_TEST(getterTests);
	RUN_TEST(areEqualyComplexTest);
	RUN_TEST(addElementTest);
	return 0;
}
