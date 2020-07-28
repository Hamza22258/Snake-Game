//============================================================================
// Name        : Tetris.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Tetris...
//============================================================================
#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<string>
//#include<sys/wait.h>
//#include<stdlib.h>
//#include<stdio.h>
#include<unistd.h>
#include<sstream>
#include<cmath>      // for basic math functions such as cos, sin, sqrt
using namespace std;

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */
double startx=320,starty=400;
int  cond=0 , score=0;
int xx1 , yy1 , xx1_2 , yy1_2 , xx1_3 , yy1_3 , xx1_4 , yy1_4 , xx1_5 , yy1_5 , xx1_b , yy1_b;//coordinates for food..
int life1=105,life2=105,food=0,bigfood=0;
int counter=0;
int s_x[200]={180},s_y[200]={180};
int lengthOfSnake=5;
bool gameOver=false;
string gameScore;

//my int xx1=100 , yy1=100;
void randomN()
{
srand(time(NULL));
xx1=rand()%610;//taking mode with 610 to not display food in borders..
yy1=rand()%610;
xx1_2=rand()%610;
yy1_2=rand()%610;
xx1_3=rand()%610;
yy1_3=rand()%610;
xx1_4=rand()%610;
yy1_4=rand()%610;
xx1_5=rand()%610;
yy1_5=rand()%610;
xx1_b=rand()%610;
yy1_b=rand()%610;
while ( xx1<23 || yy1<23 || xx1_2<23 || yy1_2<23 || xx1_3<23 || yy1_3<23 || xx1_4<23 || yy1_4<23 || xx1_5<23 || yy1_5<23 || xx1_b<23 || yy1_b <23 )//for coordinates of food to be in required place
{
xx1=rand()%610;
yy1=rand()%610;
xx1_2=rand()%610;
yy1_2=rand()%610;
xx1_3=rand()%610;
yy1_3=rand()%610;
xx1_4=rand()%610;
yy1_4=rand()%610;
xx1_5=rand()%610;
yy1_5=rand()%610;
xx1_b=rand()%610;
yy1_b=rand()%610;
}
while (((xx1==xx1_2) || (xx1_2==xx1_3) || (xx1_3==xx1_4) || (xx1_5==xx1) || (xx1==xx1_3)
|| (xx1==xx1_4) || (xx1==xx1_5) || (xx1_2==xx1_3) || (xx1_2==xx1_4) || (xx1_2==xx1_5) || (xx1_3==xx1_5)
|| (xx1_4==xx1_5) || (xx1_b==xx1_5) || (xx1_b==xx1_4) || (xx1_b==xx1_3) || (xx1_b==xx1_2) || (xx1_b==xx1))
&& ((yy1==yy1_2) || (yy1_2==yy1_3) || (yy1_3==yy1_4) || (yy1_5==xx1) || (yy1==yy1_3)
|| (yy1==yy1_4) || (yy1==yy1_5) || (yy1_2==yy1_3) || (yy1_2==yy1_4) || (yy1_2==yy1_5) || (yy1_3==yy1_5)
|| (yy1_4==yy1_5) || (yy1_b==yy1_5) ||(yy1_b==yy1_4) || (yy1_b==yy1_3) || (yy1_b==yy1_2) || (yy1_b==yy1)))
{
xx1=rand()%610;
yy1=rand()%610;
xx1_2=rand()%610;
yy1_2=rand()%610;
xx1_3=rand()%610;
yy1_3=rand()%610;
xx1_4=rand()%610;
yy1_4=rand()%610;
xx1_5=rand()%610;
yy1_5=rand()%610;
xx1_b=rand()%610;
yy1_b=rand()%610;
}
}
void Display(){

    glClearColor(0/*Red Component*/, 0.0/*Green Component*/,
            0.0/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
    glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
    //glClear(PALE_GOLDEN_ROD);
    //not DrawSquare( 2 , 3 ,20,colors[10]);  //This will draw a square shape of size 100x100  at x=300 and y=300
if (gameOver==false)
{
	if (cond==1)
  s_x[0]-=5;
  else if (cond==2)
	s_x[0]+=5;
	else if (cond==3)
  	s_y[0]+=5;
	else if (cond==4)
  	s_y[0]-=5;

  for(int i = lengthOfSnake ; i>0; i--) {//Swapping coordinates..

    s_x[i]=s_x[i-1];//x coordinate
    s_y[i]=s_y[i-1];//y coordinate
  }
 if (s_x[0]==620)
 {
    //x[0]=20;
   gameOver=true;//if snake collides with the barrier

}
else if (s_x[0]==20)
{
    //x[0]=610;
    gameOver=true;

}
   if (s_y[0]==610)
   {
    //y[0]=20;
    gameOver=true;

   }
  else if (s_y[0]==20)
  {
    //[0]=610;
    gameOver=true;

  }
  if (score>=20 && score<=80)//hurdle colliding
  {
      DrawLine( 430 , 430 ,  430 , 150 , 10 , colors[80] );
      for ( int i=0 ; i<280 ; i++)
      {
      if (s_x[0]==430 && s_y[0]==430-i)
      gameOver=true;
      if (s_y[0]==150+i && s_x[0]==430)
      gameOver=true;
      }
  }
  else if (score>80 && score<150)
  {
    DrawLine( 430 , 430 ,  430 , 150 , 10 , colors[5] );
    DrawLine( 150 , 150 ,  430 , 150 , 10 , colors[5] );
    for ( int i=0 ; i<280 ; i++)
    {
    if (s_x[0]==430 && s_y[0]==430-i)
    gameOver=true;
    if (s_y[0]==150+i && s_x[0]==430)
    gameOver=true;
    if (s_x[0]==150+i && s_y[0]==150)
    gameOver=true;
    if (s_y[0]==150 && s_x[0]==430-i)
    gameOver=true;
    }
  }
  else if (score>=150)
  {
    DrawTriangle( 400, 400 ,200 , 200 , 600 , 200 , colors[MISTY_ROSE] );
    DrawLine( 100 , 550 ,  300 , 550 , 10 , colors[31] );

    for ( int i=0; i<200 ; i++)
    {
      if (s_x[0]==400 && s_y[0]==400)
      gameOver=true;
      if (s_y[0]==200+i && s_x[0]==200+i)
      gameOver=true;
      if (s_x[0]==200+i && s_y[0]==200)
      gameOver=true;
      if (s_y[0]==200+i && s_x[0]==600-i)
      gameOver=true;
      if (s_x[0]==100+i && s_y[0]==550)
      gameOver=true;
    }

  }
for (  int j=0 ; j<lengthOfSnake; j++ )
  {
    DrawCircle( s_x[j] , s_y[j] , 5 , colors[43]);//snake ..
  }
  for (  int k=5 ; k<lengthOfSnake; k++ )//collision with tail..
    {
      if (s_x[0] == s_x[k] && s_y[0] == s_y[k] )
      gameOver=true;
    }


  DrawLine( life2 , 635 ,  350 , 635 , 7 , colors[93] );//life decrease tab.
  DrawLine( 105 , 635 ,  life1 , 635 , 7 , colors[33] );//life increase tab.
  food++;//food timer.
  bigfood++;//bigfood timer & appearing variable.
 if (bigfood>=1800 && bigfood<=2250)//bigfood appearing condition
  {
    DrawSquare( xx1_b , yy1_b ,12,colors[15]);//for large power food
    if ((s_x[0]-xx1_b>=-10 && s_x[0]-xx1_b<=10)&&(s_y[0]-yy1_b>=-10 && s_y[0]-yy1_b<=10))//matching coordinates with mouth of snake.
    {
      lengthOfSnake++;//snake increase after eating food..
      life1+=2;//life increaser
      life2+=2;//life decreaser
      score+=15;
      bigfood=0;//setting bigfood = 0 so it displays again according to the timer.
      food=0;//food timer reset after eating food..
      randomN();
    }
    else if (food==450)//food Dissapearing after 15s.
    {
     food=0;//food timer reset.
     bigfood=0;//setting timer for big food also = 0
      randomN();
    }
  }
  else
  {
  DrawSquare( xx1 , yy1 ,8,colors[16]);
  DrawSquare( xx1_2 , yy1_2 ,8,colors[16]);
  DrawSquare( xx1_3 , yy1_3 ,8,colors[16]);
  DrawSquare( xx1_4 , yy1_4 ,8,colors[16]);
  DrawSquare( xx1_5 , yy1_5 ,8,colors[16]);
  if ( (s_x[0]-xx1>=-7 && s_x[0]-xx1<=7 && s_y[0]-yy1>=-7 && s_y[0]-yy1<=7) || (s_x[0]-xx1_2>=-7 && s_x[0]-xx1_2<=7 && s_y[0]-yy1_2>=-7 && s_y[0]-yy1_2<=7) ||
  (s_x[0]-xx1_3>=-7 && s_x[0]-xx1_3<=7 && s_y[0]-yy1_3>=-7 && s_y[0]-yy1_3<=7) || (s_x[0]-xx1_4>=-7 && s_x[0]-xx1_4<=7 && s_y[0]-yy1_4>=-7 && s_y[0]-yy1_4<=7) ||
  (s_x[0]-xx1_5>=-7 && s_x[0]-xx1_5<=7 && s_y[0]-yy1_5>=-7 && s_y[0]-yy1_5<=7))//matching coordinates with mouth of snake.
  {
    life1+=2;//life increaser
    life2+=2;//life decreaser
    score+=5;
    lengthOfSnake++;
    food=0;//food timer reset after eating food..
    randomN();//making food random after eating
  }
  else if (food==450)//food Dissapearing after 15s.
  {
    food=0;//food timer reset.
    randomN();
  }
}
  // code for converting int score to string..
  stringstream S;
  S<<score;
  string scorestr=S.str();
  DrawString( 560, 630, scorestr , colors[93]);//for drawing score..
  gameScore=scorestr;

    DrawLine( 0 , 620 , 650  , 620 , 10 , colors[65] );//top line
    DrawLine( 20 , 650 ,  20 , 0 , 10 , colors[65] );//left line
    DrawLine( 0 , 20 ,  650 , 20 , 10 , colors[65] );//bottom line
    DrawLine( 630 , 0 ,  630 , 650 , 10 , colors[65] );//right line
    DrawString( 480, 630, "Score =", colors[93]);
    DrawString( 40, 630, "Snake", colors[93]);
    DrawString( 30, 0, "Press ECS to exit", colors[93]);

    if (life1>=350)//if life is full
    {
      gameOver=true;
    }
  }
  else if ( gameOver==true)//if game is over
  {
    DrawSquare( 0 , 0 ,650,colors[20]);
    DrawString( 240, 380, " Game Over!" , colors[130]);
    DrawString( 250, 350, "Your Score " , colors[130]);
    DrawString( 290, 320, gameScore , colors[130]);
    DrawString( 220, 285,"Press ESC to Exit." , colors[130]);
    counter++;//for exiting the mode gameover.
    if (counter==3500)
    exit(1);
  }


    glutSwapBuffers(); // do not modify this line..
}


/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT   /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
											// what to do when left key is pressed...

    if (cond == 3 || cond == 4 || cond == 0)
    {

        cond=1;
        glutPostRedisplay();
      }

    } else if (key == GLUT_KEY_RIGHT  /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
      if (cond == 3 || cond == 4 || cond == 0 )
      {
        cond=2;

        glutPostRedisplay();
        }

  } else if (key == GLUT_KEY_UP) /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/ {

        if (cond == 1 || cond == 2 || cond == 0)
          {
          cond=3;

          glutPostRedisplay();
          }
            }
            else if (key == GLUT_KEY_DOWN)   /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/ {

              if (cond == 1 || cond == 2 || cond == 0)
              {

              cond=4;

              glutPostRedisplay();
                  }
                  //  glutPostRedisplay();

    }


    /* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
     * this function*/
//     glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC/* Escape key ASCII*/) {
        exit(1); // exit the program when escape key is pressed.
    }
    if (key == 'R' || key=='r'/* Escape key ASCII*/) {
        exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }

    else if (int(key) == 13)
    {
	}

    glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

// implement your functionality here
	glutPostRedisplay();
// once again we tell the library to call our Timer function after next 1000/FPS
    glutTimerFunc(1000.0 /30, Timer, 0);
}


/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
    int width = 650, height = 650; // i have set my window size to be 800 x 600
    InitRandomizer(); // seed the random number generator...
    glutInit(&argc, argv); // initialize the graphics library...
    SetCanvasSize(width , height);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
    glutInitWindowPosition(50, 50); // set the initial position of our window
    glutInitWindowSize(width, height); // set the size of our window
    glutCreateWindow("PF's Snake Game"); // set the title of our game window
    SetCanvasSize(width, height); // set the number of pixels...
    randomN();//calling random fuction...
// Register your functions to the library,
// you are telling the library names of function to call for different tasks.
//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
    glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
    glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
    glutTimerFunc(5.0 / FPS, Timer, 0);

// now handle the control to library and it will call our registered functions when
// it deems necessary...
    glutMainLoop();
    return 1;
}
#endif /* Snake Game */
