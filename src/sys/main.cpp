/*
 * main.cpp
 *
 *  Created on: 04.05.2014
 *      Author: K
 */
#include "../h/sys/Stein.h"
#include "../h/sys/Spielfeld.h"
#include "../h/sys/Menue.h"
#include "../h/sys/Spiel.h"

#include "../h/gui/mainwindow.h"
#include <QApplication>

#include <iostream>

int main(int argc, char* argv[]){

    //Menue m;
    //m.start();

    QApplication a(argc,argv);
    MainWindow w;
    w.show();
    return a.exec();
}


