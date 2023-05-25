//
// Created by Acer on 22.05.2023.
//

#include "Player.h"

void Player::Draw(RenderWindow *window) {
    myArea.Draw(*window);
    enemyArea.Draw(*window);
}

void Player::Update(RenderWindow *window) {
    myArea.Update(*window);
    enemyArea.Update(*window);
}


void Player::arrangeTheShips(RenderWindow *window) {
    for (auto &ship: ships) {
        ShipMovement *shipMovement = new ShipMovement(myArea, &ship);
        while (!ship.getIsStage()) {
            window->clear(Color::White);
            shipMovement->moveShip(*window, myArea);
            Draw(window);
            window->display();
        }
    }
}

void Player::arrangeTheShipsAuto(RenderWindow *window) {
    std::vector<std::vector<isShip1>> shipsArea;
    for (int i = 0; i < myArea.getSize().y; ++i) {
        std::vector<isShip1> string;
        for (int j = 0; j < myArea.getSize().x; ++j) {
            string.push_back(isShip1::notSh);
        }
        shipsArea.push_back(string);
    }

    for (auto &ship: ships) {
        ShipMovement *shipMovement = new ShipMovement(myArea, &ship);
        while (!ship.getIsStage()) {
            window->clear(Color::White);
            shipMovement->autoPlacementShips(myArea, shipsArea);
//            sleep(seconds(1));
            Draw(window);
            window->display();
        }
    }
}
