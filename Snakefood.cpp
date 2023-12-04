
#include "SnakeFood.h"
#include <cstdlib>
#include <ctime>
#include <string.h>
#include "objPosArrayList.h"

SnakeFood::SnakeFood()
{
    foodPos.setObjPos(12, 12, '$');
}

// Inside the SnakeFood class implementation
void SnakeFood::generateFood(objPosArrayList *playerPosList, int xRange, int yRange)
{
    int bitVector[xRange][yRange] = {0};
    for (int i = 0; i < playerPosList->getSize(); i++)
    {
        objPos playerPos;
        playerPosList->getElement(playerPos, i);
        bitVector[playerPos.x][playerPos.y] = 1;
    }

    bool generated = false;
    int x, y;
    while (!generated)
    {
        x = 1 + rand() % (xRange - 2);
        y = 1 + rand() % (yRange - 2);

        if (!bitVector[x][y])
        {
            bitVector[x][y] = 1;
            generated = true;
        }
        foodPos.setObjPos(x, y, foodPos.getSymbol());
    }
    
}

void SnakeFood::getFoodPos(objPos &returnPos)
{
    returnPos = foodPos;
}