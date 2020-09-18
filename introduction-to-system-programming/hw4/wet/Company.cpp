#include "Company.h"

using std::endl;
using std::type_info;
using std::cout;

namespace mtm {
namespace escaperoom {

Company::Company(string name, string phone_number) :
		company_name(name), phone_num(phone_number), rooms() {
}

Company::Company(const Company& company) :
		rooms() {
	this->phone_num = company.phone_num;
	this->company_name = company.company_name;
	for (std::set<EscapeRoomWrapper*>::iterator itr = company.rooms.begin();
			itr != company.rooms.end(); itr++) {
		const ScaryRoom* scary_room = dynamic_cast<const ScaryRoom*>(*itr);
		const KidsRoom* kids_room = dynamic_cast<const KidsRoom*>(*itr);

		EscapeRoomWrapper* new_room;
		if (scary_room != nullptr) {
			char* name = scary_room->getNameChar();
			const int& time = scary_room->getMaxTime();
			const int& level = scary_room->level();
			const int& num_participents = scary_room->getMaxParticipants();
			const int& age_limit = scary_room->getAgeLimit();
			const int& num_scary_enigmas = scary_room->getNumOfScaryEnigmas();
			new_room = new ScaryRoom(name, time, level, num_participents,
					age_limit, num_scary_enigmas);
			vector<Enigma> temp_vec = (**itr).getAllEnigmas();
			for (vector<Enigma>::iterator itr = temp_vec.begin();
					itr != temp_vec.end(); itr++) {
				new_room->addEnigma(*itr);
			}
			free(name);
		} else if (kids_room != nullptr) {
			char* name = kids_room->getNameChar();
			const int& time = kids_room->getMaxTime();
			const int& level = kids_room->level();
			const int& num_participents = kids_room->getMaxParticipants();
			const int& age_limit = kids_room->getAgeLimit();
			new_room = new KidsRoom(name, time, level, num_participents,
					age_limit);
			vector<Enigma> temp_vec = (**itr).getAllEnigmas();
			for (vector<Enigma>::iterator itr = temp_vec.begin();
					itr != temp_vec.end(); itr++) {
				new_room->addEnigma(*itr);
			}
			free(name);
		} else {
			new_room = new EscapeRoomWrapper((**itr));
		}

		rooms.insert(new_room);
	}
}

Company& Company::operator=(const Company& company) {
	if (this == &company) {
		return *this;
	}
	this->company_name = company.company_name;
	this->phone_num = company.phone_num;
	deleteRoomsSet();
	for (std::set<EscapeRoomWrapper*>::iterator itr = company.rooms.begin();
			itr != company.rooms.end(); itr++) {
		const ScaryRoom* scary_room = dynamic_cast<const ScaryRoom*>(*itr);
		const KidsRoom* kids_room = dynamic_cast<const KidsRoom*>(*itr);

		EscapeRoomWrapper* new_room;
		if (scary_room != nullptr) {
			char* name = scary_room->getNameChar();
			const int& time = scary_room->getMaxTime();
			const int& level = scary_room->level();
			const int& num_participents = scary_room->getMaxParticipants();
			const int& age_limit = scary_room->getAgeLimit();
			const int& num_scary_enigmas = scary_room->getNumOfScaryEnigmas();
			new_room = new ScaryRoom(name, time, level, num_participents,
					age_limit, num_scary_enigmas);
			vector<Enigma> temp_vec = (**itr).getAllEnigmas();
			for (vector<Enigma>::iterator itr = temp_vec.begin();
					itr != temp_vec.end(); itr++) {
				new_room->addEnigma(*itr);
			}
			free(name);
		} else if (kids_room != nullptr) {
			char* name = kids_room->getNameChar();
			const int& time = kids_room->getMaxTime();
			const int& level = kids_room->level();
			const int& num_participents = kids_room->getMaxParticipants();
			const int& age_limit = kids_room->getAgeLimit();
			new_room = new KidsRoom(name, time, level, num_participents,
					age_limit);
			vector<Enigma> temp_vec = (**itr).getAllEnigmas();
			for (vector<Enigma>::iterator itr = temp_vec.begin();
					itr != temp_vec.end(); itr++) {
				new_room->addEnigma(*itr);
			}
			free(name);
		} else {
			new_room = new EscapeRoomWrapper((**itr));
		}

		rooms.insert(new_room);
	}
	return *this;
}

void Company::createRoom(char* name, const int& escapeTime, const int& level,
		const int& maxParticipants) {
	try {
		EscapeRoomWrapper *new_room = new EscapeRoomWrapper(name, escapeTime,
				level, maxParticipants);
		rooms.insert(new_room);
	} catch (const EscapeRoomMemoryProblemException& e) {
		throw CompanyMemoryProblemException();
	} catch (const std::bad_alloc& e) {
		throw CompanyMemoryProblemException();
	}
}
//Function creates a scary escape room using the parameters and adds the room created to the company.
//
// @param name : the name of the escape room.
// @param escapeTime : the maximal escape time allowed in the room.
// @param level : the level of the escape room.
// @param maxParticipants: the maximal participants allowed in the room.
// @param ageLimit : the age limit for the room.
// @param numOfScaryEnigmas : the number of scary enigmas in the room.
// @throws CompanyMemoryProblemException in case of room creation failure.
void Company::createScaryRoom(char* name, const int& escapeTime,
		const int& level, const int& maxParticipants, const int& ageLimit,
		const int& numOfScaryEnigmas) {
	try {
		EscapeRoomWrapper *new_room = new ScaryRoom(name, escapeTime, level,
				maxParticipants, ageLimit, numOfScaryEnigmas);
		rooms.insert(new_room);
	} catch (const std::bad_alloc& e) {
		throw CompanyMemoryProblemException();
	}
}

//Function creates a scary escape room using the parameters and adds the room created to the company.
//
// @param name : the name of the escape room.
// @param escapeTime : the maximal escape time allowed in the room.
// @param level : the level of the escape room.
// @param maxParticipants: the maximal participants allowed in the room.
// @param ageLimit : the age limit for the room.
// @throws CompanyMemoryProblemException in case of room creation failure.
void Company::createKidsRoom(char* name, const int& escapeTime,
		const int& level, const int& maxParticipants, const int& ageLimit) {
	try {
		EscapeRoomWrapper *new_room = new KidsRoom(name, escapeTime, level,
				maxParticipants, ageLimit);
		rooms.insert(new_room);
	} catch (const std::bad_alloc& e) {
		throw CompanyMemoryProblemException();
	}
}

//Function returns a set of all the rooms in the company.
//
set<EscapeRoomWrapper*> Company::getAllRooms() const {
	set<EscapeRoomWrapper*> to_return = this->rooms;
	return to_return;
}
//Function removes the room specified from the company.
//
// @param room : the room to be removed.
// @throws : CompanyRoomNotFoundException in case that room doesnt exist in company.
void Company::removeRoom(const EscapeRoomWrapper& room) {
	for (set<EscapeRoomWrapper*>::iterator itr = rooms.begin();
			itr != rooms.end(); itr++) {
		if ((**itr) == room) {
			delete *itr;
			rooms.erase(itr);
			return;
		}
	}
	throw CompanyRoomNotFoundException();
}

//Function adds the enigma to the room specified.
//
// @param room : the room to be updated.
// @param enigma : the enigma to be added.
// @throws : CompanyRoomNotFoundException in case that room doesnt exist in company.
void Company::addEnigma(const EscapeRoomWrapper& room, const Enigma& enigma) {
	for (set<EscapeRoomWrapper*>::iterator itr = rooms.begin();
			itr != rooms.end(); itr++) {
		if (**itr == room) {
			(**itr).addEnigma(enigma);
			return;
		}
	}
	throw CompanyRoomNotFoundException();
}

//Function removes the enigma from the room specified.
//
// @param room : the room to be updated.
// @param enigma : the enigma to be removed.
// @throws : CompanyRoomNotFoundException in case that room doesnt exist in company.
// @throws : CompanyRoomHasNoEnigmasException in case the room is empty.
// @throws : CompanyRoomEnigmaNotFoundException in case enigma doesnt exist in room.
void Company::removeEnigma(const EscapeRoomWrapper& room,
		const Enigma& enigma) {
	for (set<EscapeRoomWrapper*>::iterator itr = rooms.begin();
			itr != rooms.end(); itr++) {
		if (**itr == room) {
			try {
				(**itr).removeEnigma(enigma);
			} catch (const EscapeRoomNoEnigmasException&) {
				throw CompanyRoomHasNoEnigmasException();
			} catch (const EscapeRoomEnigmaNotFoundException&) {
				throw CompanyRoomEnigmaNotFoundException();
			}
			return;
		}
	}
	throw CompanyRoomNotFoundException();
}

//Function adds the item to the enigma from the room specified.
//
// @param room : the room to be updated.
// @param enigma : the enigma to be updated.
// @param element : the element to be added.
// @throws : CompanyRoomNotFoundException in case that room doesnt exist in company.
// @throws : CompanyRoomEnigmaNotFoundException in case enigma doesnt exist in room.
void Company::addItem(const EscapeRoomWrapper& room, const Enigma& enigma,
		const string& element) {
	for (set<EscapeRoomWrapper*>::iterator itr = rooms.begin();
			itr != rooms.end(); itr++) {
		if ((*(*itr)) == room) {
			try {
				(*((*itr)->getEnigma(enigma))).addElement(element);
			} catch (const EscapeRoomEnigmaNotFoundException&) {
				throw CompanyRoomEnigmaNotFoundException();
			}
			return;
		}
	}
	throw CompanyRoomNotFoundException();
}

//Function removes the item from the enigma from the room specified.
//
// @param room : the room to be updated.
// @param enigma : the enigma to be removed.
// @param element : the element to be removed.
// @throws : CompanyRoomNotFoundException in case that room doesnt exist in company.
// @throws : CompanyRoomEnigmaNotFoundException in case enigma doesnt exist in room.
// @throws : CompanyRoomEnigmaHasNoElementsException in case enigma has no elements;
// @throws : CompanyRoomEnigmaElementNotFoundException in case element doesnt exist in enigma.
void Company::removeItem(const EscapeRoomWrapper& room, const Enigma& enigma,
		const string& element) {
	for (set<EscapeRoomWrapper*>::iterator itr = rooms.begin();
			itr != rooms.end(); itr++) {
		if (**itr == room) {
			try {
				(*(*itr)->getEnigma(enigma)).removeElement(element);
			}
			catch (const EscapeRoomEnigmaNotFoundException&) {
				throw CompanyRoomEnigmaNotFoundException();
			}
			catch (const EnigmaNoElementsException&)
			{
				throw CompanyRoomEnigmaHasNoElementsException();
			}
			catch (const EnigmaElementNotFoundException&) {
				throw CompanyRoomEnigmaElementNotFoundException();
			}
			return;
		}
	}
	throw CompanyRoomNotFoundException();
}

//Function returns all the rooms in the specified type.
//
// @param: type : the type requested.
set<EscapeRoomWrapper*> Company::getAllRoomsByType(RoomType type) const {
	set<EscapeRoomWrapper*> set_to_return;
	for (set<EscapeRoomWrapper*>::iterator itr = rooms.begin();
			itr != rooms.end(); itr++) {
		const ScaryRoom* scary_room = dynamic_cast<const ScaryRoom*>(*itr);
		const KidsRoom* kids_room = dynamic_cast<const KidsRoom*>(*itr);
		if (type == SCARY_ROOM) {
			if (scary_room != nullptr) {
				set_to_return.insert(*itr);
			}
		} else if (type == KIDS_ROOM) {
			if (kids_room != nullptr) {
				set_to_return.insert(*itr);
			}
		} else if (type == BASE_ROOM) {
			if (scary_room == nullptr && kids_room == nullptr) {
				set_to_return.insert(*itr);
			}
		}
	}
	return set_to_return;
}

//Function returns the room with the specified name.
//
// @param: name : the name of the room requested.
// @throws: CompanyRoomNotFoundException if room doesnt exist.
EscapeRoomWrapper* Company::getRoomByName(const string& name) const {
	for (set<EscapeRoomWrapper*>::iterator itr = rooms.begin();
			itr != rooms.end(); itr++) {
		if ((**itr).getName() == name) {
			return *itr;
		}
	}
	throw CompanyRoomNotFoundException();
}
void Company::deleteRoomsSet() {
	set<EscapeRoomWrapper*>::iterator itr = rooms.begin();
	while (itr != rooms.end()) {
		delete *itr;
		itr++;
	}
	rooms.clear();
}
//Destructor
Company::~Company() {
	deleteRoomsSet();
}

bool Company::operator==(const Company& company) const {
	if ((company.company_name == company_name)
			&& (company.phone_num == phone_num)
			&& (company.rooms.size() == rooms.size())) {
		for (set<EscapeRoomWrapper*>::iterator itr1 = rooms.begin();
				itr1 != rooms.end(); itr1++) {
			bool temp_bool = false;
			for (set<EscapeRoomWrapper*>::iterator itr2 = company.rooms.begin();
					itr2 != company.rooms.end(); itr2++) {
				if ((**itr1) == (**itr2)) {
					temp_bool = true;
				}
			}
			if (temp_bool == false) {
				return false;
			}
		}
		return true;
	}
	return false;
}

bool Company::operator!=(const Company& company) const {
	return !((*this) == company);
}
std::ostream& operator<<(std::ostream& output, const Company& company) {
	output << company.company_name << " : " << company.phone_num << endl;
	set<EscapeRoomWrapper*> temp_set = company.rooms;
	for (set<EscapeRoomWrapper*>::iterator itr = temp_set.begin();
			itr != temp_set.end(); itr++) {
		output << (*(*itr)) << endl;
	}
	return output;
}

}
}
