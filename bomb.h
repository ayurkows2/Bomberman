/*
StanfordMcGlinnBomberman
	Alex Yurkowski
	Catherine Kromkowski
	John Mapelli
	Joe Fetsch

bomb.h
Header file for the bomb class inherited from class of cell

 */
#ifndef BOMB_H
#define BOMB_H

#include "cell.h"
using namespace std;

class bomb : public cell{
 public:
  bomb(int, int);
  int getType();  //returns that cell is a bomb
  int getStatus(); //returns status of bomb : waiting, close to explosion, after detonation
  void setStatus(int); //sets status according to input
 private:
  int status; //varible to determine stage of bom
};

#endif
