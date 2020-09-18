#include "../EscapeRoomWrapper.h"
#include "../mtmtest.h"
#include <vector>

using namespace mtm::escaperoom;
using std::vector;

void wrapperCtor() {
	ASSERT_NO_THROW(EscapeRoomWrapper((char* )"ChanceTheWrapper", 6));
	EscapeRoomWrapper room1((char *) "ChanceTheWrapper", 60, 2, 3);
	ASSERT_EQUALS("ChanceTheWrapper", room1.getName());
	ASSERT_EQUALS(60, room1.getMaxTime());
	ASSERT_EQUALS(2, room1.level());
	ASSERT_EQUALS(3, room1.getMaxParticipants());
}

void wrapperCopyCtor() {
	EscapeRoomWrapper room1((char *) "bestRoom", 2);
	EscapeRoomWrapper room2(room1);
	ASSERT_EQUALS(room1.getName(), room2.getName());
	ASSERT_EQUALS(room1.level(), room2.level());
	ASSERT_EQUALS(room1.getMaxParticipants(), room2.getMaxParticipants());
	ASSERT_EQUALS(room1.getMaxTime(), room2.getMaxTime());
}

void wrapperOperators() {
	EscapeRoomWrapper room1((char *) "IDK", 2);
	EscapeRoomWrapper room2((char *) "BLA", 2);
	room2 = room1;
	ASSERT_TRUE(room1 == room2);
	ASSERT_FALSE(room1 > room2);
	ASSERT_FALSE(room1 < room2);
	ASSERT_NO_THROW(room1 = room1);
	EscapeRoomWrapper room3((char *) "PIZZA", 2, 3, 4);
	EscapeRoomWrapper room4((char *) "PIZZA", 6, 1, 4);
	ASSERT_TRUE(room3 == room4);

}

void wrapperGetTests() {
	EscapeRoomWrapper room1((char *) "IDK", 2, 3, 4);
	EscapeRoomWrapper room2((char *) "BLABLA", 3, 4, 5);
	ASSERT_EQUALS("IDK", room1.getName());
	ASSERT_EQUALS(2, room1.getMaxTime());
	ASSERT_EQUALS(5, room2.getMaxParticipants());
	ASSERT_EQUALS(4, room2.level());
}

void wrapperAddRemoveEnigma() {
	EscapeRoomWrapper room((char *) "noam is the king", 10);
	room.addEnigma(Enigma("enig1", MEDIUM_ENIGMA));
	room.addEnigma(Enigma("enig2", EASY_ENIGMA));
	room.addEnigma(Enigma("enig3", EASY_ENIGMA));
	vector<Enigma> result = room.getAllEnigmas();
	ASSERT_EQUALS(3, (int )result.size());
	room.removeEnigma(Enigma("enig1", MEDIUM_ENIGMA));
	result = room.getAllEnigmas();
	ASSERT_EQUALS(2, (int )result.size());
	ASSERT_EQUALS("enig2", result[0].getName());
	ASSERT_EQUALS("enig3", result[1].getName());
	ASSERT_THROWS(EscapeRoomEnigmaNotFoundException,
			room.removeEnigma(Enigma("enig1", MEDIUM_ENIGMA)));
	room.removeEnigma(Enigma("enig2", EASY_ENIGMA));
	room.removeEnigma(Enigma("enig3", EASY_ENIGMA));
	ASSERT_THROWS(EscapeRoomNoEnigmasException,
			room.removeEnigma(Enigma("enig1", MEDIUM_ENIGMA)));
}

void wrapperGetHardestEnigma() {
	EscapeRoomWrapper room((char *) "noam is the king", 10);
	ASSERT_THROWS(EscapeRoomNoEnigmasException, room.getHardestEnigma());
	Enigma enig1("enig1", EASY_ENIGMA);
	Enigma enig2("enig2", EASY_ENIGMA);
	Enigma enig3("enig3", MEDIUM_ENIGMA);
	Enigma enig4("enig4", EASY_ENIGMA);
	Enigma enig5("enig5", MEDIUM_ENIGMA);
	room.addEnigma(enig1);
	room.addEnigma(enig2);
	room.addEnigma(enig3);
	room.addEnigma(enig4);
	room.addEnigma(enig5);
	Enigma hardest_enig = room.getHardestEnigma();
	ASSERT_EQUALS("enig3", hardest_enig.getName());
	room.removeEnigma(enig3);
	hardest_enig = room.getHardestEnigma();
	ASSERT_EQUALS("enig5", hardest_enig.getName());
	Enigma enig6("enig6", HARD_ENIGMA);
	room.addEnigma(enig6);
	hardest_enig = room.getHardestEnigma();
	ASSERT_EQUALS("enig6", hardest_enig.getName());
}

void wrapperRateFunctions() {
	EscapeRoomWrapper room((char *) "noam is the king", 10);
	room.rate(2);
	ASSERT_THROWS(EscapeRoomIllegalRateException, room.rate(6));
	ASSERT_THROWS(EscapeRoomIllegalRateException, room.rate(-2));
	room.rate(3);
	room.rate(4);
	ASSERT_EQUALS(3, room.getRate());
}

void getAllEnigmaFunction() {
	EscapeRoomWrapper room((char *) "room", 10);
	room.addEnigma(Enigma("enigma1", EASY_ENIGMA));
	room.addEnigma(Enigma("enigma2", EASY_ENIGMA));
	room.addEnigma(Enigma("enigma3", EASY_ENIGMA));
	room.addEnigma(Enigma("enigma4", EASY_ENIGMA));
	vector<Enigma>& temp_vec = room.getAllEnigmas();
	temp_vec[0].addElement("element");
	temp_vec = room.getAllEnigmas();
	ASSERT_NO_THROW(temp_vec[0].removeElement("element"));
	for (int i = 0; i < 4; i++) {
		ASSERT_TRUE(temp_vec[i].getDifficulty() == EASY_ENIGMA);
	}
}

void getEnigmaFunction() {
	EscapeRoomWrapper room((char *) "room", 10);
	Enigma enigma1("enigma1", EASY_ENIGMA);
	Enigma enigma2("enigma2", EASY_ENIGMA);
	Enigma enigma3("enigma3", EASY_ENIGMA);
	Enigma enigma4("enigma4", EASY_ENIGMA);
	room.addEnigma(Enigma("enigma1", EASY_ENIGMA));
	room.addEnigma(Enigma("enigma2", EASY_ENIGMA));
	room.addEnigma(Enigma("enigma3", EASY_ENIGMA));
	room.addEnigma(Enigma("enigma4", EASY_ENIGMA));
	vector<Enigma>::iterator itr = room.getEnigma(
			Enigma("enigma2", EASY_ENIGMA));
	ASSERT_TRUE(*itr == enigma2);
	itr++;
	ASSERT_NO_THROW(room.removeEnigma(enigma1));
	ASSERT_NO_THROW(room.removeEnigma(enigma2));
	ASSERT_NO_THROW(room.removeEnigma(enigma3));
	ASSERT_NO_THROW(room.removeEnigma(enigma4));
	room.addEnigma(enigma1);
	room.addEnigma(enigma2);
	room.addEnigma(enigma3);
	room.addEnigma(enigma4);
	itr = room.getEnigma(enigma1);
	ASSERT_TRUE(*itr == enigma1);
	itr++;
	ASSERT_TRUE(*itr == enigma2);
	itr++;
	ASSERT_TRUE(*itr == enigma3);
	itr++;
	ASSERT_TRUE(*itr == enigma4);
}
int main_wrapper() {
	RUN_TEST(wrapperCtor);
	RUN_TEST(wrapperCopyCtor);
	RUN_TEST(wrapperOperators);
	RUN_TEST(wrapperGetTests);
	RUN_TEST(wrapperAddRemoveEnigma);
	RUN_TEST(wrapperGetHardestEnigma);
	RUN_TEST(wrapperRateFunctions);
	RUN_TEST(getAllEnigmaFunction);
	RUN_TEST(getEnigmaFunction);
	return 0;
}
