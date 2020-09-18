/*
 * Engima.cpp
 *
 *  Created on: Jun 21, 2017
 *      Author: Noam
 */

#include "Enigma.h"

using std::endl;

namespace mtm {
namespace escaperoom {
Enigma::Enigma(const std::string& name, const Difficulty& difficulty,
		const int& num_of_elements, const set<string>& elements) {
	int size_set = elements.size();
	if (size_set != num_of_elements) {
		throw EnigmaIllegalSizeParamException();
	}
	this->name = name;
	this->difficulty = difficulty;
	this->num_of_elements = num_of_elements;
	this->elements = elements;
}

Enigma::Enigma(const std::string& name, const Difficulty& difficulty) :
		name(name), difficulty(difficulty), num_of_elements(0), elements() {
}

bool Enigma::operator==(const Enigma& enigma) const {
	return difficulty == enigma.difficulty && name == enigma.name;
}

bool Enigma::operator!=(const Enigma& enigma) const {
	return !(*this == enigma);
}
bool Enigma::operator<(const Enigma& enigma) const {
	return difficulty < enigma.difficulty;
}
bool Enigma::operator>(const Enigma& enigma) const {
	return enigma < *this;
}
bool Enigma::areEqualyComplex(const Enigma& enigma) const {
	return this->difficulty == enigma.difficulty
			&& this->num_of_elements == enigma.num_of_elements;
}

Difficulty Enigma::getDifficulty() const {
	return difficulty;
}

void Enigma::addElement(const string& element) {
	if (elements.insert(element).second){
		num_of_elements++;
	}
}

void Enigma::removeElement(const string& element) {
	if (num_of_elements == 0) {
		throw EnigmaNoElementsException();
	}
	if (elements.find(element) == elements.end()) {
		throw EnigmaElementNotFoundException();
	}
	elements.erase(element);
	this->num_of_elements--;
}
std::ostream& operator<<(std::ostream& output, const Enigma& enigma) {
	output << enigma.name << " (" << enigma.difficulty << ") ";
	output << enigma.num_of_elements;
	return output;
}

string Enigma::getName() const {
	return name;
}

set<string> Enigma::getAllElement() const{
	return elements;
}

}  // namespace escaperoom
}  // namespace mtm

