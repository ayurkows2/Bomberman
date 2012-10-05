/*
StanfordMcGlinnBomberman
	Alex Yurkowski
	Catherine Kromkowski
	John Mapelli
	Joe Fetsch

bomb.cpp
Implementation file for the bomb subclass of cell

*/

#include "bomb.h"
using namespace std;


bomb::bomb(int inX, int inY):cell(inX, inY){
    status = 0; //ZERO == WAITING TO BLOW UP
                //ONE == SHOULD BLOW UP NOW
                //-1 == ALREADY BLEW UP
}

int bomb::getType(){
  return 2;  //returns cell type as "bomb" 
}

int bomb::getStatus(){
    return status; //see status explanation aboveabove
}

void bomb::setStatus(int stat){
    status = stat; //sets the status of the bomb to waiting, about to, or already past
}
