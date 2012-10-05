/*
StanfordMcGlinnBomberman
	Alex Yurkowski
	Catherine Kromkowski
	John Mapelli
	Joe Fetsch

cell.h
cell for bombs, blanks, or boxes
*/
#ifndef CELL_H
#define CELL_H

using namespace std;

class cell{
 public:
  cell();
  cell(int, int);  
  virtual int getType();  //returns type of cell--used in bomb and block 
  int getx();  //returns x pos
  int gety(); //returns y pos
  int getStatus(); //returns status of cell
  int getOwner();  //returns player owner of cell
  void setOwner(int);  //sets cell to have owner
 protected:
  int owner; //player
  int x; //x pos
  int y; //y pos
};

#endif
