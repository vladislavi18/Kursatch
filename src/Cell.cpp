//
// Created by Acer on 20.05.2023.
//

#include "Cell.h"

void Cell::setTexture(CellState newState) {
    state = newState;

    switch (state) {
        case CellState::Empty:
            sprite.setTexture(textures->getEmptyTexture());
            break;
        case CellState::Ship:
            sprite.setTexture(textures->getShipTexture());
            break;
        case CellState::Hit:
            sprite.setTexture(textures->getHitTexture());
            break;
        case CellState::Miss:
            sprite.setTexture(textures->getMissTexture());
            break;
    }
    sprite.setScale(0.5f, 0.5f);
}

Sprite &Cell::getSprite() {
    return sprite;
}

CellState Cell::getState() {
    return state;
}

void Cell::Update(RenderWindow &window) {
    if (Mouse::isButtonPressed(Mouse::Left)) {
        int x = Mouse::getPosition(window).x;
        int y = Mouse::getPosition(window).y;

        if (x >= sprite.getGlobalBounds().left &&
            x <= sprite.getGlobalBounds().left + sprite.getGlobalBounds().width &&
            y >= sprite.getGlobalBounds().top &&
            y <= sprite.getGlobalBounds().top + sprite.getGlobalBounds().height) {

            if (state == CellState::Ship)
                setTexture(CellState::Hit);
            else if (state == CellState::Empty)
                setTexture(CellState::Miss);
        }
    }
}