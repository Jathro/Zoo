/*
 * Mammal.h
 *
 *  Created on: Dec 7, 2020
 *      Author: 0760848_snhu
 */

#ifndef MAMMAL_H_
#define MAMMAL_H_

#include "Animal.h"

class Mammal: public Animal {
public:
	Mammal();
	virtual ~Mammal();
	bool CheckClass(string input);
private:
	bool Nurse;
};

#endif /* MAMMAL_H_ */
