#include "floor.h"

void Floor::recursiveBacktracker(int startX, int startY){
    floor[startY][startX] = true;

    std::vector<int> directions = { 0, 1, 2, 3 };
    std::shuffle(directions.begin(), directions.end(), randomEngine);


    for (const auto& direction : directions) {
        int newX = startX;
        int newY = startY;

        switch (direction) {
        case 0:
            newY -= 2;
            if (newY >= 1 && floor[newY][newX] == false) {
                floor[static_cast<size_t>(newY) + 1][newX] = true;
                recursiveBacktracker(newX, newY);
            }
            break;
        case 1:
            newY += 2;
            if (newY < floor.size() - 1 && floor[newY][newX] == false) {
                floor[static_cast<size_t>(newY) - 1][newX] = true;
                recursiveBacktracker(newX, newY);
            }
            break;
        case 2:
            newX -= 2;
            if (newX >= 1 && floor[newY][newX] == false) {
                floor[newY][static_cast<size_t>(newX) + 1] = true;
                recursiveBacktracker(newX, newY);
            }
            break;
        case 3:
            newX += 2;
            if (newX < floor[0].size() - 1 && floor[newY][newX] == false) {
                floor[newY][static_cast<size_t>(newX) - 1] = true;
                recursiveBacktracker(newX, newY);
            }
            break;
        }
    }
}

void Floor::generateMaze(int sizeX, int sizeY) {
    floor.resize(sizeX, std::vector<bool>(sizeY));

    recursiveBacktracker();
}
