

							 *
						    **
						   *
						   |
						   |
						   |
					     ___________
					    /	        \
					   /		 \
					  |	 	  |  <-- Supposed to be a bomb
					  |		  |
					   \             /
					    \___________/  
						  




					BOMBERMAN


				    Game Simulator



/////////////////
ABOUT:         //
/////////////////
	
	This program is designed to emulate the classic "Bomberman" games.  This project was completed as part of a 
final project for the class Fundamentals of Computing II (CSE20212) at the University of Notre Dame, CSE department.

/////////////////
CONFIGURATION: //
/////////////////

	Bomberman has been tested to work on the student Linux machines, and on PC's remotely accessing a Linux machine


/////////////////
INSTALLATION:  //
/////////////////

	Files can be downloaded from http://code.google.com/p/stanfordmcglinbomberman/ .  Makefile can be created using
standard qt commands, or user can use included makefile


/////////////////
OPERATION:     //
/////////////////

		The goal of the game is to destroy the other player by placing bombs in such a way that the opponent will be in 
the explosion's path.  Each user can move up, down, left, and right; and place bombs at their current location.  
For full list of controls see the "CONTROLS" section in this document. The user's movement is restricted by bombs,
blocks, and the edge of the board.  
		Bombs are placed at the current location, and once placed, obstruct the user's movement to that space.  Bombs will
explode after three seconds in the upwards, downwards, left, and right directions.  This explosion extends in each direction
until it encounters a block, the end of the board, or a player.  If the explosion encounters a block, the explosion destroys 
that block and stops exploding in the direction.  If the explosion encounters a player, that player is killed, and the 
explosion continues on.  If the explosion encounters the end of the board, the explosion stops in that direction.  It is 
also important to note that each player can only place have three bombs on the board at a given time
		Upon the death of one or more of the players, the program is halted and the winner, if one exists, is determined.  
The users are allowed to replay the game, or quit the program.  
		The users can quit or restart the game from the "File" menu.  Additionally, the user can ask for help from 
the "Help" menu.  The help pop up window provides the user with the control commands, and information on the restrictions of
bomb placement.


/////////////////
CONTROLS:      //
/////////////////

PLAYER ONE:						PLAYER TWO:						
W: Up movement						Up Arrow: Up movement
A: Left movement					Left Arrow: Left movement
S: Down movement					Down Arrow: Down movement
D: Right movement					Right Arrow: Right movement
E: Bomb placement					/: Bomb placement


KEYBOARD SHORTCUTS:
Alt-F: Opens file menu
	WHILE FILE MENU IS OPEN:
	Alt-Q: Quit
	Alt-R: Reset
Alt-H: Opens help menu
	WHILE HELP MENU IS OPEN:
	Alt-H: Display help pop-up

/////////////////
FILE MANIFEST: //
/////////////////

Total : 25 Files 

Images:
1.) background.png
2.) box.gif
3.) gameover.png
4.) player1image.png
5.) player1.png
6.) player2image.png
7.) player2.png


Classes/Subclasses
1.) board.cpp / board.h
	Composed of:
	A.) cell.cpp / cell.h
		Inherits from:
		I.) block.cpp / block.h
		II.) bomb.cpp / bomb.h
2.) man.cpp / man.h
	

QT Files:
1.) mainwindow.cpp / mainwindow.h / mainwindow.ui
2.) qtOne.pro / qtOne.pro.user
3.) stanfordmcglinbomberman.pro


Other Files:
1.) main.cpp
2.) Makefile
3.) README.txt (this file)



///////////////////////////////
AUTHORS AND ACKNOWLEDGMENTS: //
///////////////////////////////

Authors/Programmers:
-John Mapelli
-Alex Yurkowski
-Catherine Kromkowski
-Joe Fetsch

Techinical (and emotional) support provided by:
-Scott J. Emrich -- Instructor
-Dinesh Rajan -- T.A.
-Dipanwita Dasgupta -- T.A. 
-Kerry Dobmeier -- T.A. 
-William Heineman -- T.A.
-Michael O'Brien -- T.A. 
-Josh Wise -- T.A. 

Resources:
-Google Code (code.google.com) - Used for version control
-QT Project Documentation (qt-project.org/doc/qt-4.8/) - Used as reference



///////////////////////////////
CONTACT INFORMATION:         //
///////////////////////////////

Issues/Concerns/Questions?  Send correspondence to:
-jmapelli@nd.edu












