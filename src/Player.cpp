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
        ShipMovement shipMovement = *new ShipMovement(myArea, &ship);
        while (!ship.getIsStage()) {
            window->clear(Color::White);
            shipMovement.moveShip(*window, myArea, &ship);
            Draw(window);
            window->display();
        }
    }
}
