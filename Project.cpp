#include <iostream>
#include <string>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "SnakeFood.h"
#include "objPosArrayList.h"
#include "definitions.h"

Player *player;
GameMechs *gameMechs;
SnakeFood *snakeFood;
using namespace std;
string debug;

#define DELAY_CONST 100000

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while (gameMechs->getExitFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    gameMechs = new GameMechs();
    player = new Player(gameMechs);
    snakeFood = new SnakeFood();

    exitFlag = false;
}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        gameMechs->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    player->updatePlayerDir();
    player->movePlayer();

    if (gameMechs->getInput() == ' ')
    {
        gameMechs->setLoseTrue();
        gameMechs->clearInput();
    }
    objPos playerPos;
    player->getPlayerPos(playerPos);
    snakeFood->generateFood(playerPos, boardSizeX, boardSizeY, "$");
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    objPos playerPos;
    player->getPlayerPos(playerPos);

    objPos FoodPos;
    snakeFood->getFoodPos(FoodPos);

    for (int i = 0; i < gameMechs->getBoardSizeY(); ++i)
    {
        for (int j = 0; j <= gameMechs->getBoardSizeX(); j++)
        {
            if (j == gameMechs->getBoardSizeX())
            {
                cout << endl;
            }
            else if (i == 0 || i == gameMechs->getBoardSizeY() - 1 || j == 0 || j == gameMechs->getBoardSizeX() - 1)
            {
                cout << "#"; // make border
            }
            else if (playerPos.x == j && playerPos.y == i)
            {

                cout << playerPos.symbol;
            }
            else if (i == FoodPos.y && j == FoodPos.x)
            {
                cout << FoodPos.symbol; // draw food
            }
            else
            {
                cout << " "; // empty space between border
            }
        }
    }
    cout << "DEBUG" << endl << playerPos.toString() << endl;
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();
    delete player;
    delete gameMechs;
    delete snakeFood;
    MacUILib_uninit();
}