#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include <iostream>
#include "definitions.h"
#include "Snakefood.h"

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    
    playerPos.setObjPos(10, 10, '*');

    // more actions to be included
}

Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos = playerPos;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();
    if (input != 0)
    {
        switch (input)
        {
        case 'w':
            myDir = UP;
            break;
        case 's':
            myDir = DOWN;
            break;
        case 'a':
            myDir = LEFT;
            break;
        case 'd':
            myDir = RIGHT;
            break;
        case ' ':
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseTrue();
            break;
        }
        mainGameMechsRef->clearInput();
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    if (!((prevDirection == UP && myDir == DOWN) ||
            (prevDirection == DOWN && myDir == UP) ||
            (prevDirection == LEFT && myDir == RIGHT) ||
            (prevDirection == RIGHT && myDir == LEFT)))
    {
        prevDirection = myDir;
    }
    switch (prevDirection)
    {
    case UP:
        if (playerPos.y > 1)
        {
            playerPos.y--;
        }
        else
        {
            playerPos.y = mainGameMechsRef->getBoardSizeY() - 2;
        }
        break;
    case DOWN:
        if (playerPos.y < mainGameMechsRef->getBoardSizeY() - 2)
        {
            playerPos.y++;
        }
        else
        {
            playerPos.y = 1;
        }
        break;
    case LEFT:
        if (playerPos.x > 1)
        {
            playerPos.x--;
        }
        else
        {
            playerPos.x = mainGameMechsRef->getBoardSizeX() - 2;
        }
        break;
    case RIGHT:
        if (playerPos.x < mainGameMechsRef->getBoardSizeX() - 2)
        {
            playerPos.x++;
        }
        else
        {
            playerPos.x = 1;
        }
        break;
    }
}
