/*StanfordMcGlinnBomberman
	Alex Yurkowski
	Catherine Kromkowski
	John Mapelli
	Joe Fetsch

block.cpp
Implementation file for the block class
A subclass of the type cell

*/


#include "block.h"
using namespace std;


block::block(int inX, int inY):cell(inX, inY){

  health=1; //constructs cell of type block
}

int block::getType(){
  return 1; //returns that cell is a block
}

