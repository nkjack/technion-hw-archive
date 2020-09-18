#include "../Company.h"
#include "../mtmtest.h"
#include "../Exceptions.h"
#include <assert.h>

using namespace mtm::escaperoom;
using std::vector;
using std::set;
using std::cout;
using std::endl;

void CtorTest() {
	ASSERT_NO_THROW(Company("apple", "05043434"));
	Company newComp("apple", "05043434");
	Company newComp1("apple", "05043434");
	ASSERT_EQUALS(newComp, newComp1);
}

void copyTest() {
	Company comp("pakapaka", "0000000");
	Company comp2(comp);
	ASSERT_EQUALS(comp, comp2);
	EscapeRoomWrapper room((char*) "room1", 60, 10, 6);
	ScaryRoom scary_room((char*) "room1", 60, 10, 6, 18, 999);
	ASSERT_NO_THROW(comp.createRoom((char* )"room1", 60, 10, 6));
	ASSERT_FALSE(comp == comp2);
	ASSERT_NO_THROW(comp.removeRoom(room));
	ASSERT_TRUE(comp == comp2);
	ASSERT_NO_THROW(comp2.createScaryRoom((char* )"room1", 60, 10, 6, 18, 999));
	ASSERT_FALSE(comp == comp2);
	ASSERT_NO_THROW(comp.createRoom((char* )"room1", 60, 10, 6));
	ASSERT_TRUE(comp == comp2);
}

void operatorsTest() {
	Company comp1("comp1", "111111");
	Company comp2("comp2", "222222");
	ASSERT_TRUE(comp1 != comp2);
	comp2 = comp1;
	ASSERT_EQUALS(comp2, comp1);
	ASSERT_TRUE(comp2 == comp1);
	comp1.createRoom((char*) "room1", 60, 10, 6);
	comp2.createScaryRoom((char*) "room1", 60, 10, 6, 18, 999);
	ASSERT_TRUE(comp2 == comp1);
	comp1.createRoom((char*) "room1", 60, 10, 6);
	comp1.createRoom((char*) "room2", 60, 10, 6);
	comp1.createRoom((char*) "room3", 60, 10, 6);
	ASSERT_FALSE(comp2 == comp1);
	comp1 = comp2;
	ASSERT_TRUE(comp2 == comp1);
	ASSERT_TRUE(comp1 == comp2);
	ASSERT_NO_THROW(
			comp2.removeRoom(EscapeRoomWrapper((char* )"room1", 60, 10, 6)));
	ASSERT_FALSE(comp2 == comp1);
}

void createRoomTest() {
	Company noRooms("test", "4536782");
	ASSERT_NO_THROW(noRooms.createRoom((char * ) "name1", 4, 3, 4));
	ASSERT_EQUALS(noRooms.getAllRooms().size(), 1);
	ASSERT_NO_THROW(noRooms.createRoom((char * ) "name2", 3, 4, 2));
	ASSERT_EQUALS(noRooms.getAllRooms().size(), 2);
	EscapeRoomWrapper *lastAdded = *(++(noRooms.getAllRooms().begin()));
	string last_name = lastAdded->getName();
	ASSERT_TRUE("name2" == last_name || "name1" == last_name);
	int last_time = lastAdded->getMaxTime();
	ASSERT_TRUE(3 == last_time || 4 == last_time);
	Company comp1("comp1", "111111");
	Company comp2("comp1", "111111");
	comp1.createRoom((char*) "room", 60, 10, 6);
	comp1.createScaryRoom((char*) "scary", 60, 10, 6, 18, 999);
	comp1.createKidsRoom((char*) "kids", 60, 10, 6, 18);
	comp2.createRoom((char*) "room", 60, 10, 6);
	comp2.createScaryRoom((char*) "scary", 60, 10, 6, 18, 999);
	comp2.createKidsRoom((char*) "kids", 60, 10, 6, 18);
	ASSERT_EQUALS(comp1, comp2);
}

void kidsAndScaryRoomTest() {
	Company noRooms("test", "4536782");
	ASSERT_NO_THROW(noRooms.createKidsRoom((char * ) "kids", 56, 2, 3, 3));
	ASSERT_NO_THROW(noRooms.createScaryRoom((char * ) "scary", 55, 4, 2, 4, 4));
	EscapeRoomWrapper *lastAdded = *(++(noRooms.getAllRooms().begin()));
	string last_name = lastAdded->getName();
	ASSERT_TRUE("scary" == last_name || last_name == "kids");
	int lastLevel = (*((noRooms.getAllRooms().begin())))->level();
	ASSERT_TRUE(2 == lastLevel || lastLevel == 4);
}

void getAllRoomsTest() {
	Company newComp("test", "3456");
	EscapeRoomWrapper first((char *) "1st", 4, 3, 3);
	EscapeRoomWrapper second((char *) "2nd", 4, 3, 3);
	EscapeRoomWrapper third((char *) "3rd", 4, 3, 3);
	EscapeRoomWrapper fourth((char *) "4th", 4, 3, 3);
	ASSERT_NO_THROW(newComp.createRoom((char * ) "1st", 4, 3, 3));
	ASSERT_NO_THROW(newComp.createRoom((char * ) "2nd", 4, 3, 3));
	ASSERT_NO_THROW(newComp.createRoom((char * ) "3rd", 4, 3, 3));
	ASSERT_NO_THROW(newComp.createRoom((char * ) "4th", 4, 3, 3));
	set<EscapeRoomWrapper *> received = newComp.getAllRooms();
	set<EscapeRoomWrapper *>::iterator itr = received.begin();
	ASSERT_TRUE(
			(**itr) == first || (**itr) == second || (**itr) == third
					|| (**itr) == fourth);
	itr++;
	ASSERT_TRUE(
			(**itr) == first || (**itr) == second || (**itr) == third
					|| (**itr) == fourth);
	itr++;
	ASSERT_TRUE(
			(**itr) == first || (**itr) == second || (**itr) == third
					|| (**itr) == fourth);
	itr++;
	ASSERT_TRUE(
			(**itr) == first || (**itr) == second || (**itr) == third
					|| (**itr) == fourth);
}

void removeRoomTest() {
	Company company("c1", "1234");
	ASSERT_NO_THROW(company.createRoom((char * ) "r1", 60, 2, 2));
	ASSERT_NO_THROW(company.createRoom((char * ) "r2", 60, 3, 4));
	ASSERT_NO_THROW(company.createRoom((char * ) "r3", 60, 5, 6));
	ASSERT_NO_THROW(company.createKidsRoom((char * ) "r4", 60, 2, 2, 7));
	ASSERT_NO_THROW(company.createScaryRoom((char * ) "r5", 60, 2, 2, 11, 20));
	ASSERT_NO_THROW(
			company.removeRoom(EscapeRoomWrapper((char* )"r1", 60, 2, 2)));
	ASSERT_THROWS(CompanyRoomNotFoundException,
			company.removeRoom(EscapeRoomWrapper((char* )"r1", 60, 2, 2)));
	ASSERT_NO_THROW(
			company.removeRoom(ScaryRoom((char * )"r5", 60, 2, 2, 11, 20)));
	ASSERT_THROWS(CompanyRoomNotFoundException,
			company.removeRoom(ScaryRoom((char * )"r5", 60, 2, 2, 11, 20)));

	Company comp("dummy", "34251");
	EscapeRoomWrapper new_room((char *) "name", 4, 4, 4);
	ASSERT_THROWS(CompanyRoomNotFoundException, comp.removeRoom(new_room));
	ASSERT_NO_THROW(comp.createRoom((char * ) "name", 4, 4, 4));
	ASSERT_NO_THROW(comp.removeRoom(new_room));
	ASSERT_THROWS(CompanyRoomNotFoundException, comp.removeRoom(new_room));

	ASSERT_NO_THROW(comp.createRoom((char * ) "room", 60, 9, 6));
	ASSERT_NO_THROW(comp.createScaryRoom((char * ) "scary", 50, 9, 6, 18, 9));
	ASSERT_NO_THROW(comp.createKidsRoom((char * ) "kids", 40, 9, 6, 18));
	ASSERT_TRUE((int )comp.getAllRooms().size() == 3);

	ASSERT_THROWS(CompanyRoomNotFoundException,
			comp.removeRoom(ScaryRoom((char * ) "scary", 50, 4, 6, 18, 9)));
	ASSERT_NO_THROW(
			comp.removeRoom(ScaryRoom((char * ) "scary", 50, 9, 6, 18, 9)));
	ASSERT_THROWS(CompanyRoomNotFoundException,
			comp.removeRoom(ScaryRoom((char * ) "scary", 50, 9, 6, 18, 9)));

	ASSERT_NO_THROW(
			comp.removeRoom(EscapeRoomWrapper((char* )"room", 60, 9, 6)));
	ASSERT_THROWS(CompanyRoomNotFoundException,
			comp.removeRoom(EscapeRoomWrapper((char* )"room", 60, 9, 6)));

	ASSERT_NO_THROW(
			comp.removeRoom(EscapeRoomWrapper((char* )"kids", 40, 9, 6)));
	ASSERT_THROWS(CompanyRoomNotFoundException,
			comp.removeRoom(EscapeRoomWrapper((char* )"kids", 40, 9, 6)));
	ASSERT_TRUE((int )comp.getAllRooms().size() == 0);

}

void enigmaTests() {
	Company new_comp("rue", "34435");
	Enigma new_enigma("name", EASY_ENIGMA);
	EscapeRoomWrapper newRoom((char *) "name", 4, 4, 4);
	ASSERT_THROWS(CompanyRoomNotFoundException,
			new_comp.removeEnigma(newRoom, new_enigma));
	ASSERT_NO_THROW(new_comp.createRoom((char * ) "name", 4, 4, 4));
	ASSERT_THROWS(CompanyRoomHasNoEnigmasException,
			new_comp.removeEnigma(newRoom, new_enigma));
	ASSERT_NO_THROW(new_comp.addEnigma(newRoom, new_enigma));
	Enigma enigma2("anothername", HARD_ENIGMA);
	ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,
			new_comp.removeEnigma(newRoom, enigma2));
}

void itemTests1() {
	Company company("c1", "1234");
	company.createRoom((char *) "r1", 60, 2, 2);
	EscapeRoomWrapper room1((char *) "r1", 60, 2, 2);
	EscapeRoomWrapper room2((char *) "r2", 60, 2, 2);
	Enigma enigma1("e1", EASY_ENIGMA);
	Enigma enigma2("e2", HARD_ENIGMA);

	company.addEnigma(room1, enigma1);
	ASSERT_NO_THROW(company.addItem(room1, enigma1, "x"));
	ASSERT_NO_THROW(company.addItem(room1, enigma1, "y"));
	ASSERT_NO_THROW(company.addItem(room1, enigma1, "z"));
	ASSERT_NO_THROW(company.removeItem(room1, enigma1, "z"));
	ASSERT_NO_THROW(company.removeItem(room1, enigma1, "y"));
	ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,
			company.addItem(room1, enigma2, "x"));
	ASSERT_THROWS(CompanyRoomNotFoundException,
			company.addItem(room2, enigma1, "x"));
	ASSERT_THROWS(CompanyRoomNotFoundException,
			company.removeItem(room2, enigma1, "x"));
	ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,
			company.removeItem(room1, enigma2, "x"));
	ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException,
			company.removeItem(room1, enigma1, "y"));
	ASSERT_NO_THROW(company.removeItem(room1, enigma1, "x"));

}
void itemTests2() {
	Company comp("rue", "34435");
	Enigma enigma("enigma", EASY_ENIGMA);
	Enigma enigma2("enigma2", HARD_ENIGMA);
	EscapeRoomWrapper room((char *) "name", 4, 4, 4);
	EscapeRoomWrapper room2((char *) "anothername", 4, 4, 4);
	ASSERT_THROWS(CompanyRoomNotFoundException,
			comp.addItem(room, enigma, "firstEnigma"));
	ASSERT_NO_THROW(comp.createRoom((char * ) "name", 4, 4, 4));
	ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,
			comp.addItem(room, enigma, "firstEnigma"));
	ASSERT_NO_THROW(comp.addEnigma(room, enigma));
	ASSERT_NO_THROW(comp.addItem(room, enigma, "firstEnigma"));

	ASSERT_THROWS(CompanyRoomNotFoundException,
			comp.removeItem(room2, enigma, "firstEnigma"));
	ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,
			comp.removeItem(room, enigma2, "firstEnigma"));
	ASSERT_NO_THROW(comp.addEnigma(room, enigma2));
	ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException,
			comp.removeItem(room, enigma2, "firstEnigma"));
	ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException,
			comp.removeItem(room, enigma, "stam"));
	ASSERT_NO_THROW(comp.removeItem(room, enigma, "firstEnigma"));
}

void getRoomsTests() {
	Company comp("rue", "34435");
	EscapeRoomWrapper first((char *) "1st", 4, 3, 3);
	EscapeRoomWrapper second((char *) "2nd", 4, 3, 3);
	EscapeRoomWrapper scaryRoom((char *) "scaryroom", 3, 4, 3);
	EscapeRoomWrapper secondscary((char *) "scary2", 20, 10, 10);
	EscapeRoomWrapper kidsRoom((char *) "kidsRoom", 40, 20, 5);
	EscapeRoomWrapper secondkids((char *) "kidsRoom2", 30, 20, 5);
	ASSERT_NO_THROW(comp.createRoom((char * ) "1st", 4, 3, 3));
	ASSERT_NO_THROW(comp.createRoom((char * ) "2nd", 4, 3, 3));
	ASSERT_NO_THROW(comp.createScaryRoom((char * ) "scaryroom", 3, 4, 3, 2, 1));
	ASSERT_NO_THROW(comp.createScaryRoom((char * ) "scary2", 20, 10, 10, 1, 1));
	ASSERT_NO_THROW(comp.createKidsRoom((char * ) "kidsRoom", 40, 20, 5, 2));
	ASSERT_NO_THROW(comp.createKidsRoom((char * ) "kidsRoom2", 30, 20, 5, 0));
	ASSERT_THROWS(CompanyRoomNotFoundException, comp.getRoomByName("ababa"));
	EscapeRoomWrapper *found = comp.getRoomByName("1st");
	ASSERT_TRUE(*found == first);
	set<EscapeRoomWrapper *> received = comp.getAllRoomsByType(BASE_ROOM);
	set<EscapeRoomWrapper *>::iterator itr = received.begin();

	ASSERT_TRUE((**itr) == first || (**itr == second));
	itr++;
	ASSERT_TRUE((**itr) == first || (**itr == second));
	itr++;
	ASSERT_TRUE(itr == received.end());
	set<EscapeRoomWrapper *> received2 = comp.getAllRoomsByType(SCARY_ROOM);
	set<EscapeRoomWrapper *>::iterator itr2 = received2.begin();
	ASSERT_TRUE((**itr2) == scaryRoom || (**itr2 == secondscary));
	++itr2;
	ASSERT_TRUE((**itr2) == secondscary || (**itr2 == scaryRoom));
	++itr2;
	ASSERT_TRUE(itr2 == received2.end());
	set<EscapeRoomWrapper *> received3 = comp.getAllRoomsByType(KIDS_ROOM);
	set<EscapeRoomWrapper *>::iterator itr3 = received3.begin();
	ASSERT_TRUE((**itr3) == kidsRoom || (**itr3 == secondkids));
	ASSERT_NO_THROW((**itr3).addEnigma(Enigma("noam", HARD_ENIGMA)));
	++itr3;
	ASSERT_TRUE((**itr3) == kidsRoom || (**itr3 == secondkids));
	ASSERT_NO_THROW((**itr3).addEnigma(Enigma("noam", HARD_ENIGMA)));
	++itr3;
	ASSERT_TRUE(itr3 == received3.end());
	itr3 = received3.begin();
	ASSERT_NO_THROW((**itr3).removeEnigma(Enigma("noam", HARD_ENIGMA)));

}

int main_company() {
	RUN_TEST(CtorTest);
	RUN_TEST(copyTest);
	RUN_TEST(operatorsTest);
	RUN_TEST(createRoomTest);
	RUN_TEST(kidsAndScaryRoomTest);
	RUN_TEST(getAllRoomsTest);
	RUN_TEST(removeRoomTest);
	RUN_TEST(enigmaTests);
	RUN_TEST(itemTests1);
	RUN_TEST(itemTests2);
	RUN_TEST(getRoomsTests);
	return 1;
}
