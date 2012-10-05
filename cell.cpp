/*
StanfordMcGlinnBomberman
	Alex Yurkowski
	Catherine Kromkowski
	John Mapelli
	Joe Fetsch

cell.cpp
Implementation file for the class of cells 
Defines member functions for the class of cell
*/
#include "cell.h"
using namespace std;

cell::cell(){
  x = 0; //default position is at 0,0
  y = 0;
}

cell::cell(int inX, int inY){
  x = inX; //input position to set x,y
  y = inY;
}

int cell::getType(){
  return 0; //returns that cell is not bomb or block
}

int cell::getx(){
  return x;  //returns x position
}

int cell::gety(){
  return y; //returns y position
}

int cell::getStatus(){
  return 0; //returns status of cell as null
}

int cell::getOwner(){
  return owner; //returns if player occupies cell
}

void cell::setOwner(int player){
  owner = player;  //sets cell to be occupied by player
}
