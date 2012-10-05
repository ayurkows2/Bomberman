/*
StanfordMcGlinnBomberman
	Alex Yurkowski
	Catherine Kromkowski
	John Mapelli
	Joe Fetsch

block.h
Block header file

 */
#ifndef BLOCK_H
#define BLOCK_H

#include "cell.h"
using namespace std;

class block : public cell{
 public:
  block(int, int); //constructor
  int getType(); //returns type of cell
 private:
  int health; //set to type of cell
};

#endif
