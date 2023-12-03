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
    gameMechs = new GameMechs(30,15);
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
    objPosArrayList playerPosList;
    player->getPlayerPos();
    snakeFood->generateFood(&playerPosList, gameMechs->getBoardSizeX(), gameMechs->getBoardSizeY(), "$");
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    objPosArrayList* playerPosList = player->getPlayerPos();

    objPos FoodPos;
    snakeFood->getFoodPos(FoodPos);

    bool isPlayerSymbol;

    for (int i = 0; i < gameMechs->getBoardSizeY(); i++)
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
            else
            {
                isPlayerSymbol = false;

                // Check if the current position is occupied by the player
                for (int k = 0; k < playerPosList->getSize(); k++)
                {
                    objPos currentPlayerPos;
                    playerPosList->getElement(currentPlayerPos, k);

                    if (currentPlayerPos.x == j && currentPlayerPos.y == i)
                    {
                        cout << currentPlayerPos.symbol;
                        isPlayerSymbol = true;
                        break;
                    }
                }

                // If not occupied by the player, check for food
                if (!isPlayerSymbol && i == FoodPos.y && j == FoodPos.x)
                {
                    cout << FoodPos.symbol; // draw food
                }
                else if (!isPlayerSymbol)
                {
                    cout << " "; // empty space between border
                }
            }
        }
    }
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