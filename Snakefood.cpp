
#include "SnakeFood.h"
#include <cstdlib>
#include <ctime>
#include <string.h>

SnakeFood::SnakeFood() {
    isFoodGenerated = false;
    resetCharUsed();
    srand(time(NULL));
}

SnakeFood::~SnakeFood() {
    // Destructor, if needed
}

void SnakeFood::resetCharUsed() {
    for (int i = 0; i < 256; ++i) {
        charUsed[i] = false;
    }
}

void SnakeFood::generateFood(objPos playerPos, int xRange, int yRange, const char* str) {
    if (!isFoodGenerated) {
        do {
            foodPos.x = 1 + rand() % (xRange - 2);
            foodPos.y = 1 + rand() % (yRange - 2);

            // Check if food overlaps with player position
            if (foodPos.x == playerPos.x && foodPos.y == playerPos.y) {
                continue;
            }

            // Check if food has already been generated at this position
            if (charUsed[(unsigned char)foodPos.symbol]) {
                continue;
            }

            // Generate a random symbol for the food
            do {
                foodPos.symbol = str[rand() % strlen(str)];
            } while (charUsed[(unsigned char)foodPos.symbol]);

            charUsed[(unsigned char)foodPos.symbol] = true;

            // Food generation successful
            isFoodGenerated = true;
            break;
        } while (true);
    }
}

void SnakeFood::getFoodPos(objPos& returnPos) {
    returnPos = foodPos;
}

void SnakeFood::setFoodGenerated(bool value) {
    isFoodGenerated = value;
}
