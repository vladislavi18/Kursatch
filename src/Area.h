#ifndef KURSATCH3_AREA_H
#define KURSATCH3_AREA_H

#include "Cell.h"

class Area {
    int rowSize = 10, colSize = 10;
    std::vector<std::vector<Cell>> area;
    float posX, posY;
    float spriteSize = 32;


public:
    Area(Vector2f startPos = Vector2f(0, 0)) {
        posX = startPos.x;
        posY = startPos.y;
        for (int i = 0; i < rowSize; ++i) {
            std::vector<Cell> string;
            for (int j = 0; j < colSize; ++j) {
                Cell cell = *new Cell(posX, posY, CellState::Empty);
                string.push_back(cell);
                posX += spriteSize;
            }
            area.push_back(string);
            posY += spriteSize;
            posX = startPos.x;
        }
    }

    std::vector<Cell>& operator[](int index) {
        return area[index];
    }

    void Update(RenderWindow &window);

    void Draw(RenderWindow &window);

    void setShipByCoordinates(std::vector<Vector2f> coordinates);

    int getWidth();

    void deleteShipByCoordinates(std::vector<Vector2f> coordinates);

    Vector2f getSize();

};


#endif //KURSATCH3_AREA_H
