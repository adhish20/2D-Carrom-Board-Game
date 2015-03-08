#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <time.h>
using namespace std;

class Player
{
    public:
        Player();
        Player(char* name);
        int getScore();
        void setScore(int scor);
        char* getName();
        virtual ~Player();
    protected:
    private:
        int score;
        char* name;
};

#endif // PLAYER_H
