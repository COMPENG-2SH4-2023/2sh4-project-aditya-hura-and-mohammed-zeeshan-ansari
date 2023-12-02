#ifndef SNAKEFOOD_H
#define SNAKEFOOD_H

#include "objPos.h"

class SnakeFood {
public:
    SnakeFood();
    ~SnakeFood();

    void generateFood(objPos playerPos, int xRange, int yRange, const char* str);
    void getFoodPos(objPos& returnPos);

private:
    objPos foodPos;
    bool isFoodGenerated;
    bool charUsed[256];

    void resetCharUsed();
    void setFoodGenerated(bool value);
};

#endif
