#ifndef COIN_H
#define COIN_H
#include<utility>
using namespace std;
class Coin
{
    public:
        Coin();
        Coin(float cent_x,float cent_y,float rad,float col_r,float col_g,float col_b,float mas,int points);
        void createCoin();
        bool isPocketed();
        void pocketCoin();
        float get_x();
        float get_y();
        float get_dock();
        void set_x(float x);
        void set_y(float y);
        void set_dock(float dock);
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
    protected:
    private:
        int pocketed;
        float dock;
        int power;
        pair<float,float> position;
        float radius;
        float mass;
        pair<float,float> velocity;
        pair<float,pair<float,float> > colour;
        int points;
};

#endif // COIN_H
