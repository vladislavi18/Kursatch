//
// Created by Acer on 22.05.2023.
//

#include "Player.h"

void Player::Draw(RenderWindow *window) {
    myArea->Draw(*window);
    enemyArea->Draw(*window);
}

void Player::shot(RenderWindow *window) {
    ShipShot *shipShot = new ShipShot(enemyArea);
    enemyArea->shot(*window, shipShot);
}


void Player::arrangeTheShips(RenderWindow *window) {
    for (auto &ship: ships) {
        ShipMovement *shipMovement = new ShipMovement(*myArea, &ship);
        while (!ship.getIsStage()) {
            window->clear(Color::White);
            shipMovement->moveShip(*window, *myArea);
            Draw(window);
            window->display();
        }
    }
}

void Player::arrangeTheShipsAuto(RenderWindow *window) {
    std::vector<std::vector<isShip1>> shipsArea;
    for (int i = 0; i < myArea->getSize().y; ++i) {
        std::vector<isShip1> string;
        for (int j = 0; j < myArea->getSize().x; ++j) {
            string.push_back(isShip1::notSh);
        }
        shipsArea.push_back(string);
    }

    for (auto &ship: ships) {
        ShipMovement *shipMovement = new ShipMovement(*myArea, &ship);
        while (!ship.getIsStage()) {
            window->clear(Color::White);
            shipMovement->autoPlacementShips(*myArea, shipsArea);
            Draw(window);
            window->display();
        }
    }
}

void Player::setEnemyArea(Area *enemyArea) {
    this->enemyArea = enemyArea;
}

Area *Player::getMyArea() {
    return myArea;
}

bool Player::shipsIsAlive(RenderWindow &window) {
    int countAliveShips = ships.size();
    for (auto &ship: ships) {
        if (!ship.IsAlive(*myArea)) {
            countAliveShips--;
            int x1 = ship.getCoordinates()[0].x;
            int x2 = ship.getCoordinates()[ship.getLength() - 1].x;
            int y1 = ship.getCoordinates()[0].y;
            int y2 = ship.getCoordinates()[ship.getLength() - 1].y;
            if (ship.getCoordinates()[0].x - 1 >= 0)
                x1 = ship.getCoordinates()[0].x - 1;
            if (ship.getCoordinates()[ship.getLength() - 1].x + 1 < myArea->getSize().x)
                x2 = ship.getCoordinates()[ship.getLength() - 1].x + 1;
            if (ship.getCoordinates()[0].y - 1 >= 0)
                y1 = ship.getCoordinates()[0].y - 1;
            if (ship.getCoordinates()[ship.getLength() - 1].y + 1 < myArea->getSize().y)
                y2 = ship.getCoordinates()[ship.getLength() - 1].y + 1;

            for (int i = y1; i < y2 + 1; ++i) {
                for (int j = x1; j < x2 + 1; ++j) {
                    bool isShip = false;
                    for (int k = 0; k < ship.getCoordinates().size(); ++k) {
                        if (Vector2f((float) j, (float) i) == ship.getCoordinates()[k]) {
                            isShip = true;
                        }
                    }
                    if (!isShip) {
                        (*myArea)[i][j].setTexture(CellState::Miss);
                    }
                }
            }
        }
    }
    if (countAliveShips == 0) {
        sf::Font font;
        if (!font.loadFromFile(R"(D:\Program Files\CLionProjects\Kursatch3\fonts/arialmt.ttf)")) {
            // Обработка ошибки загрузки шрифта
            return EXIT_FAILURE;
        }

        sf::Text text("You are lose, Bot wins", font, 48);
        text.setFillColor(sf::Color::Black);
        text.setStyle(sf::Text::Bold);
        text.setPosition(window.getSize().x / 2 - text.getGlobalBounds().width / 2,
                         window.getSize().y / 2 - text.getGlobalBounds().height / 2);

        window.draw(text);
        window.display();
        sleep(seconds(5));
        window.close();
    }
}
