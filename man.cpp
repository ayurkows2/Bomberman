/*
StanfordMcGlinnBomberman
	Alex Yurkowski
	Catherine Kromkowski
	John Mapelli
	Joe Fetsch

man.cpp
Implementation file for "man" class

*/
#include "man.h"

using namespace std;

man::man() 
{
    x=0;  //sets default position of player
    y=0;   
    alive =1; //sets life status as alive
}

man::man(int x_init, int y_init){
    x = x_init;  //sets player position of input x,y position
    y = y_init;
    alive = 1; //sets life status
}


int man::getx(){
    return x; //returns x pos of player
}

int man::gety(){
    return y; //returns y pos of player
}

int man::is_alive(){
    return alive; //returns life status (alive or dead)
}

void man::setx(int x_set){
    x=x_set;  //sets x pos
}

void man::sety(int y_set){
    y=y_set;  //sets y pos
}

void man::kill(){
    alive = 0; //sets life status of player to dead
}

void man:: resurrect() {
	alive = 1; //sets life status to live
}
