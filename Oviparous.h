/*
 * Oviparous.h
 *
 *  Created on: Dec 7, 2020
 *      Author: 0760848_snhu
 */

#ifndef OVIPAROUS_H_
#define OVIPAROUS_H_

#include "Animal.h"


class Oviparous: public Animal {
public:
	Oviparous();
	virtual ~Oviparous();
private:
	int NumberOfEggs;
};

#endif /* OVIPAROUS_H_ */
