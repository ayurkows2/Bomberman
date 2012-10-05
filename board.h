/*
StanfordMcGlinnBomberman
	Alex Yurkowski
	Catherine Kromkowski
	John Mapelli
	Joe Fetsch

board.h
class of the board
Board is a grid with either nothing, a bomb, or a box in each cell
 */
#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <deque>
#include "cell.h"
#include "block.h"
#include "bomb.h"
using namespace std;

class board{
 public:
  board();
  void setBoard(int, int, cell*); //set a cell x,y,cell
  cell* getBoard(int, int);       //get contents of a cell, x,y
  void addBomb(int, int, bomb*); //add a bomb to the board
  bomb* getBomb();  
  int getSize();
  void popTopBomb(); //deletes bomb from arsenal
  int bombActive(cell*); //activates bomb on board --changes status of cell
  void reset(); //clear game/reset
 private:
  vector<vector<cell*> > myBoard; //2D vector of cells creates game board
  deque<bomb*> bombs; //deque of bombs in arsenal
  int size; 
  cell empty;
};

#endif
