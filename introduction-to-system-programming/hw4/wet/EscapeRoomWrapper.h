#ifndef ESCAPEROOMWRAPPER_H
#define ESCAPEROOMWRAPPER_H

#include <string>
#include <iostream>
#include "EscapeRoom.h"
#include <vector>
#include "Enigma.h"
#include "Exceptions.h"

using std::vector;

namespace mtm {
namespace escaperoom {

class EscapeRoomWrapper {
	static const int MAX_TIME_DEFAULT = 60;
	static const int NUM_PARTICIPENTS_DEFAULT = 6;
//        bool equals(const EscapeRoomWrapper& other) const;
protected:
	EscapeRoom room; // protected in order to give the derived classes access.
	vector<Enigma> vector_enigma;

	// Prints the data of the Room in the following format:
	//
	//     "<name> (<maxTime>/<level>/<maxParticipants>)"
	//
	// @param output : the output stream to which the data is printed.
	// @param room : the room whose data is printed.
	friend std::ostream& operator<<(std::ostream& output,
			const EscapeRoomWrapper& room);

	/**
	 * this function get ostream reference for input and put the correct text
	 * for output that descriped in the operator<< function.
	 *
	 * @param std::ostream& the output the function write into
	 *
	 * @return void
	 */
	virtual void print(std::ostream& output) const;
public:
	// Constructs a new Escape Room with the specified data.
	//
	// @param name : the name of the escape room.
	// @param escapeTime : the maximal escape time allowed in the room.
	// @param level : the level of the escape room.
	// @param maxParticipants: the maximal participants allowed in the room.
	// The rest of the room's data is initialized as described in the exercise sheet.
	// @throws EscapeRoomMemoryProblemException in case of creation failure.
	EscapeRoomWrapper(char* name, const int& escapeTime, const int& level,
			const int& maxParticipants);

	// Constructs a new Escape Room with the specified data.
	//
	// @param name : the name of the enigma.
	// @param level : the level of the escape room.
	// The rest of the room's data is initialized as described in the exercise sheet.
	// @throws EscapeRoomMemoryProblemException in case of creation failure.
	EscapeRoomWrapper(char* name, const int& level);

	//copy constructor
	//
	//@param room : the room to be copied.
	//@throws EscapeRoomMemoryProblemException in case of creation failure.
	EscapeRoomWrapper(const EscapeRoomWrapper& room);

	//assignment operator
	//
	//@param room : the room to be assigned.
	EscapeRoomWrapper& operator=(const EscapeRoomWrapper& room);

	// Comparison operators for Escape Rooms. rooms are compared as described in
	// the exercise sheet.
	//
	// @param room : the right-hand side operand.
	virtual bool operator==(const EscapeRoomWrapper& room) const;
	virtual bool operator!=(const EscapeRoomWrapper& room) const;
	virtual bool operator<(const EscapeRoomWrapper& room) const;
	virtual bool operator>(const EscapeRoomWrapper& room) const;

	bool operator<=(const EscapeRoomWrapper& room) const = delete;
	bool operator>=(const EscapeRoomWrapper& room) const = delete;

	// return the level of the Escape Room.
	//
	int level() const;

	// the method changes the rate according to the rate given.
	//
	// @param newRate : the new rate accepted to the room.
	//@throws EscapeRoomIllegalRateException in case of illegal rate parameter.
	void rate(const int& newRate) const;

	// Destructor for EscapeRoomWrapper
	virtual ~EscapeRoomWrapper();

	//Function returns the name of the EscapeRoom.
	//
	std::string getName() const;

	char* getNameChar() const;
	//Function returns the rate of the EscapeRoom.
	//
	double getRate() const;

	//Function returns the maximum escape time of the EscapeRoom.
	//
	int getMaxTime() const;

	//Function returns the number of participants allowed in the EscapeRoom.
	//
	int getMaxParticipants() const;

	/**
	 * This function  get Enigma refernce for input and add it to the
	 * std::vector of Enigmas that the class has.
	 * This funcion add a copy of the inputed enigma.
	 *
	 * @param Enigma& the enigma to add into the room arsenal
	 * @return void
	 */
	void addEnigma(const Enigma& enigma);

	/**
	 * This funcion get Enigma& for input and remove the equal enigma from the
	 * vector of enigmas of the room.
	 *
	 * @param Enigma& the enigma which the function remove from the current room.
	 *
	 * @throws EscapeRoomNoEnigmasException if no Enigmas in this current room.
	 * @throws EscapeRoomEnigmaNotFoundException if the inputed enigma is not
	 * existed in this room
	 */
	void removeEnigma(const Enigma& enigma);

	/**
	 * This function return the hardest Enigma of this room. If there are few
	 * enigmas in the same level the function will return the first one in the
	 * vector of enigmas of the room.
	 *
	 * @return a copy of Enigma
	 * @throws  EscapeRoomNoEnigmasException if no enigmas exist in the room
	 */
	Enigma getHardestEnigma() const;

	/**
	 * This function return the refernce of the vector of enigmas of this room.
	 * could return an empty vector!
	 *
	 * @return vector<Enigma>& - the vector of enigmas of the room.
	 */
	vector<Enigma>& getAllEnigmas();

	const vector<Enigma>& getAllEnigmas() const;

	/**
	 * This function get Enigma& for input and return the iterator of the
	 * vector of this room that fits the same enigma.
	 */
	//vector<Enigma>::iterator
	vector<Enigma>::iterator getEnigma(const Enigma& enigma);
};

std::ostream& operator<<(std::ostream& output, const EscapeRoomWrapper& room);
} // end of namespace eascaperoom
} // end of namespace mtm

#endif //ESCAPEROOMWRAPPER_H
