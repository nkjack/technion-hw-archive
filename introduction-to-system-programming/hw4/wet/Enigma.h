#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include <set>
#include "Exceptions.h"

using std::set;
using std::string;

namespace mtm {
namespace escaperoom {

typedef enum {
	EASY_ENIGMA, MEDIUM_ENIGMA, HARD_ENIGMA
} Difficulty;

class Enigma {
	string name;
	Difficulty difficulty;
	int num_of_elements;
	set<string> elements;
public:

	// Constructs a new Enigma with the specified data.
	//
	// @param name : the name of the enigma.
	// @param difficulty : the difficulty of the enigma.
	// @param numOfElements : the number of elements in the enigma.
	// @param elements : the set of string to add into the Enigma set of elements
	Enigma(const std::string& name, const Difficulty& difficulty,
			const int& num_of_elements, const set<string>& elements);

	/**
	 * Constructs a new Enigma with a default amount of elements to 0.
	 *
	 * @param name : the name of the enigma
	 * @param difficulty : the difficulty of the enigma
	 */
	Enigma(const std::string& name, const Difficulty& difficulty);
	//copy constructor
	//
	//@param enigma : the enigma to be copied.
	Enigma(const Enigma& enigma) = default;

	//assignment operator
	//
	//@param enigma : the enigma to be assigned.
	Enigma& operator=(const Enigma& enigma) = default;

	// Comparison operators for Enigmas. enigmas are compared as described in
	// the exercise sheet.
	//
	// @param enigma : the right-hand side operand.
	bool operator==(const Enigma& enigma) const;
	bool operator!=(const Enigma& enigma) const;
	bool operator<(const Enigma& enigma) const;
	bool operator>(const Enigma& enigma) const;

	bool operator<=(const Enigma& enigma) const = delete;
	bool operator>=(const Enigma& enigma) const = delete;

	// method returns true if both enigmas are equaly complex.
	//definition of equaly complex is described in the exercise sheet.
	//
	//@param enigma : the enigma being compared to.
	bool areEqualyComplex(const Enigma& enigma) const;

	// return the difficulty level of the enigma.
	//
	Difficulty getDifficulty() const;

	/**
	 * This function get a string element and add it into the set of elements
	 * of this current Enigma.
	 *
	 * @param element : the string element to insert into the Enigma
	 */
	void addElement(const string& element);

	/**
	 * This function get string& element for input and remove the same element
	 * from the set of elements of this Enigma.
	 *
	 * @param element : the element to remove from this enigma
	 * @throws EnigmaElementNotFoundException - if the enigma is no in this enigma
	 * @throws  EnigmaNoElementsException - if no elements in this enigma.
	 */
	void removeElement(const string& element);

	/**
	 * This function return a copy of the set of elements of this Enigma.
	 */
	set<string> getAllElement() const;

	// Prints the data of the Enigma in the following format:
	//
	//     "<name> (<Difficulty>) <number of items>"
	//
	// @param output : the output stream to which the data is printed.
	// @param enigma : the enigma whose data is printed.
	friend std::ostream& operator<<(std::ostream& output, const Enigma& enigma);

	~Enigma() = default;

	//Function returns the name of the enigma.
	//
	string getName() const;

};

std::ostream& operator<<(std::ostream& output, const Enigma& enigma);
} // end of namespace eascaperoom
} // end of namespace mtm

#endif //ENIGMA_H
