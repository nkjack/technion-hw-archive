//
// Created by Samuel Panzieri on 6/21/2017.
//

#include "EscapeRoomWrapper.h"

using std::endl;

namespace mtm {
namespace escaperoom {

EscapeRoomWrapper::EscapeRoomWrapper(char *name, const int &escapeTime,
		const int &level, const int &maxParticipants) {
	room = escapeRoomCreate(name, escapeTime, maxParticipants, level);
	if (!room) {
		throw EscapeRoomMemoryProblemException();
	}
}

EscapeRoomWrapper::EscapeRoomWrapper(char *name, const int &level) {
	room = escapeRoomCreate(name, MAX_TIME_DEFAULT, NUM_PARTICIPENTS_DEFAULT,
			level);
	if (!room) {
		throw EscapeRoomMemoryProblemException();
	}
}

EscapeRoomWrapper::EscapeRoomWrapper(const EscapeRoomWrapper& room) {
	this->room = escapeRoomCopy(room.room);
	if (!this->room) {
		throw EscapeRoomMemoryProblemException();
	}
	this->vector_enigma = room.vector_enigma;
}

EscapeRoomWrapper& EscapeRoomWrapper::operator=(const EscapeRoomWrapper& room) {
	if (this == &room) {
		return *this;
	}
	EscapeRoom newroom = escapeRoomCopy(room.room);
	if (!newroom){
		throw EscapeRoomMemoryProblemException();
	}
	escapeRoomDestroy(this->room);
	this->room = newroom;
	this->vector_enigma = room.vector_enigma;
	return *this;
}

bool EscapeRoomWrapper::operator==(const EscapeRoomWrapper& room) const {
	return (areEqualRooms(this->room, room.room));
}
bool EscapeRoomWrapper::operator!=(const EscapeRoomWrapper& room) const {
	return (!areEqualRooms(this->room, room.room));
}
bool EscapeRoomWrapper::operator<(const EscapeRoomWrapper& room) const {
	return (isBiggerRoom(room.room, this->room));
}
bool EscapeRoomWrapper::operator>(const EscapeRoomWrapper& room) const {
	return room < *this;
}
int EscapeRoomWrapper::level() const {
	return (getLevel(this->room));
}

void EscapeRoomWrapper::rate(const int& newRate) const {
	if (newRate < 1 || newRate > 5) {
		throw EscapeRoomIllegalRateException();
	}
	updateRate(this->room, newRate);
}
EscapeRoomWrapper::~EscapeRoomWrapper() {
	escapeRoomDestroy(room);
}

void EscapeRoomWrapper::print(std::ostream& output) const {
	output << getName();
	output << " (" << getMaxTime() << "/" << level();
	output << "/" << getMaxParticipants() << ")";
}

std::ostream& operator<<(std::ostream& output, const EscapeRoomWrapper& room) {
	room.print(output);
	return output;
}

std::string EscapeRoomWrapper::getName() const {
	char* temp = roomGetName(room);
	string new_string(temp);
	free(temp);
	return new_string;
}

char* EscapeRoomWrapper::getNameChar() const{
	return roomGetName(room);
}
double EscapeRoomWrapper::getRate() const {
	return roomGetRate(room);
}
int EscapeRoomWrapper::getMaxTime() const {
	return roomGetMaxTime(room);
}
int EscapeRoomWrapper::getMaxParticipants() const {
	return roomGetMaxParticipants(room);
}

void EscapeRoomWrapper::addEnigma(const Enigma& enigma) {
	vector_enigma.push_back(enigma);
}

void EscapeRoomWrapper::removeEnigma(const Enigma& enigma) {
	int size = vector_enigma.size();
	if (size == 0) {
		throw EscapeRoomNoEnigmasException();
	}
	for (vector<Enigma>::iterator itr = vector_enigma.begin();
			itr != vector_enigma.end(); ++itr) {
		if (*itr == enigma) {
			vector_enigma.erase(itr);
			return;
		}
	}
	throw EscapeRoomEnigmaNotFoundException();
}

Enigma EscapeRoomWrapper::getHardestEnigma() const{
	int size = vector_enigma.size();
	if (size == 0) {
		throw EscapeRoomNoEnigmasException();
	}
	Enigma enigma_to_return = vector_enigma[0]; //first enigma
	for (Enigma enigma : vector_enigma) {
		if (enigma.getDifficulty() > enigma_to_return.getDifficulty()) {
			enigma_to_return = enigma;
		}
	}
	return enigma_to_return;
}

vector<Enigma>& EscapeRoomWrapper::getAllEnigmas() {
	return vector_enigma;
}

const vector<Enigma>& EscapeRoomWrapper::getAllEnigmas() const{
	return vector_enigma;
}

vector<Enigma>::iterator EscapeRoomWrapper::getEnigma(const Enigma& enigma) {
	vector<Enigma>::iterator itr = vector_enigma.begin();
	while (itr != vector_enigma.end()) {
		if (*itr == enigma) {
			return itr;
		}
		itr++;
	}
	throw EscapeRoomEnigmaNotFoundException();
}

}
}
