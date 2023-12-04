#ifndef SNAKEFOOD_H
#define SNAKEFOOD_H

#include "objPos.h"
#include "objPosArrayList.h"

class SnakeFood
{
private:
    objPos foodPos;

public:
    SnakeFood(); // Constructor to set xRange and yRange

    void generateFood(objPosArrayList *playerPosList, int xRange, int yRange);
    void getFoodPos(objPos& returnPos);
};

#endif // SNAKEFOOD_H

