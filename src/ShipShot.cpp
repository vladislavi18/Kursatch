//
// Created by Acer on 25.05.2023.
//

#include "ShipShot.h"
#include "Area.h"

bool ShipShot::takeAShot(RenderWindow &window, Cell cell, int i, int j) {
    int x = Mouse::getPosition(window).x;
    int y = Mouse::getPosition(window).y;

    Sprite sprite = cell.getSprite();
    if (x >= sprite.getGlobalBounds().left &&
        x <= sprite.getGlobalBounds().left + sprite.getGlobalBounds().width &&
        y >= sprite.getGlobalBounds().top &&
        y <= sprite.getGlobalBounds().top + sprite.getGlobalBounds().height) {

        if (cellStateArea[i][j] == CellState::Ship) {
            cellStateArea[i][j] = CellState::Hit;
            return true;
        } else if (cellStateArea[i][j] == CellState::Empty) {
            cellStateArea[i][j] = CellState::Miss;
            return true;
        }
    }
    return false;
}

std::vector<std::vector<CellState>> ShipShot::getCellStateArea() {
    return cellStateArea;
}

ShipShot::ShipShot(Area *area) {
    for (int i = 0; i < area->getSize().y; ++i) {
        std::vector<CellState> string;
        for (int j = 0; j < area->getSize().x; ++j) {
            string.push_back((*area)[i][j].getState());
        }
        cellStateArea.push_back(string);
    }
}

