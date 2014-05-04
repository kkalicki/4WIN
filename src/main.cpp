/*
 * main.cpp
 *
 *  Created on: 04.05.2014
 *      Author: K
 */
#include "../h/Stein.h"
#include "../h/Spielfeld.h"
#include <iostream>

int main(void){

	Stein st;
	Stein *stein = new Stein(GELB);
	Spielfeld spf;
	cout << *stein << "\n";
	cout << st;
	cout << spf;
	delete stein;
	return 0;
}


