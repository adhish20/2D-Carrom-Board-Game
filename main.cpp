#include <iostream>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <GL/glut.h>
#include<glut.h>
#include<string.h>
#include <sys/time.h>
#include "Coin.h"
#include "Player.h"
#include "Board.h"
#include "Striker.h"
using namespace std;

//Macro Definitions
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#define RAD2DEG(rad) (rad * 180 / PI)
#define ROTATEX(x,y,deg) ((x * cos(DEG2RAD(deg)))-(y*sin(DEG2RAD(deg))))
#define ROTATEY(x,y,deg) ((x * sin(DEG2RAD(deg)))+(y*cos(DEG2RAD(deg))))
#define RED_COIN coin[8]

//GLobal Variables
float ball_rad = 5.0f;
int first_display = 0;
float inner_box_len = 150.0f;
int display_hover = 1;
float windowWidth,windowHeight;
int play = 0;
char buffer[30];
int processing[10][10]={{0}};
float dock = -75.0f;
int first = 0;
time_t current,previous;
int gameover = 0;
//Object Declarations
Board board;
Coin coin[9];
Striker striker;
Player player1("Adhish");
struct timeval tv;

void output(int x, int y, float r, float g, float b, void* font, char *string)
{
  glColor3f( r, g, b );
  glRasterPos2f(x, y);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}

void initialize_board()
{
    float rtang = 0.0f;
    for(int i = 0; i <= 3 ; i++)
    {
        coin[i] = Coin(ROTATEX(10.0f,0.0f,rtang),ROTATEY(10.0f,0.0f,rtang),3.5f,0.0f,0.0f,0.0f,5.0f,10);
        coin[i].createCoin();
        rtang += 90.0f;
    }

    rtang = 45.0f;
    for(int i = 4; i <= 7 ; i++)
    {
        coin[i] = Coin(ROTATEX(10.0f,0.0f,rtang),ROTATEY(10.0f,0.0f,rtang),3.5f,1.0f,1.0f,1.0f,5.0f,10);
        coin[i].createCoin();
        rtang += 90.0f;
    }

    RED_COIN = Coin(0.0f,0.0f,3.5f,1.0f,0.0f,0.0f,5.0f,50);
    striker = Striker(0.0f,-55.5f,4.5f,0.0f,1.0f,0.0f,8.0f,-5);
    RED_COIN.createCoin();
    striker.createStriker();
}

void reset_new_chance()
{
    striker.set_vx(0.0f);
    striker.set_vy(0.0f);
    striker.set_radius(4.5f);
    striker.set_hover_rot(90.0f);
    striker.set_x(0.0f);
    striker.set_y(-55.5f);
    display_hover = 1;
    striker.set_power(10.0f);
    striker.set_hover_x((0.0f + striker.get_x())/2);
    striker.set_hover_y((0.0f + striker.get_y())/2);
    play = 0;
}

void drawScene() {

    if(!first_display)
    {
        gettimeofday(&tv,NULL);
        current = tv.tv_sec;
        previous = current;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, -200.0f);
    board.createBoard();
    if(!(first_display++))
        initialize_board();

    for(int i = 0; i <= 8 ; i++)
        coin[i].createCoin();

    striker.createStriker();

    if(display_hover)
    {
        glColor3f(0.0f,0.0f,1.0f);
        glBegin(GL_LINE_STRIP);
        glVertex2f(striker.get_x(), striker.get_y());
        glVertex2f(striker.get_hover_x(),striker.get_hover_y());
        glEnd();
    }

    striker.display_power_bar();
    output(-145.0f,-60.0f,0.0f,0.0f,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,"Your Score:");
    itoa(player1.getScore(),buffer,10);
    output(-105.0f,-60.0f,0.0f,0.0f,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,buffer);
    if(first == 0 && gameover == 0)
    {
        output(-40.0f,-20.0f,0.0f,0.0f,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,"Choose  1.Black   2.White");
    }
    if(gameover == 1)
    {
        output(-40.0f,-20.0f,0.0f,0.0f,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,"Your Final Score : ");
        itoa(player1.getScore(),buffer,10);
        output(25.0f,-20.0f,0.0f,0.0f,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,buffer);
        first = 0;
    }
    glPopMatrix();
    glutSwapBuffers();
}

void detect_collision()
{
    int collided[10][10]={{0}};
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(!collided[i][j] && coin[i].isCollided(coin[j]) && i!=j && processing[i][j]==0)
            {
                collided[i][j] = 1;
                collided[j][i] = 1;
                coin[i].collide(&coin[j]);
                processing[i][j]=1;
                processing[j][i]=1;
                i = -1;
                break;
            }
            else if(!coin[i].isCollided(coin[j]) && i!=j && processing[i][j]==1)
            {
                processing[i][j]=0;
                processing[j][i]=0;
            }
            if(!collided[9][i] && striker.isCollided(coin[i]) && processing[9][i]==0)
            {
                collided[9][i] = 1;
                collided[i][9] = 1;
                striker.collide(&coin[i]);
                processing[i][9]=1;
                processing[9][i]=1;
                i = -1;
                break;
            }
            else if(!striker.isCollided(coin[i]) && processing[9][i]==1)
            {
                processing[i][9]=0;
                processing[9][i]=0;
            }
        }
    }
}

void update(int value)
{
    if(first == 1)
    {
        int i;
        for(i=0;i<4;i++)
        {
            if(!coin[i].isPocketed())
                break;
        }
        if(i == 4 && coin[8].isPocketed())
            gameover = 1;

    }
    else if(first == 2)
    {
        int i;
        for(i=4;i<8;i++)
        {
            if(!coin[i].isPocketed())
                break;
        }
        if(i == 8 && coin[8].isPocketed())
            gameover = 1;
    }
    gettimeofday(&tv,NULL);
    current = tv.tv_sec;
    if(first != 0)
    {
        if(play!=1 && current-previous==1)
            player1.setScore(player1.getScore()-1);
        if(play == 1)
        {
            for(int i=0;i<9;i++)
                coin[i].friction_impact();
            striker.friction_impact();


            for(int i=0; i<9 && striker.get_vx()==0.0f && striker.get_vy()==0.0f; i++)
            {
                if(coin[i].get_vx()!=0.0f || coin[i].get_vy()!=0.0f)
                    break;
                else if(i==8)
                {
                    play = 2;
                    reset_new_chance();
                }
            }
        }
        detect_collision();

        for(int i=0;i<9;i++)
        {
            if(!coin[i].isPocketed())
            {
                if(sqrtf((coin[i].get_x()-board.hole_x)*(coin[i].get_x()-board.hole_x) + (coin[i].get_y()-board.hole_y)*(coin[i].get_y()-board.hole_y)) <= board.hole_radius)
                {
                    coin[i].pocketCoin();
                    coin[i].set_dock(dock);
                    dock+=(2*coin[i].get_radius()+1.5f);
                    player1.setScore(player1.getScore()+coin[i].get_points());
                }
                if(sqrtf((coin[i].get_x()+board.hole_x)*(coin[i].get_x()+board.hole_x) + (coin[i].get_y()-board.hole_y)*(coin[i].get_y()-board.hole_y)) <= board.hole_radius)
                {
                    coin[i].pocketCoin();
                    coin[i].set_dock(dock);
                    dock+=(2*coin[i].get_radius()+1.5f);
                    player1.setScore(player1.getScore()+coin[i].get_points());
                }
                if(sqrtf((coin[i].get_x()-board.hole_x)*(coin[i].get_x()-board.hole_x) + (coin[i].get_y()+board.hole_y)*(coin[i].get_y()+board.hole_y)) <= board.hole_radius)
                {
                    coin[i].pocketCoin();
                    coin[i].set_dock(dock);
                    dock+=(2*coin[i].get_radius()+1.5f);
                    player1.setScore(player1.getScore()+coin[i].get_points());
                }
                if(sqrtf((coin[i].get_x()+board.hole_x)*(coin[i].get_x()+board.hole_x) + (coin[i].get_y()+board.hole_y)*(coin[i].get_y()+board.hole_y)) <= board.hole_radius)
                {
                    coin[i].pocketCoin();
                    coin[i].set_dock(dock);
                    dock+=(2*coin[i].get_radius()+1.5f);
                    player1.setScore(player1.getScore()+coin[i].get_points());
                }
            }
        }

        for(int i=0;i<9;i++)
        {
            if(!coin[i].isPocketed())
            {
                if(coin[i].get_x() + coin[i].get_radius() > board.square2/2)
                {
                    coin[i].set_vx(coin[i].get_vx()*-1);
                    coin[i].set_x(board.square2/2 - coin[i].get_radius());
                }
                if(coin[i].get_x() - coin[i].get_radius() < -board.square2/2)
                {
                    coin[i].set_vx(coin[i].get_vx()*-1);
                    coin[i].set_x(-board.square2/2 + coin[i].get_radius());
                }
                if(coin[i].get_y() + coin[i].get_radius() > board.square2/2)
                {
                    coin[i].set_vy(coin[i].get_vy()*-1);
                    coin[i].set_y(board.square2/2 - coin[i].get_radius());
                }
                if(coin[i].get_y() - coin[i].get_radius() < -board.square2/2)
                {
                    coin[i].set_vy(coin[i].get_vy()*-1);
                    coin[i].set_y(-board.square2/2 + coin[i].get_radius());
                }
                coin[i].set_x(coin[i].get_vx()+coin[i].get_x());
                coin[i].set_y(coin[i].get_vy()+coin[i].get_y());
            }
            else
            {
                coin[i].set_vx(0.0f);
                coin[i].set_vy(0.0f);
                coin[i].set_x(-90.0f);
                coin[i].set_y(coin[i].get_dock());
            }
        }

        //Striker Pocketed

        if(sqrtf((striker.get_x()-board.hole_x)*(striker.get_x()-board.hole_x) + (striker.get_y()-board.hole_y)*(striker.get_y()-board.hole_y)) <= board.hole_radius)
        {
            striker.set_radius(0.0f);
            striker.set_vx(0.0f);
            striker.set_vy(0.0f);
            striker.set_x(0.0f);
            striker.set_y(0.0f);
            player1.setScore(player1.getScore()-5);
        }
        if(sqrtf((striker.get_x()+board.hole_x)*(striker.get_x()+board.hole_x) + (striker.get_y()-board.hole_y)*(striker.get_y()-board.hole_y)) <= board.hole_radius)
        {
            striker.set_radius(0.0f);
            striker.set_x(0.0f);
            striker.set_y(0.0f);
            striker.set_vx(0.0f);
            striker.set_vy(0.0f);
            player1.setScore(player1.getScore()-5);
        }
        if(sqrtf((striker.get_x()-board.hole_x)*(striker.get_x()-board.hole_x) + (striker.get_y()+board.hole_y)*(striker.get_y()+board.hole_y)) <= board.hole_radius)
        {
            striker.set_radius(0.0f);
            striker.set_x(0.0f);
            striker.set_y(0.0f);
            striker.set_vx(0.0f);
            striker.set_vy(0.0f);
            player1.setScore(player1.getScore()-5);
        }
        if(sqrtf((striker.get_x()+board.hole_x)*(striker.get_x()+board.hole_x) + (striker.get_y()+board.hole_y)*(striker.get_y()+board.hole_y)) <= board.hole_radius)
        {
            striker.set_radius(0.0f);
            striker.set_x(0.0f);
            striker.set_y(0.0f);
            striker.set_vx(0.0f);
            striker.set_vy(0.0f);
            player1.setScore(player1.getScore()-5);
        }


//Striker collision with board
        if(striker.get_x() + striker.get_radius() > board.square2/2)
        {
            striker.set_vx(striker.get_vx()*-1);
            striker.set_x(board.square2/2 - striker.get_radius());
        }
        if(striker.get_x() - striker.get_radius() < -board.square2/2)
        {
            striker.set_vx(striker.get_vx()*-1);
            striker.set_x(-board.square2/2 + striker.get_radius());
        }
        if(striker.get_y() + striker.get_radius() > board.square2/2)
        {
            striker.set_vy(striker.get_vy()*-1);
            striker.set_y(board.square2/2 - striker.get_radius());
        }
        if(striker.get_y() - striker.get_radius() < -board.square2/2)
        {
            striker.set_vy(striker.get_vy()*-1);
            striker.set_y(-board.square2/2 + striker.get_radius());
        }
        striker.set_x(striker.get_vx()+striker.get_x());
        striker.set_y(striker.get_vy()+striker.get_y());
    }

    previous = current;
    glutTimerFunc(10, update, 0);
}

// Initializing some openGL 3D rendering options
void initRendering() {

    //glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
    glEnable(GL_COLOR_MATERIAL);    // Enable coloring
    glClearColor(0.70f, 0.70f, 0.70f, 1.0f);   // Setting a background color
}

// Function called when the window is resized
void handleResize(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

    if (key == 27) {
        exit(0);     // escape key is pressed
    }
    if(first!=0)
    {
        if(key==32 && play==0)
        {
            display_hover = 0;
            striker.Striker_shoot();
            play = 1;
        }
        if (key == 'a')
        {
            if(!play)
                striker.hover_move(1);
        }
        if (key == 'c')
        {
            if(!play)
                striker.hover_move(-1);
        }
    }
    if(key == '1' && first == 0)
    {
        first = 1;
        for(int i = 4 ; i<=7;i++)
            coin[i].set_points(-5);
    }
    if(key == '2' && first == 0)
    {
        first = 2;
        for(int i = 0 ; i<=3;i++)
            coin[i].set_points(-5);
    }
}

void handleKeypress2(int key, int x, int y) {
    if(first!=0)
    {
        if(key == GLUT_KEY_LEFT)
        {
            if(!play)
            {
                striker.Striker_move(-1);
            }
        }
        if(key == GLUT_KEY_RIGHT)
        {
            if(!play)
            {
                striker.Striker_move(1);
            }
        }
        if (key == GLUT_KEY_UP)
        {
            if(striker.get_power() < 35 && play==0)
            {
                striker.set_power(striker.get_power()+5.0f);
            }
        }
        if (key == GLUT_KEY_DOWN)
        {
            if(striker.get_power() > -35 && play==0)
            {
                striker.set_power(striker.get_power()-5.0f);
            }
        }
    }
}

int isRightClicked = 0;
int isLeftClicked = 0;
int drag_on_left = 0;
int drag_on_right = 0;
int just_closed = 0;
int position[2];

void handleMouseclick(int button, int state, int x, int y) {
    if(first!=0)
    {
        drag_on_right = 0;
        if (button == GLUT_RIGHT_BUTTON)
            isRightClicked = (!state);
        if (button == GLUT_LEFT_BUTTON)
            isLeftClicked = (!state);
        if (button == GLUT_LEFT_BUTTON && state == 1)
        {
            display_hover = 0;
            striker.Striker_shoot();
            play = 1;
        }
        if(isRightClicked)
            drag_on_right = 1 ;
        if(isLeftClicked)
            drag_on_left = 1 ;
    }
}
int position_drag[2]; //to check left or right
int position_drag_initial[2]; // intensity
int direction=0;
void handleMotionClick(int x,int y)
{
    if(first!=0)
    {
        if(drag_on_right)
        {
            if(position_drag[0]>x)
            {
                if(direction!=-1)
                {
                    position_drag_initial[0]=x;
                }
                direction=-1;
                for(int i=-1;i<(position_drag_initial[0]-x)/100;i++)
                {
                    if(!play)
                        striker.Striker_move(-1);
                }
            }
            if(position_drag[0]<x)
            {
                if(direction!=1)
                {
                    position_drag_initial[0]=x;
                }
                direction=1;
                for(int i=-1;i<(x-position_drag_initial[0])/100;i++)
                {
                    if(!play)
                        striker.Striker_move(1);
                }
            }
            position_drag[0]=x;
        }
        if(drag_on_left)
        {
            if(position_drag[0]>x)
            {
                if(direction!=-1)
                {
                    position_drag_initial[0]=x;
                }
                direction=-1;
                for(int i=-1;i<(position_drag_initial[0]-x)/100;i++)
                {
                    if(!play)
                        striker.hover_move(1);
                }
            }
            if(position_drag[0]<x)
            {
                if(direction!=1)
                {
                    position_drag_initial[0]=x;
                }
                direction=1;
                for(int i=-1;i<(x-position_drag_initial[0])/100;i++)
                {
                    if(!play)
                        striker.hover_move(-1);
                }
            }
            position_drag[0]=x;
        }
    }
}

int main(int argc, char **argv) {
    striker.set_x(0.0f);
    striker.set_y(-55.5f);
    striker.set_radius(4.5f);
    striker.set_colour(0.0f,1.0f,0.0f);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    int w = glutGet(GLUT_SCREEN_WIDTH);
    int h = glutGet(GLUT_SCREEN_HEIGHT);
    windowWidth = w * 2 / 3;
    windowHeight = h * 2 / 3;

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

    glutCreateWindow("Carrom");
    initRendering();

    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutKeyboardFunc(handleKeypress1);
    glutSpecialFunc(handleKeypress2);
    glutMouseFunc(handleMouseclick);
    glutMotionFunc(handleMotionClick);
    glutReshapeFunc(handleResize);
    glutTimerFunc(10, update, 0);

    glutMainLoop();
    return 0;
}
