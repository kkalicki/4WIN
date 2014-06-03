#ifndef KONSTANTEN_H_
#define KONSTANTEN_H_
#include <string>
// Konstanten fuer Spieler, Spielfeld, und Steine
const static unsigned short int ROT = 1;
const static unsigned short int GELB = 0;

// Konstanten fuer Spielfeld
const static unsigned short int X               = 7; //umbenennen in ROWS
const static unsigned short int Y               = 6; //COLUMNS
const static unsigned short CELL_SIZE           = 80;
const static unsigned short SEC_IN_MS           = 1000;
const static unsigned short DEFAULT_PORT_TCP    = 8001;
const static unsigned short DEFAULT_PORT_UDP    = 8002;
const static std::string    LOCALHOST           = "127.0.0.1";

#endif /* SPIELFELD_H_ */
