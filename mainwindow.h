/*
StanfordMcGlinnBomberman
	Alex Yurkowski
	Catherine Kromkowski
	John Mapelli
	Joe Fetsch

mainwindow.h
The header file for the main QT window and program file.  Includes all other classes from previous files to describe all public functions and private variables. 

*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <vector>
#include "board.h"
#include "bomb.h"
#include "block.h"
#include "cell.h"
#include "man.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
	//main functions
    void explode();
    void clearExplosion();
	void reset();
	void help();
	void quit();
private:
    Ui::MainWindow *ui;
    man player1; //declare 1st player of type man
    int player1BombCount;  //number of bombs player 1 has dispatched onto board
    man player2;  //declare 2nd player of type man
    int player2BombCount;  //number of bombs dispatched by player 2 onto board
    int winSize; //size of window
    int barSize; //size of bar
    int maxBombs;  //3 bomb maximum for each player at a time
    int gameIsOver;  //variable to determine status of the game (in play or over)
    board myBoard; //board variable
    cell emptyCell;  //cell variable
    int BOMBTIME;  //timer variable
    int boardSize;  //size of board
    void drop_bomb(int, int, int);  //drop bomb function 
    void realReset();  //function to reset the game
    void gameOver();  //function to declare the game over or still in play
    int cell_pix;  //pixels of cell
    void bombExplode(cell *);  //function to explode bomb
    QImage *backgroundImage;  //imported image of game background
    QImage *player1Image;  //imported image of player 1
    QImage *player2Image;  //imported image of player 2
    QImage *boxImage;  //imported image of box 
    QImage *boxImage2; //imported image of box #2
    deque<deque<int> > explosions;  //hold all explosion points
	void createMenus();  //create the following menu tabs
	QMenu *fileMenu;
	QMenu *optionsMenu;
	QMenu *helpMenu;
	QAction *resetAction;  
	QAction *quitAction;
	QAction *helpAction;


protected:
	//all events in QT
    void paintEvent(QPaintEvent *);  
    void mousePressEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
};

#endif // MAINWINDOW_H
