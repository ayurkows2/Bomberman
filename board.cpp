/*
StanfordMcGlinnBomberman
	Alex Yurkowski
	Catherine Kromkowski
	John Mapelli
	Joe Fetsch

board.cpp
Board class implementation
*/
#include<iostream>
#include "board.h"
#include <iterator>
using namespace std;

board::board(){
  int i, j;
  size = 20;
  for(i=0;i<size;i++) {
    vector<cell*> tempVec;  
    for(j=0; j<size; j++) {  //vector of cells
      cell p(i,j);
      tempVec.push_back(&p); 
    }
    myBoard.push_back(tempVec); //make 2D vector of cells 
  }
}

void board::setBoard(int x, int y, cell *c){
  myBoard[x][y]= c; //sets x,y position to type of cell
}

cell* board::getBoard(int x, int y){
  return myBoard[x][y]; //returns type of cell that is at x,y pos
}

void board::addBomb(int x, int y, bomb *b){
  myBoard[x][y] = b; //sets cell at x,y pos to bomb
  bombs.push_back(b); 
}

int board::getSize(){
    return size; //returns size of board
}


bomb * board::getBomb(){
    if(bombs.size()>0){
        bomb* b = bombs[0];  //get the bomb from the vector of bombs
        return b;
    }
    else return 0;
}

void board::popTopBomb(){
    bombs.pop_front();  //deletes bomb in arsenal
}

int board::bombActive(cell *b){
    for(int i = 0; i < bombs.size(); i++){
        if(bombs[i]==b){
            bombs[i]->setStatus(1); //if bomb is placed, set cell to active bomb
            return 1;
        }
    }
    return 0;
}

void board::reset(){
  bombs.clear(); //resets game board
}


