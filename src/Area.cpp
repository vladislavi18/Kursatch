//
// Created by Acer on 20.05.2023.
//

#include "Area.h"

using namespace sf;


void Area::shot(RenderWindow &window, ShipShot *shipShot) {
    bool isChangeState = false;
    while (!isChangeState) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            for (int i = 0; i < area.size(); ++i) {
                for (int j = 0; j < area[i].size(); ++j) {
                    isChangeState = shipShot->takeAShot(window, area[i][j], i, j);
                    if (isChangeState) {
                        area[i][j].setTexture(shipShot->getCellStateArea()[i][j]);
                        break;
                    }
                }
                if (isChangeState)
                    break;
            }
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
    for (auto &coordinate: coordinates) {
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
    for (auto &coordinate: coordinates) {
        area[coordinate.y][coordinate.x].setTexture(CellState::Empty);
    }
}
