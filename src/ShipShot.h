//
// Created by Acer on 25.05.2023.
//

#ifndef KURSATCH3_SHIPSHOT_H
#define KURSATCH3_SHIPSHOT_H

#include "Cell.h"
class Area;

using namespace sf;

class ShipShot {
    std::vector<std::vector<CellState>> cellStateArea;

public:
    explicit ShipShot(Area *area);

    ShipShot(std::vector<std::vector<CellState>> cellStateArea) {
        this->cellStateArea = cellStateArea;
    }

    bool takeAShot(RenderWindow &window, Cell cell, int i, int j);

    void takeAShotBot(RenderWindow &window, int i, int j);

    std::vector<std::vector<CellState>> getCellStateArea();

};


#endif //KURSATCH3_SHIPSHOT_H
