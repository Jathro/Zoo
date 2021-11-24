/*
 * Mammal.cpp
 *
 *  Created on: Dec 7, 2020
 *      Author: 0760848_snhu
 */

#include "Mammal.h"

Mammal::Mammal() {
	// TODO Auto-generated constructor stub
}

Mammal::~Mammal() {
	// TODO Auto-generated destructor stub
}

bool Mammal::CheckClass(string input) {
	if (input == "Bat" || input == "Whale" || input == "SeaLion") {
		return true;
	}
	return false;
}
