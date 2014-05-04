/*
 * main.cpp
 *
 *  Created on: 04.05.2014
 *      Author: K
 */
#include "../h/Stein.h"
#include "../h/Spielfeld.h"
#include "../h/Menue.h"
#include <iostream>

int main(void){

	Stein st;
	Spielfeld spf;
	Menue m;

	cout << st;
	cout << spf;

	m.start();

	return 0;
}


