/*
 * main.cpp
 *
 *  Created on: 04.05.2014
 *      Author: K
 */
#include "../h/Stein.h"
#include <iostream>

int main(void){

	Stein st;
	Stein stein = new Stein(GELB);
	cout << stein << "\n";
	cout << st;
	delete stein;
	return 0;
}


