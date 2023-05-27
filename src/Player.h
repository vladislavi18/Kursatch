//
// Created by Acer on 22.05.2023.
//

#ifndef KURSATCH3_PLAYER_H
#define KURSATCH3_PLAYER_H

#include "ShipMovement.h"
#include <SFML/Graphics.hpp>

class Player {
    std::vector<ship> ships;
    Area *myArea;
    Area *enemyArea;

public:
    Player(int i) {
        Director *director = new Director();
        int decks = 4;
        int countShips = 1;
        while (decks > 0) {
            for (int j = 0; j < countShips; ++j) {
                ships.push_back(director->giveATask(decks, Vector2f(0, 0)));
            }
            countShips++;
            decks--;
        }
        if(i == 0) {
            myArea = new Area();
            enemyArea = new Area(Vector2f(myArea->getWidth() + myArea->getWidth() / 4, 0));
        }
        else {
            myArea = new Area(Vector2f(0, 320 + 50));
            enemyArea = new Area(Vector2f(320+ 50, 320 + 50));
        }

    }

    void Draw(RenderWindow *window);

    void shot(RenderWindow *window);

    void arrangeTheShips(RenderWindow *window);

    void arrangeTheShipsAuto(RenderWindow *window);

    void setEnemyArea(Area *enemyArea);

    Area* getMyArea();
};


#endif //KURSATCH3_PLAYER_H
