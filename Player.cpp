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

    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2, '*');
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    

    // more actions to be included
}

Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
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

    int yChange,xChange;
    // PPA3 Finite State Machine logic
    if (!((prevDirection == UP && myDir == DOWN) ||
            (prevDirection == DOWN && myDir == UP) ||
            (prevDirection == LEFT && myDir == RIGHT) ||
            (prevDirection == RIGHT && myDir == LEFT)))
    {
        prevDirection = myDir;
    }
    objPos currentPos;
    playerPosList->getHeadElement(currentPos);
    switch (prevDirection)
    {
    case UP:
        if (currentPos.y > 1)
        {
            currentPos.y--;
        }
        else
        {
            currentPos.y = mainGameMechsRef->getBoardSizeY() - 2;
        }
        break;
    case DOWN:
        if (currentPos.y < mainGameMechsRef->getBoardSizeY() - 2)
        {
            currentPos.y++;
        }
        else
        {
            currentPos.y = 1;
        }
        break;
    case LEFT:
        if (currentPos.x > 1)
        {
            currentPos.x--;
        }
        else
        {
            currentPos.x = mainGameMechsRef->getBoardSizeX() - 2;
        }
        break;
    case RIGHT:
        if (currentPos.x < mainGameMechsRef->getBoardSizeX() - 2)
        {
            currentPos.x++;
        }
        else
        {
            currentPos.x = 1;
        }
        break;
    }
    // Calculate new head position


    // Insert new head position to the front of the list
    playerPosList->insertHead(currentPos);

    // Remove the last element from the list
    playerPosList->removeTail();
}