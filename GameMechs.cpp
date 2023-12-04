#include "GameMechs.h"
#include<iostream>

GameMechs::GameMechs()
{
    boardSizeX = 30;
    boardSizeY = 15;
    exitFlag = false;
    loseFlag = false;
    score = 0;
}

GameMechs::GameMechs(int boardX, int boardY)
{

}

// do you need a destructor?
/*GameMechs::~GameMechs()
{

}*/



bool GameMechs::getExitFlagStatus()
{

}

char GameMechs::getInput()
{

}

int GameMechs::getBoardSizeX()
{

}

int GameMechs::getBoardSizeY()
{

}

void GameMechs::setExitTrue()
{

void GameMechs::setLoseTrue()
{
    loseFlag = true;
    cout<<"Current score:"<<score<<endl;
}

void GameMechs::setInput(char this_input)
{

}

void GameMechs::clearInput()
{
    input =0;
}



void GameMechs::IncrementScore()
{
    score++;
}