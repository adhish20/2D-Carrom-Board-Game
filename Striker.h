#ifndef STRIKER_H
#define STRIKER_H
#include<utility>
#include "Coin.h"
#include <GL/glut.h>
#include<glut.h>
using namespace std;
class Striker
{
    public:
        Striker();
        Striker(float cent_x,float cent_y,float rad,float col_r,float col_g,float col_b,float mas,int points);
        void createStriker();
        bool isPocketed();
        void pocketStriker();
        float get_x();
        float get_y();
        void set_x(float x);
        void set_y(float y);
        float get_vx();
        float get_vy();
        void set_vx(float vel);
        void set_vy(float vel);
        float get_mass();
        void set_mass(float mass);
        float get_radius();
        void set_radius(float radius);
        pair<float,pair<float,float> > getcolour();
        void set_colour(float r,float g,float b);
        int get_points();
        void set_points(int points);
        void collide(Coin *second);
        void friction_impact();
        bool isCollided(Coin a);
        float get_hover_x();
        void set_hover_x(float x);
        float get_hover_y();
        void set_hover_y(float x);
        float get_hover_rot();
        void set_hover_rot(float x);
        float get_power();
        void set_power(float pow);
        void display_power_bar();
        void hover_move(int dir);
        void Striker_move(int dir);
        void Striker_shoot();
    protected:
    private:
        int pocketed;
        pair<float,float> position;
        float radius;
        float mass;
        float hover_x;
        float hover_y;
        float hover_rot;
        float power;
        pair<float,float> velocity;
        pair<float,pair<float,float> > colour;
        int points;
};

#endif // STRIKER_H
