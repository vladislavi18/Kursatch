//
// Created by Acer on 22.05.2023.
//

#ifndef KURSATCH3_PLAYER_H
#define KURSATCH3_PLAYER_H

#include <iostream>
#include "ship.h"
#include "ShipMovement.h"
#include <SFML/Graphics.hpp>

class Player {
    std::vector<ship> ships;
    Area myArea;
    Area enemyArea;

public:
    Player() {
        Director director = *new Director();
        int decks = 1;
        int countShips = 4;
        while (countShips > 0) {
            for (int j = 0; j < countShips; ++j) {
                ships.push_back(director.giveATask(decks, Vector2f(0, 0)));
            }
            countShips--;
            decks++;
        }
        myArea = *new Area();
        enemyArea = *new Area(Vector2f(myArea.getWidth() + myArea.getWidth() / 4, 0));
    }

    Area dwtMyArea() {
        return myArea;
    }

    void Draw(RenderWindow &window);

    void Update(RenderWindow &window);

    void arrangeTheShips(RenderWindow &window);
};


#endif //KURSATCH3_PLAYER_H
