#include "Board.h"
#include "Striker.h"
#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include<glut.h>
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#define RAD2DEG(rad) (rad * 180 / PI)
#define ROTATEX(x,y,deg) ((x * cos(DEG2RAD(deg)))-(y*sin(DEG2RAD(deg))))
#define ROTATEY(x,y,deg) ((x * sin(DEG2RAD(deg)))+(y*cos(DEG2RAD(deg))))


void drawBox(float len);
void drawBox_hollow(float len);
void drawHoles(float rad,float x,float y);
void drawBall_hollow(float rad,float x,float y);
void initialize_board();
void drawArc(float rad, float x, float y, float u , float v);

Board::Board()
{
    this->square1 = 160.0f;
    this->square2 = 150.0f;
    this->square3 = 120.0f;
    this->square4 = 102.0f;
    this->hole_radius = 5.0f;
    this->hole_x = 69.5f;
    this->hole_y = 69.5f;
    this->inner_circle_rad = 5.0f;
    this->outer_circle_rad = 15.0f;
}

void Board::createBoard()
{
    glColor3f(0.419f, 0.267f, 0.157f);
    drawBox(this->square1);

    glColor3f(0.882f, 0.75f, 0.515f);
    drawBox(this->square2);

    glColor3f(0.0f, 0.0f, 0.0f);
    //drawBox_hollow(this->square3);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(-49,60);
    glVertex2f(49,60);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(-49,-60);
    glVertex2f(49,-60);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(60,-49);
    glVertex2f(60,49);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(-60,-49);
    glVertex2f(-60,49);
    glEnd();
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(-49,51);
    glVertex2f(49,51);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(-49,-51);
    glVertex2f(49,-51);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(51,-49);
    glVertex2f(51,49);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(-51,-49);
    glVertex2f(-51,49);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glPushMatrix();
    glColor3f(0.8f, 0.4f, 0.2f);
    drawHoles(this->hole_radius, this->hole_x, this->hole_y);
    drawHoles(this->hole_radius, this->hole_x, -(this->hole_y));
    drawHoles(this->hole_radius, -(this->hole_x), -(this->hole_y));
    drawHoles(this->hole_radius, -(this->hole_x), this->hole_y);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBall_hollow(this->inner_circle_rad,0.0,0.0);
    drawBall_hollow(this->outer_circle_rad,0.0,0.0);
    glPopMatrix();

    //Design
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    drawBall_hollow(4.5,-49.0,-55.5);
    drawBall_hollow(4.5,-55.5,-49.0);
    drawBall_hollow(4.5,-49.0,55.5);
    drawBall_hollow(4.5,-55.5,49.0);
    drawBall_hollow(4.5,49.0,-55.5);
    drawBall_hollow(4.5,55.5,-49.0);
    drawBall_hollow(4.5,49.0,55.5);
    drawBall_hollow(4.5,55.5,49.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawHoles(3.5,-49.0,-55.5);
    drawHoles(3.5,-55.5,-49.0);
    drawHoles(3.5,49.0,-55.5);
    drawHoles(3.5,55.5,-49.0);
    drawHoles(3.5,-49.0,55.5);
    drawHoles(3.5,-55.5,49.0);
    drawHoles(3.5,49.0,55.5);
    drawHoles(3.5,55.5,49.0);
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-63,-63);
    glVertex2f(-25,-25);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(63,-63);
    glVertex2f(25,-25);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(-63,63);
    glVertex2f(-25,25);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(63,63);
    glVertex2f(25,25);
    glEnd();
    drawArc(5.5,25,25,90,360);
    drawArc(5.5,-25,25,-180,90);
    drawArc(5.5,25,-25,0,270);
    drawArc(5.5,-25,-25,-90,180);
    glPopMatrix();
}

void drawBox(float len)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
    glVertex2f(-len / 2, -len / 2);
    glVertex2f(len / 2, -len / 2);
    glVertex2f(len / 2, len / 2);
    glVertex2f(-len / 2, len / 2);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawBox_hollow(float len)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    glVertex2f(-len / 2, -len / 2);
    glVertex2f(len / 2, -len / 2);
    glVertex2f(len / 2, len / 2);
    glVertex2f(-len / 2, len / 2);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void drawHoles(float rad,float x,float y)
{
   glBegin(GL_TRIANGLE_FAN);
   for(int i=0 ; i<360 ; i++) {
       glVertex2f(x+(rad * cos(DEG2RAD(i))), y+(rad * sin(DEG2RAD(i))));
   }
   glEnd();
}

void drawBall_hollow(float rad,float x,float y)
{
   glBegin(GL_LINE_STRIP);
   for(int i=0 ; i<360 ; i++) {
       glVertex2f(x+(rad * cos(DEG2RAD(i))), y+(rad * sin(DEG2RAD(i))));
   }
   glEnd();
}

void drawArc(float rad,float x,float y,float u,float v)
{
   glBegin(GL_LINE_STRIP);
   for(int i=u ; i<v ; i++) {
       glVertex2f(x+(rad * cos(DEG2RAD(i))), y+(rad * sin(DEG2RAD(i))));
   }
   glEnd();
}

Board::~Board()
{

}
