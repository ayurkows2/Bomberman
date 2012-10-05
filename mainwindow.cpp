/*
StanfordMcGlinnBomberman
	Alex Yurkowski
	Catherine Kromkowski
	John Mapelli
	Joe Fetsch

mainwindow.cpp
The main implementation file which defines all QT paintevents, image graphics, and the implementation of the game.  Includes all QT gui's built and graphics incorporated to make the game a preferable user experience. 
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QWidget>
#include <QTimer>
#include <QColor>
#include <stdlib.h>
#include <time.h>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>

using namespace std;
// comment comment
MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Bomberman");
    srand ( time(NULL) );

    winSize = 600;    //Window Size
    barSize = 25;     // menu bar size
    BOMBTIME = 3000;  //Timer for bombs in milliseconds
    maxBombs = 3;     //number of bombs one player can drop at one time

    player1BombCount = 0;  //respective player starting bomb count
    player2BombCount = 0;


    resize(winSize, winSize+barSize); //allows resizing of window

    boardSize = myBoard.getSize();  //defines board size from constructed board
    
    gameIsOver=0; //variable to determine if game has ended (player dies) 

    for(int i=0; i<boardSize; i++){		// boardSize x boardSize grid
        for(int j=0; j<boardSize; j++){
            myBoard.setBoard(i, j, &emptyCell);		// Set all the spaces to be empty
        }
    }

    cell_pix = winSize/boardSize; // pixel size of each cell

    //Set player2 to bottom right corner
    player2.setx(boardSize-1);
    player2.sety(boardSize-1);

    //make blocks 
    // added random
    for(int i=0; i<boardSize; i++){
        for(int j=0; j<boardSize; j++){
            if(i+j>=2 && i+j<=(boardSize-1)*2-2) {
	      		if(rand()%10<6) {
  	      			myBoard.setBoard(i, j, new block(i, j));  //sets board with random blocks spread throughout
				}
			}
        }
    }

//load all images into program
    boxImage = new QImage("./box.gif"); //image of blocking squares
    if(boxImage->isNull()) {
        std::cout << "Failed to load the image." <<std::endl;
    }
    player1Image = new QImage("./player1.png"); //image of player 1
    if(player1Image->isNull()) {
        std::cout << "Failed to load the image." <<std::endl;
    }
    player2Image = new QImage("./player2.png"); //image of player 2
    if(player2Image->isNull()) {
        std::cout << "Failed to load the image." <<std::endl;
    }
    backgroundImage = new QImage("./background.png"); //image in background
    if(backgroundImage->isNull()) {
        std::cout << "Failed to load the image." <<std::endl;
    }
    this->createMenus();
    
}

MainWindow::~MainWindow()
{
    delete ui; //deconstructor
}

void MainWindow::paintEvent(QPaintEvent *e)
{  

    setStatusBar(0); //create status bar

    QPainter painter(this);

    painter.setPen(Qt::black);	// Set the colors of the pen/brush to black
    painter.setBrush(Qt::black);

    painter.drawImage(0,barSize, *backgroundImage); //draws background image that has been imported
    for(int i = cell_pix; i<winSize; i+=cell_pix){		// Draw a grid on the window
        painter.drawLine(i, 0, i, winSize+barSize);
    }
    for(int i=cell_pix+barSize; i<winSize+barSize; i+=cell_pix){
      painter.drawLine(0, i, winSize, i);
    }

    //sets pen/brush of color red to indicate explosion
    painter.setPen(QColor(100,100,250));
    painter.setBrush(QColor(100,100,250));
    painter.setPen(Qt::red); 
    painter.setBrush(Qt::red);
    
    for(int i = 0; i<explosions.size();i++){
      for(int j = 0; j<explosions[i].size();j++){
        painter.drawRect((explosions[i][j]/30)*(cell_pix), (explosions[i][j]%30)*(cell_pix)+barSize, cell_pix, cell_pix); //draw rectangle in all space horizontal and vertical until next block
      }
    }

    //drawblocks
    painter.setPen(Qt::black);	// Set the colors of the pen/brush to black
    painter.setBrush(Qt::black);
    for(int i=0; i<boardSize; i++){
        for(int j=0; j<boardSize; j++){
            if(myBoard.getBoard(i, j)->getType()==1){	// If a block, draw a square
             //painter.drawImage(i*(cell_pix), j*(cell_pix)+barSize, boxImage->scaledToHeight(cell_pix));
             painter.drawRect(i*(cell_pix), j*(cell_pix)+barSize, cell_pix, cell_pix);
            }
        }
    }

    // draw player 1
    if(player1.is_alive()){
      //painter.drawImage(player1.getx()*(cell_pix), player1.gety()*(cell_pix)+barSize, player1Image->scaledToHeight(cell_pix));
        painter.setBrush(Qt::red);
        painter.setPen(Qt::red);
        painter.drawEllipse(player1.getx()*(cell_pix), player1.gety()*(cell_pix)+barSize, cell_pix, cell_pix);
    }

    // draw player 2
    if(player2.is_alive()){
      //painter.drawImage(player2.getx()*(cell_pix), player2.gety()*(cell_pix)+barSize, player2Image->scaledToHeight(cell_pix));
        painter.setBrush(Qt::blue);
        painter.setPen(Qt::blue);
        painter.drawEllipse(player2.getx()*(cell_pix), player2.gety()*(cell_pix)+barSize, cell_pix, cell_pix);
    }

    //draw bombs after players
    for(int i=0; i<boardSize; i++){
        for(int j=0; j<boardSize; j++){
            if(myBoard.getBoard(i, j)->getType()==2){	
                painter.setBrush(Qt::black);
                painter.setPen(Qt::black);
               painter.drawEllipse(i*(cell_pix)+5, j*(cell_pix)+barSize+5, cell_pix-10, cell_pix-10); 
            }
	}
    }
    
    if(gameIsOver==1)
    {
      gameIsOver=2;  //sets game is over to quit
      gameOver();    //before quit implement function
    }

    if((!player1.is_alive() || !player2.is_alive()) && gameIsOver==0){
         gameIsOver=1; //sets gameIsOver variable to indicate game end
    }

    if(gameIsOver==2) quit(); //if game is definitely over, quit game


}

void MainWindow::mousePressEvent(QMouseEvent *e){		// On a click

    update();  //update screen

}

void MainWindow::keyPressEvent ( QKeyEvent * event ){		// On a button press
    if(player1.is_alive() && player2.is_alive())  //if both players are alive
    {
    switch(event->key()){
      case Qt::Key_R:
	reset(); // reset if R is pressed
	break;
        // MOVE PLAYER 1
        case Qt::Key_A :
            if(player1.getx()>0 && myBoard.getBoard(player1.getx()-1, player1.gety())->getType()==0) player1.setx(player1.getx()-1); //sets player1 x position one spot to the left
            break;
        case Qt::Key_W:
            if(player1.gety()>0 && myBoard.getBoard(player1.getx(), player1.gety()-1)->getType()==0) player1.sety(player1.gety()-1); //sets player1 y position one spot up the screen
            break;
        case Qt::Key_S:
            if(player1.gety()<boardSize-1 && myBoard.getBoard(player1.getx(), player1.gety()+1)->getType()==0) player1.sety(player1.gety()+1);  //sets player1 y position one spot down the screen
            break;
        case Qt::Key_D:
            if(player1.getx()<boardSize-1 && myBoard.getBoard(player1.getx()+1, player1.gety())->getType()==0) player1.setx(player1.getx()+1);  //sets player1 x position one spot to the right
            break;
        case Qt::Key_E:  // DROP A BOMB FOR PLAYER1
	  if(player1.is_alive()&&player1BombCount<maxBombs){
	    drop_bomb(player1.getx(), player1.gety(), 1);
	  }
            break;
        // MOVE PLAYER 2
        case Qt::Key_Left :
            if(player2.getx()>0 && myBoard.getBoard(player2.getx()-1, player2.gety())->getType()==0) player2.setx(player2.getx()-1); //sets player2 x position one spot to the left
            break;
        case Qt::Key_Up:
            if(player2.gety()>0 && myBoard.getBoard(player2.getx(), player2.gety()-1)->getType()==0) player2.sety(player2.gety()-1);//sets player2 y position one spot up the screen
            break;
        case Qt::Key_Down:
            if(player2.gety()<boardSize-1 && myBoard.getBoard(player2.getx(), player2.gety()+1)->getType()==0) player2.sety(player2.gety()+1);//sets player2 y position one spot down the screen
            break;
        case Qt::Key_Right:
            if(player2.getx()<boardSize-1 && myBoard.getBoard(player2.getx()+1, player2.gety())->getType()==0) player2.setx(player2.getx()+1); //sets player2 x position one spot to the right
            break;
        case Qt::Key_Slash:  // DROP A BOMB FOR PLAYER2
	  if(player2.is_alive()&&player2BombCount<maxBombs) drop_bomb(player2.getx(), player2.gety(), 2);
            break;
    }
    }
    update();
}

void MainWindow::drop_bomb(int xIndex, int yIndex, int player){
    if(myBoard.getBoard(xIndex, yIndex)->getType()==0){
        bomb * b = new bomb(xIndex, yIndex); //allocate memory for new bomb at location
	b->setOwner(player); //set owner of bomb
	if(player==1){
	  player1BombCount++;  //if player 1 set the bomb, increase respective bomb count
	}
	else if(player == 2){
	  player2BombCount++; //if player 2 set the bomb, increase respective bomb count
	}
        myBoard.addBomb(xIndex, yIndex, b);  //add bomb to board
	QTimer::singleShot(BOMBTIME, this, SLOT(explode())); //set time for bomb explosion
    }
}

void MainWindow::bombExplode(cell *b){
    //bomb hasnt exploded yet if contains==1
    int contains = myBoard.bombActive(b);  //get state of bomb activation
    if(contains){
        QTimer::singleShot(500, this, SLOT(clearExplosion())); //explosion time
	deque<int> temp;  //create deque of temporary ints
	deque<cell*> bombsToExplode; //deque of bombs that are supposed to explode
        int x = b->getx(); //get x position bomb
        int y = b->gety(); //get y position of bomb
	temp.push_back(x*30+y); 
        myBoard.setBoard(x, y, &emptyCell); //get rid of bomb in board

	if(b->getOwner() == 1) player1BombCount--;  //decrease count of number of bombs on board per player
	else if(b->getOwner() == 2) player2BombCount--;

        if(player1.getx()==x && player1.gety()==y) player1.kill();//kill players if theyre standing on bomb
        if(player2.getx()==x && player2.gety()==y) player2.kill();

        for(int i = x+1; i<myBoard.getSize(); i++){ //CHECK X POSITIVE SIDE OF EXPLOSION
	  temp.push_back(i*30+y);
          if(myBoard.getBoard(i, y)->getType()==1){ //IF THERE IS A BLOCK
            myBoard.setBoard(i, y, &emptyCell);
            break;      // stop exploding in this direction
          }
          else if(myBoard.getBoard(i, y)->getType()==2){
	    bombsToExplode.push_back(myBoard.getBoard(i, y)); //will explode this after this bomb is done exploding
	    //bombExplode(myBoard.getBoard(i, y));  //explode at given position until a block is in the way
            break;
          }

          //KILL PLAYERS IN PATH
          if(player1.getx()==i && player1.gety()==y) player1.kill();
          if(player2.getx()==i && player2.gety()==y) player2.kill();
        }

        // repeat for each direction
        for(int i = x-1; i>=0; i--){
	  temp.push_back(i*30+y);
	  //explode until next block in left direction
          if(myBoard.getBoard(i, y)->getType()==1){
            myBoard.setBoard(i, y, &emptyCell);  //stop at block
            break;
          }
          else if(myBoard.getBoard(i, y)->getType()==2){
            //bombExplode(myBoard.getBoard(i, y)); //else explode
	    bombsToExplode.push_back(myBoard.getBoard(i, y)); //hit a bomb, explode after this bomb is done
            break;
          }
	  //kill all players in the path
          if(player1.getx()==i && player1.gety()==y) player1.kill();
          if(player2.getx()==i && player2.gety()==y) player2.kill();
        }
	
        for(int i = y; i<myBoard.getSize(); i++){
	  temp.push_back(x*30+i);
	  //explode until next block in up direction
          if(myBoard.getBoard(x, i)->getType()==1){
            myBoard.setBoard(x, i, &emptyCell); //stop at block
            break;
          }
          else if(myBoard.getBoard(x, i)->getType()==2){
            //bombExplode(myBoard.getBoard(x, i)); //if bomb, explode bomb
            bombsToExplode.push_back(myBoard.getBoard(x, i)); // hit a bomb, explode after this bomb is done
	    break;
          }
	  //kill all players in the path
          if(player1.getx()==x && player1.gety()==i) player1.kill();
          if(player2.getx()==x && player2.gety()==i) player2.kill();
        }

        for(int i = y; i>=0; i--){
	  temp.push_back(x*30+i);
	  //explode until next block in down direction
          if(myBoard.getBoard(x, i)->getType()==1){
            myBoard.setBoard(x, i, &emptyCell);  //stop at block
            break;
          }
          else if(myBoard.getBoard(x, i)->getType()==2){
            //bombExplode(myBoard.getBoard(x, i));  //if bomb, explode bomb
	    bombsToExplode.push_back(myBoard.getBoard(x, i)); // hit a bomb, explode after this bomb is done
            break;
          }
	 //kill all players in the path
          if(player1.getx()==x && player1.gety()==i) player1.kill();
          if(player2.getx()==x && player2.gety()==i) player2.kill();
        }
       explosions.push_back(temp);

       for(int i =0; i<bombsToExplode.size(); i++) bombExplode(bombsToExplode[i]); // explode the bombs that it hit
    }
}

void MainWindow::explode(){
    bomb * b = myBoard.getBomb();
    if(b!=NULL){
      if(b->getStatus() == 0) bombExplode(b); //function above: myBoard.bombExplode(b);
      myBoard.popTopBomb(); //remove bomb from deque
      update(); //update screen
    }
}

void MainWindow::clearExplosion(){
    explosions.pop_front();  //remove top explosion
    update(); //update
}

void MainWindow::createMenus()
 {
	fileMenu = menuBar()->addMenu(tr("&File"));  //create menue bar with file and help tabs
	helpMenu = menuBar()->addMenu(tr("&Help"));
    
	//three actions initialized
    resetAction=new QAction(("&Reset"),this);  
    connect(resetAction,SIGNAL(triggered()),SLOT(reset()));

    quitAction=new QAction(("&Quit"),this);
    connect(quitAction,SIGNAL(triggered()),SLOT(quit()));

    helpAction=new QAction(("&Help"),this);
    connect(helpAction,SIGNAL(triggered()),SLOT(help()));

	//under File tab: reset and quit; under Help tabe: help
	fileMenu->addAction(resetAction);
	fileMenu->addAction(quitAction);
	helpMenu->addAction(helpAction);
}


void MainWindow::reset(){			// Called from menu bar, resets the game
	QMessageBox msgBox;
	QSize msgBoxSize = msgBox.sizeHint();  //outputs message box popup to screen
	msgBox.move((winSize-msgBoxSize.width())/2,(winSize-msgBoxSize.height())/2);
	msgBox.setWindowTitle("RESET?");
	msgBox.setText("Really Reset the game?");
	msgBox.addButton("YES!", QMessageBox::AcceptRole);
	msgBox.addButton("NO!", QMessageBox::RejectRole);
	int returnval = msgBox.exec();	
	
	if(returnval==QMessageBox::AcceptRole) // only reset if yes is pressed
	{
	  realReset(); //if yes,then reset the game
	}
}

void MainWindow::realReset(){
	gameIsOver=0;
	
	player1.resurrect();	// Bring  both players back "from the dead"
	player2.resurrect();

	player1.setx(0);		// Set the players at their original positions
	player1.sety(0);
	player2.setx(boardSize-1);
	player2.sety(boardSize-1);

	player1BombCount = 0;  //set the bomb count on the board per player to 0
	player2BombCount = 0;

	myBoard.reset();  //resets the board 

	for(int i=0; i<boardSize; i++){
	  for(int j=0; j<boardSize; j++){
	    myBoard.setBoard(i, j, &emptyCell);
	  }
	}

	//make blocks // added random
	for(int i=0; i<boardSize; i++){
	    for(int j=0; j<boardSize; j++){
		if(i+j>=2 && i+j<=(boardSize-1)*2-2){		// This if loop ensures you are not placing blocks in places that will prohibit the bomber me from making initial moves.  i.e. It gives them space to start off in		    
			if(rand()%10<6) {
				myBoard.setBoard(i, j, new block(i, j));
			}
		}
	    }
	}
    update();
    }

void MainWindow::help(){
        QMessageBox msgBox;
	QSize msgBoxSize = msgBox.sizeHint(); //popup message box with instructions of the user
	msgBox.move((winSize-msgBoxSize.width())/2,(winSize-msgBoxSize.height())/2);
	msgBox.setWindowTitle("HELP ME!");
	msgBox.setText("Player 1 (white): WASD to move, E to place a bomb\nPlayer 2 (red): arrows to move, '/' to place a bomb\nOnly 3 bombs can be placed by a player at a time");
	msgBox.addButton("OK!", QMessageBox::AcceptRole);
	msgBox.exec();	
}

void MainWindow::gameOver(){
  	QMessageBox msgBox;
	QSize msgBoxSize = msgBox.sizeHint(); //popupmessage box declaring the game as over
	msgBox.move((winSize-msgBoxSize.width())/2,(winSize-msgBoxSize.height())/2);
	msgBox.setWindowTitle("Game Over!");
	int p1Alive = player1.is_alive();  //get the life status of both players
	int p2Alive = player2.is_alive();
	if(p1Alive == 0 && p2Alive == 1)  //if player 2 is alive, declare player 2 the winner
	{
	msgBox.setText("Player 1 has died!\nPlayer 2 wins!\n\nPlay again?"); //output winning message
	}
	else if (p1Alive == 1 && p2Alive == 0) //if player 1 is alive, declare player 1 the winner
	{
	msgBox.setText("Player 2 has died!\nPlayer 1 wins!\n\nPlay again?");  //output respective message
	}
	else if(p1Alive ==0 && p2Alive == 0 ) //if  both players are dead, then declare tie
	{
	  msgBox.setText("Both players died.\nTie Game.\n\nPlay again?"); //output message
	}
	//Ask user if would like to play again, input buttons which take action upon being pressed
	msgBox.addButton("YES!", QMessageBox::AcceptRole); 
	msgBox.addButton("NO!", QMessageBox::RejectRole);
	int returnval = msgBox.exec();	
	
	if(returnval==QMessageBox::AcceptRole) // only reset if yes is pressed and user would like to play again
	{
	  realReset(); //reset board
	}
}

void MainWindow::quit() {
	exit(0);  //if player would like to quit, then exit game 
}
