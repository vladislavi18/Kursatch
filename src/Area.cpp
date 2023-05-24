//
// Created by Acer on 20.05.2023.
//

#include "Area.h"

void Area::Update(RenderWindow &window) {
    for (auto & i : area) {
        for (auto & j : i) {
            j.Update(window);
        }
    }
}

void Area::Draw(RenderWindow &window) {
    for (int i = 0; i < area.size(); ++i) {
        for (int j = 0; j < area[i].size(); ++j) {
            window.draw(area[i][j].getSprite());
        }
    }
}

void Area::setShipByCoordinates(std::vector<Vector2f> coordinates) {
    for (auto & coordinate : coordinates) {
        area[coordinate.y][coordinate.x].setTexture(CellState::Ship);
    }
}

int Area::getWidth() {
    return rowSize * spriteSize;
}

Vector2f Area::getSize() {
    return Vector2f(rowSize, colSize);
}

void Area::deleteShipByCoordinates(std::vector<Vector2f> coordinates) {
    for (auto & coordinate : coordinates) {
        area[coordinate.y][coordinate.x].setTexture(CellState::Empty);
    }
}
