#include "Player.h"
#include <string>
#include <time.h>
using namespace std;

Player::Player()
{
    this->score = 30;
    this->name = "NoName";
}

Player::Player(char* name)
{
    this->score = 30;
    this->name = name;
}

Player::~Player()
{

}

int Player::getScore()
{
    return this->score;
}

void Player::setScore(int score)
{
    this->score = score;
}

char* Player::getName()
{
    return this->name;
}
