/*
 * Animal.h
 *
 *  Created on: Dec 7, 2020
 *      Author: 0760848_snhu
 */

#ifndef ANIMAL_H_
#define ANIMAL_H_

#include <string>

using namespace std;

class Animal {
public:
	Animal();
	Animal(int trackNum, string name);
	virtual ~Animal();
	bool CheckClass(string input);
private:
	string Name;
	int TrackNum;
};

#endif /* ANIMAL_H_ */
