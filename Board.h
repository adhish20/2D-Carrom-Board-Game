#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include "Striker.h"
using namespace std;

class Board
{
    public:
        float square1;
        float square2;
        float square3;
        float square4;
        float hole_radius;
        float hole_x;
        float hole_y;
        float inner_circle_rad;
        float outer_circle_rad;
        void createBoard();
        Board();
        virtual ~Board();
    protected:
    private:
};

#endif // BOARD_H
