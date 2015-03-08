#include "Coin.h"
#include<stdio.h>
#include<utility>
#include<iostream>
#include <cmath>
#include <GL/glut.h>
#include<glut.h>
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#define RAD2DEG(rad) (rad * 180 / PI)
#define ROTATEX(x,y,deg) ((x * cos(DEG2RAD(deg)))-(y*sin(DEG2RAD(deg))))
#define ROTATEY(x,y,deg) ((x * sin(DEG2RAD(deg)))+(y*cos(DEG2RAD(d
#define RED_COIN coin[8]
#define STRIKER coin[9]

float getDistance(float x1,float y1,float x2,float y2);

Coin::Coin()
{
    this->pocketed=0;
    this->position = make_pair(0.0f,0.0f);
    this->radius=0.0f;
    this->mass=0.0f;
    this->velocity = make_pair(0.0f,0.0f);
    this->colour = make_pair(0.0f,make_pair(0.0f,0.0f));
    this->points=10;
}

Coin::Coin(float cent_x,float cent_y,float rad,float col_r,float col_g,float col_b,float mas,int points)
{
    this->pocketed=0;
    this->position = make_pair(cent_x,cent_y);
    this->radius=rad;
    this->mass=mas;
    this->velocity = make_pair(0.0f,0.0f);
    this->colour = make_pair(col_r,make_pair(col_g,col_b));
    this->points=points;
}

void Coin::createCoin()
{
    pair<float,pair<float,float> > color;
    color = this->getcolour();
    glColor3f(color.first,color.second.first,color.second.second);
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0 ; i<360 ; i++) {
        glVertex2f(this->get_x()+(this->get_radius() * cos(DEG2RAD(i))), this->get_y()+(this->get_radius() * sin(DEG2RAD(i))));
    }
    glEnd();
}

void Coin::collide(Coin *second)
{
    float m1 = this->get_mass();
    float m2 = second->get_mass();
    float x1 = this->get_x();
    float y1 = this->get_y();
    float x2 = second->get_x();
    float y2 = second->get_y();
    float u_x1 = this->get_vx();
    float u_y1 = this->get_vy();
    float u_x2 = second->get_vx();
    float u_y2 = second->get_vy();

    float e=0.7f;

    float d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	float un_x = (x2 - x1) / d, un_y = (y2 - y1) / d;
	float ut_x = -un_y, ut_y = un_x;
	float ua_n = un_x * u_x1 + un_y * u_y1, ua_t = ut_x * u_x1 + ut_y * u_y1;
	float ub_n = un_x * u_x2 + un_y * u_y2, ub_t = ut_x * u_x2 + ut_y * u_y2;
	float va_n = (e * m2 * (ub_n - ua_n) + m1 * ua_n + m2 * ub_n) / (m1 + m2);
	float vb_n = (e * m1 * (ua_n - ub_n) + m1 * ua_n + m2 * ub_n) / (m1 + m2);
	float va_t = ua_t, vb_t = ub_t;
	float vax_n = va_n * un_x, vay_n = va_n * un_y, vax_t = va_t * ut_x, vay_t = va_t * ut_y;
	float vbx_n = vb_n * un_x, vby_n = vb_n * un_y, vbx_t = vb_t * ut_x, vby_t = vb_t * ut_y;
	this->set_vx(vax_n + vax_t);
	this->set_vy(vay_n + vay_t);
	second->set_vx(vbx_n + vbx_t);
	second->set_vy(vby_n + vby_t);
}

bool Coin::isCollided(Coin a)
{
    return (getDistance(this->get_x(),this->get_y(),a.get_x(),a.get_y()) < (this->get_radius()+a.get_radius()));
}

float getDistance(float x1,float y1,float x2,float y2)
{
    return sqrtf(((x2-x1)*(x2-x1)) + ((y2-y1)*(y2-y1)));
}

void Coin::friction_impact()
{
    bool sign;
    float x=this->get_vx(),y=this->get_vy();
    float friction=0.008f;
    float den = sqrtf((x*x) + (y*y));
    float x_comp=abs((x/den)*friction);
    float y_comp=abs((y/den)*friction);
    if(x>0)
    {
        sign=true;
        this->set_vx(this->get_vx()-x_comp);
    }
    else if(x<0)
    {
        sign=false;
        this->set_vx(this->get_vx()+x_comp);
    }
    if((this->get_vx()>0) != sign)
        this->set_vx(0.0f);


    if(y>0)
    {
        sign=true;
        this->set_vy(this->get_vy()-y_comp);
    }
    else if(y<0)
    {
        sign=false;
        this->set_vy(this->get_vy()+y_comp);
    }
    if((this->get_vy()>0) != sign)
        this->set_vy(0.0f);
}

bool Coin::isPocketed()
{
    return (this->pocketed==1);
}

void Coin::pocketCoin()
{
    this->pocketed = 1;
}

float Coin::get_x()
{
    return (this->position).first;
}

float Coin::get_y()
{
    return (this->position).second;
}

float Coin::get_dock()
{
    return this->dock;
}

void Coin::set_x(float x)
{
    this->position.first = x;
}

void Coin::set_y(float y)
{
    this->position.second = y;
}

void Coin::set_dock(float dock)
{
    this->dock = dock;
}

float Coin::get_vx()
{
    return (this->velocity).first;
}

float Coin::get_vy()
{
    return (this->velocity).second;
}

void Coin::set_vx(float vel)
{
    this->velocity.first = vel;
}

void Coin::set_vy(float vel)
{
    this->velocity.second = vel;
}

float Coin::get_mass()
{
    return this->mass;
}

void Coin::set_mass(float mass)
{
    this->mass = mass;
}

float Coin::get_radius()
{
    return this->radius;
}

void Coin::set_radius(float radius)
{
    this->radius = radius;
}

pair<float,pair<float,float> > Coin::getcolour()
{
    return this->colour;
}

void Coin::set_colour(float r, float g, float b)
{
    this->colour = make_pair(r,make_pair(g,b));
}

int Coin::get_points()
{
    return this->points;
}

void Coin::set_points(int points)
{
    this->points = points;
}
