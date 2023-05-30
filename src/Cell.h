#ifndef KURSATCH3_CELL_H
#define KURSATCH3_CELL_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Textures.h"

using namespace sf;

enum CellState {
    Empty,
    Ship,
    Hit,
    Miss
};

class Cell {
    Sprite sprite;
    CellState state = CellState::Empty;
    Textures *textures = new Textures();

public:
    Cell(float posX, float posY, CellState newState) {
        sprite.setPosition(posX, posY);
        setTexture(newState);
    }

    void setTexture(CellState newState);

    Sprite &getSprite();

    CellState getState();

    void Update(RenderWindow &window);
};


#endif //KURSATCH3_CELL_H
