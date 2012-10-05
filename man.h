/*
StanfordMcGlinnBomberman
	Alex Yurkowski
	Catherine Kromkowski
	John Mapelli
	Joe Fetsch


man.cpp
man class header file
class "man" sets member functions for players in game 

*/
#ifndef MAN_H
#define MAN_H

class man{
public:
    man();
    man(int, int); //sets starting position, alive status
    int getx(); //returns x pos
    int gety(); //returns y pos
    void setx(int);  //sets x position of player
    void sety(int);  //sets y position of player
    int is_alive();  //returns life status of player
    void kill();   //sets life status to dead
    void resurrect(); //sets life status to live
private:
    int x; //x position
    int y; //y position
    int alive; //life status 
};

#endif // MAN_H
