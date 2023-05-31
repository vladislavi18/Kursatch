//
// Created by Acer on 22.05.2023.
//

#include "Player.h"

void Player1::Draw(RenderWindow *window) {
    myArea->Draw(*window);
}

CellState Player1::shot(RenderWindow *window) {
    ShipShot *shipShot = new ShipShot(enemyAreaC);
    CellState c = enemyArea->shot(*window, shipShot);
    return c;
}


void Player1::arrangeTheShips(RenderWindow *window) {
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

void Player1::arrangeTheShipsAuto(RenderWindow *window) {
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
            shipMovement->autoPlacementShips(*myArea, shipsArea, false);
            Draw(window);
            window->display();
        }
    }
}

void Player1::setEnemyArea(Area *enemyArea) {
    this->enemyArea = enemyArea;
}

Area *Player1::getMyArea() {
    return myArea;
}

bool Player1::shipsIsAlive(RenderWindow &window) {
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

        window.clear(Color::White);
        window.draw(text);
        window.display();
        sleep(seconds(5));
        window.close();
    }
}

Area *Player1::getEnemyArea() {
    return enemyArea;
}

void Player1::setEnemyAreaC(std::vector<std::vector<CellState>> enemyAreaC) {
    this->enemyAreaC = enemyAreaC;
}

int Player1::countAliveShips() {
    int count = 0;
    for (auto &ship: ships) {
        if (ship.IsAlive(*myArea))
            count++;
    }
    return count;
}

void Bot::Draw(RenderWindow *window) {
    myArea->Draw(*window);
}

CellState Bot::shot(RenderWindow *window, int i, int j) {
    ShipShot *shipShot = new ShipShot(enemyArea);
    CellState c = enemyArea->shotBot(*window, shipShot, i, j);
    return c;
}

void Bot::arrangeTheShipsAuto(RenderWindow *window) {
    std::vector<std::vector<isShip1>> shipsArea;
    for (int i = 0; i < myArea->getSize().y; ++i) {
        std::vector<isShip1> string;
        for (int j = 0; j < myArea->getSize().x; ++j) {
            string.push_back(isShip1::notSh);
        }
        shipsArea.push_back(string);
    }

    for (auto &ship: ships) {
        ShipMovement *shipMovement = new ShipMovement(myAreaC, &ship);
        while (!ship.getIsStage()) {
            window->clear(Color::White);
            shipMovement->autoPlacementShips(&myAreaC, shipsArea, true);
            Draw(window);
            window->display();
        }
    }
}

void Bot::setEnemyArea(Area *enemyArea) {
    this->enemyArea = enemyArea;
}

bool Bot::shipsIsAlive(RenderWindow &window) {
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

        sf::Text text("Bot lose? You Win!", font, 48);
        text.setFillColor(sf::Color::Black);
        text.setStyle(sf::Text::Bold);
        text.setPosition(window.getSize().x / 2 - text.getGlobalBounds().width / 2,
                         window.getSize().y / 2 - text.getGlobalBounds().height / 2);

        window.clear(Color::White);
        window.draw(text);
        window.display();
        sleep(seconds(5));
        window.close();
    }
}

std::vector<std::vector<CellState>> Bot::GetMyArea() {
    return myAreaC;
}

CellState Bot::moveBot(RenderWindow *window, int countAliveShips) {
    if (countAliveShips < this->countIsAliveEnemyShips) {
        isShip = false;
        this->countIsAliveEnemyShips = countAliveShips;
        c = CellState::Empty;
        for (int i = 0; i < enemyArea->getSize().y; ++i) {
            for (int j = 0; j < enemyArea->getSize().x; ++j) {
                if ((*enemyArea)[i][j].getState() != CellState::Empty &&
                    (*enemyArea)[i][j].getState() != CellState::Ship) {
                    for (int k = 0; k < moves.size(); ++k) {
                        if (Vector2f((float) j, (float) i) == moves[k].getCoordinates()) {
                            moves.erase(moves.begin() + k);
                            break;
                        }
                    }
                }
            }
        }
    }
    if (c == CellState::Hit || isShip) {
        if (!isShip && prevCoor.y - 1 >= 0) {
            c = shot(window, prevCoor.y - 1, prevCoor.x);
            if (c == CellState::Hit) {
                shotState = ShotState::Up;
                prevCoor = Vector2f(prevCoor.x, prevCoor.y - 1);
            } else {
                shotState = ShotState::Down;
            }
            isShip = true;
            startCoor = prevCoor;
        } else if (!isShip && prevCoor.y + 1 < myArea->getSize().y) {
            c = shot(window, prevCoor.y + 1, prevCoor.x);
            if (c == CellState::Hit) {
                shotState = ShotState::Down;
                prevCoor = Vector2f(prevCoor.x, prevCoor.y + 1);
            } else {
                shotState = ShotState::Left;
            }
            isShip = true;
            startCoor = prevCoor;
        } else if (shotState == ShotState::Up) {
            if (prevCoor.y - 1 >= 0) {
                c = shot(window, prevCoor.y - 1, prevCoor.x);
                if (c == CellState::Hit) {
                    shotState = ShotState::Up;
                    prevCoor = Vector2f(prevCoor.x, prevCoor.y - 1);
                } else {
                    prevCoor = startCoor;
                    shotState = ShotState::Down;
                }
            } else {
                shotState = ShotState::Down;
            }
        } else if (shotState == ShotState::Down) {
            if (prevCoor.y + 1 < myArea->getSize().y) {
                c = shot(window, prevCoor.y + 1, prevCoor.x);
                if (c == CellState::Hit) {
                    shotState = ShotState::Down;
                    prevCoor = Vector2f(prevCoor.x, prevCoor.y + 1);
                } else {
                    prevCoor = startCoor;
                    shotState = ShotState::Left;
                }
            } else {
                shotState = ShotState::Left;
            }
        } else if (shotState == ShotState::Left) {
            if (prevCoor.x - 1 >= 0) {
                c = shot(window, prevCoor.y, prevCoor.x - 1);
                if (c == CellState::Hit) {
                    shotState = ShotState::Left;
                    prevCoor = Vector2f(prevCoor.x - 1, prevCoor.y);
                } else {
                    prevCoor = startCoor;
                    shotState = ShotState::Right;
                }
            } else {
                shotState = ShotState::Right;
            }
        } else if (shotState == ShotState::Right) {
            if (prevCoor.x + 1 < myArea->getSize().x) {
                c = shot(window, prevCoor.y, prevCoor.x + 1);
                if (c == CellState::Hit) {
                    shotState = ShotState::Right;
                    prevCoor = Vector2f(prevCoor.x + 1, prevCoor.y);
                } else {
                    prevCoor = startCoor;
                    shotState = ShotState::Left;
                }
            } else {
                shotState = ShotState::Up;
            }
        }

    } else {
        c = shot(window, moves[0].getCoordinates().y, moves[0].getCoordinates().x);
        if (c == CellState::Hit)
            prevCoor = moves[0].getCoordinates();
        moves.erase(moves.begin());
    }
    return c;
}

void Bot::setVectorMoves(int value) {
    int i = 0;
    while (i < myArea->getSize().x) {
        int j;
        i == 0 ? j = value : j = 3;
        while (j >= 0) {
            int k = j;
            while (k < myArea->getSize().y) {
                moves.push_back(moveCell(i, k)); // i и k потому что в координатах сначала x потом y
                k += 4;
            }
            j--;
            i++;
            if (i > myArea->getSize().x - 1)
                break;
        }
    }

}
