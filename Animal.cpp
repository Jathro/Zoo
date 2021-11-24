/*
 * Animal.cpp
 *
 *  Created on: Dec 7, 2020
 *      Author: 0760848_snhu
 */

#include "Animal.h"

Animal::Animal(){
	Name = "UNKNOWN";
	TrackNum = 0;
}

Animal::~Animal() {
}

Animal::Animal(int trackNum, string name) {
	Name = name;
	TrackNum = trackNum;

}

bool Animal::CheckClass(string input) {
	if (input == "Mammal" || input == "Oviparous") {
		return true;
	}
	return false;
}
