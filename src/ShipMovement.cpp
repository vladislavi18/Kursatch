//
// Created by Acer on 23.05.2023.
//

#include "ShipMovement.h"

bool ShipMovement::isShip(Vector2f startCoordinates, float length) {
    std::vector<Vector2f> coor;
    coor.push_back(startCoordinates);
    Vector2f curPos = startCoordinates;
    for (int i = 1; i < length; ++i) {
        if (ship1->getDirection() == Direction::Horizontal)
            curPos.x++;
        else
            curPos.y++;

        coor.push_back(curPos);
    }

    bool isShip = false;

    int x1 = coor[0].x;
    int x2 = coor[ship1->getLength() - 1].x;
    int y1 = coor[0].y;
    int y2 = coor[ship1->getLength() - 1].y;
    if (coor[0].x - 1 >= 0)
        x1 = coor[0].x - 1;
    if (coor[ship1->getLength() - 1].x + 1 < area.getSize().x)
        x2 = coor[ship1->getLength() - 1].x + 1;
    if (coor[0].y - 1 >= 0)
        y1 = coor[0].y - 1;
    if (coor[ship1->getLength() - 1].y + 1 < area.getSize().y)
        y2 = coor[ship1->getLength() - 1].y + 1;

    for (int i = x1; i < x2 + 1; ++i) {
        for (int j = y1; j < y2 + 1; ++j) {
            bool isCoor = false;
            for (int k = 0; k < coor.size(); ++k) {
                if (Vector2f((float) i, (float) j) == coor[k]) {
                    isCoor = true;
                    break;
                }
            }
            if (area[j][i].getState() == CellState::Ship && !isCoor) {
                isShip = true;
                break;
            }
        }
    }

    return isShip;
}

void ShipMovement::moveShip(RenderWindow &window, Area &area1) {
    std::vector<Vector2f> coordinates = ship1->getCoordinates();
    float length = ship1->getLength();
    Vector2f startCoordinates = coordinates[0];
    bool isEvent = false;
    bool isEnter = false;
    Event event{};
    int lengthForMovementY, lengthForMovementX;
    if (ship1->getDirection() == Direction::Vertical) {
        lengthForMovementY = length;
        lengthForMovementX = 1;
    } else {
        lengthForMovementY = 1;
        lengthForMovementX = length;
    }
    while (window.pollEvent(event)) {
        if (event.type == Event::KeyPressed) {
            coordinates = ship1->getCoordinates();
            startCoordinates = coordinates[0];
            if (event.key.code == Keyboard::W && startCoordinates.y > 0) {
                if (ship1->getDirection() == Direction::Vertical) {
                    if (area[startCoordinates.y - 1][startCoordinates.x].getState() !=
                        CellState::Ship) {
                        startCoordinates.y -= 1;
                        isEvent = true;
                        break;
                    }
                } else {
                    int count = 0;
                    for (int i = 0; i < lengthForMovementX; ++i) {
                        if ((area[startCoordinates.y - 1][startCoordinates.x + i].getState() !=
                             CellState::Ship))
                            count++;
                    }
                    if (count == lengthForMovementX) {
                        startCoordinates.y -= 1;
                        isEvent = true;
                        break;
                    }
                }
            } else if (event.key.code == Keyboard::S && startCoordinates.y + lengthForMovementY < area.getSize().y) {
                if (ship1->getDirection() == Direction::Vertical) {
                    if (area[startCoordinates.y + lengthForMovementY][startCoordinates.x].getState() !=
                        CellState::Ship) {
                        startCoordinates.y += 1;
                        isEvent = true;
                        break;
                    }
                } else {
                    int count = 0;
                    for (int i = 0; i < lengthForMovementX; ++i) {
                        if ((area[startCoordinates.y + 1][startCoordinates.x + i].getState() !=
                             CellState::Ship))
                            count++;
                    }
                    if (count == lengthForMovementX) {
                        startCoordinates.y += 1;
                        isEvent = true;
                        break;
                    }
                }
            } else if (event.key.code == Keyboard::A && startCoordinates.x > 0) {
                if (ship1->getDirection() == Direction::Horizontal) {
                    if (area[startCoordinates.y][startCoordinates.x - 1].getState() !=
                        CellState::Ship) {
                        startCoordinates.x -= 1;
                        isEvent = true;
                        break;
                    }
                } else {
                    int count = 0;
                    for (int i = 0; i < lengthForMovementY; ++i) {
                        if ((area[startCoordinates.y + i][startCoordinates.x - 1].getState() !=
                             CellState::Ship))
                            count++;
                    }
                    if (count == lengthForMovementY) {
                        startCoordinates.x -= 1;
                        isEvent = true;
                        break;
                    }
                }
            } else if (event.key.code == Keyboard::D && startCoordinates.x + lengthForMovementX < area.getSize().x) {
                if (ship1->getDirection() == Direction::Horizontal) {
                    if (area[startCoordinates.y][startCoordinates.x + lengthForMovementX].getState() !=
                        CellState::Ship) {
                        startCoordinates.x += 1;
                        isEvent = true;
                        break;
                    }
                } else {
                    int count = 0;
                    for (int i = 0; i < lengthForMovementY; ++i) {
                        if ((area[startCoordinates.y + i][startCoordinates.x + 1].getState() !=
                             CellState::Ship))
                            count++;
                    }
                    if (count == lengthForMovementY) {
                        startCoordinates.x += 1;
                        isEvent = true;
                        break;
                    }
                }
            } else if (event.key.code == Keyboard::R) {
                if (ship1->getDirection() == Direction::Horizontal) {
                    if (coordinates[ship1->getLength() - 1].y - (length - 1) >= 0) {
                        int count = 0;
                        for (int i = 1; i < lengthForMovementX; ++i) {
                            if (area[startCoordinates.y - i][startCoordinates.x].getState() !=
                                CellState::Ship)
                                count++;
                        }
                        if (count == lengthForMovementX - 1) {
                            startCoordinates = Vector2f(startCoordinates.x,
                                                        coordinates[ship1->getLength() - 1].y - (length - 1));
                            ship1->setDirection(Direction::Vertical);
                        }
                    } else if (coordinates[ship1->getLength() - 1].y + (length - 1) <= area.getSize().y) {
                        int count = 0;
                        for (int i = 1; i < lengthForMovementX; ++i) {
                            if (area[startCoordinates.y + i][startCoordinates.x].getState() !=
                                CellState::Ship)
                                count++;
                        }
                        if (count == lengthForMovementX - 1) {
                            startCoordinates = Vector2f(startCoordinates.x,
                                                        coordinates[ship1->getLength() - 1].y);
                            ship1->setDirection(Direction::Vertical);
                        }
                    }

                } else {
                    if (coordinates[ship1->getLength() - 1].x - (length - 1) >= 0) {
                        int count = 0;
                        for (int i = 1; i < lengthForMovementY; ++i) {
                            if (area[startCoordinates.y][startCoordinates.x - i].getState() !=
                                CellState::Ship) {
                                count++;
                            }
                            if (count == lengthForMovementY - 1) {
                                startCoordinates = Vector2f(coordinates[ship1->getLength() - 1].x - (length - 1),
                                                            startCoordinates.y);
                                ship1->setDirection(Direction::Horizontal);
                            }
                        }
                    } else if (coordinates[ship1->getLength() - 1].x + (length - 1) <= area.getSize().x) {
                        int count = 0;
                        for (int i = 1; i < lengthForMovementY; ++i) {
                            if (area[startCoordinates.y][startCoordinates.x + i].getState() !=
                                CellState::Ship) {
                                count++;
                            }
                            if (count == lengthForMovementY - 1) {
                                startCoordinates = Vector2f(coordinates[ship1->getLength() - 1].x,
                                                            startCoordinates.y);
                                ship1->setDirection(Direction::Horizontal);
                            }
                        }
                    }
                }
                isEvent = true;
            } else if (event.key.code == Keyboard::Enter) {
                if (!isShip(startCoordinates, length)) {
                    isEvent = true;
                    isEnter = true;
                    break;
                }
            }
        }
    }

    if (isEvent) {
        if (!ship1->getIsStage()) {
            ship1->deleteShip(area);
        }
        ship1->setCoordinate(startCoordinates);
        ship1->setShip(area);

        if (isEnter) {
            ship1->setIsStage();
        }
        area1 = area;
    }
}

bool ShipMovement::findEmptyPlace(int startX, int startY, std::vector<std::vector<isShip1>> &shipsArea,
                                  std::vector<Vector2f> &coor) {
    if (ship1->getDirection() == Direction::Horizontal) {
        for (int i = startY; i < shipsArea.size(); ++i) {
            int countEmptyPlace = 0;
            for (int j = startX; j < shipsArea[0].size(); ++j) {
                if (shipsArea[i][j] == isShip1::notSh) {
                    countEmptyPlace++;
                    coor.push_back(Vector2f((float) j, (float) i));
                    if (countEmptyPlace == ship1->getLength()) {
                        return true;
                    }
                } else {
                    coor.clear();
                    countEmptyPlace = 0;
                }
            }
        }
    } else if (ship1->getDirection() == Direction::Vertical) {
        for (int i = startX; i < shipsArea[0].size(); ++i) {
            int countEmptyPlace = 0;
            for (int j = startY; j < shipsArea.size(); ++j) {
                if (shipsArea[i][j] == isShip1::notSh) {
                    countEmptyPlace++;
                    coor.push_back(Vector2f((float) i, (float) j));
                    if (countEmptyPlace == ship1->getLength()) {
                        return true;
                    }
                } else {
                    coor.clear();
                    countEmptyPlace = 0;
                }
            }
        }
    }
    return false;
}

void ShipMovement::autoPlacementShips(Area &area1, std::vector<std::vector<isShip1>> &shipsArea, bool isBot = false) {
    srand(time(nullptr));
    int x = rand() % shipsArea[0].size();
    int y = rand() % shipsArea.size();

    Direction direction = (Direction) (rand() % 2);
    ship1->setDirection(direction);

    std::vector<Vector2f> coor;

    bool isEmptyPlace = findEmptyPlace(x, y, shipsArea, coor);


    if (isEmptyPlace) {
        bool isCanPutAShip = true;

        int x1 = coor[0].x;
        int x2 = coor[ship1->getLength() - 1].x;
        int y1 = coor[0].y;
        int y2 = coor[ship1->getLength() - 1].y;
        if (coor[0].x - 1 >= 0)
            x1 = coor[0].x - 1;
        if (coor[ship1->getLength() - 1].x + 1 < area.getSize().x)
            x2 = coor[ship1->getLength() - 1].x + 1;
        if (coor[0].y - 1 >= 0)
            y1 = coor[0].y - 1;
        if (coor[ship1->getLength() - 1].y + 1 < area.getSize().y)
            y2 = coor[ship1->getLength() - 1].y + 1;

        for (int i = x1; i < x2 + 1; ++i) {
            for (int j = y1; j < y2 + 1; ++j) {
                if (shipsArea[j][i] == isShip1::Sh) {
                    isCanPutAShip = false;
                    break;
                }
            }
            if (!isCanPutAShip)
                break;
        }

        if (isCanPutAShip) {
            for (auto &i: coor) {
                shipsArea[i.y][i.x] = isShip1::Sh;
            }

            ship1->setCoordinate(coor[0]);
            if (!isBot)
                ship1->setShip(area);
            else {
                for (auto &i: coor) {
                    enemyAreaC[i.y][i.x] = CellState::Ship;
                }
            }
            ship1->setIsStage();

            area1 = area;
        }
    }
}

void ShipMovement::autoPlacementShips(std::vector<std::vector<CellState>> *area1,
                                      std::vector<std::vector<isShip1>> &shipsArea, bool isBot = false) {
    srand(time(nullptr));
    int x = rand() % shipsArea[0].size();
    int y = rand() % shipsArea.size();

    Direction direction = (Direction) (rand() % 2);
    ship1->setDirection(direction);

    std::vector<Vector2f> coor;

    bool isEmptyPlace = findEmptyPlace(x, y, shipsArea, coor);


    if (isEmptyPlace) {
        bool isCanPutAShip = true;

        int x1 = coor[0].x;
        int x2 = coor[ship1->getLength() - 1].x;
        int y1 = coor[0].y;
        int y2 = coor[ship1->getLength() - 1].y;
        if (coor[0].x - 1 >= 0)
            x1 = coor[0].x - 1;
        if (coor[ship1->getLength() - 1].x + 1 < area.getSize().x)
            x2 = coor[ship1->getLength() - 1].x + 1;
        if (coor[0].y - 1 >= 0)
            y1 = coor[0].y - 1;
        if (coor[ship1->getLength() - 1].y + 1 < area.getSize().y)
            y2 = coor[ship1->getLength() - 1].y + 1;

        for (int i = x1; i < x2 + 1; ++i) {
            for (int j = y1; j < y2 + 1; ++j) {
                if (shipsArea[j][i] == isShip1::Sh) {
                    isCanPutAShip = false;
                    break;
                }
            }
            if (!isCanPutAShip)
                break;
        }

        if (isCanPutAShip) {
            for (auto &i: coor) {
                shipsArea[i.y][i.x] = isShip1::Sh;
            }

            ship1->setCoordinate(coor[0]);
            if (!isBot)
                ship1->setShip(area);
            else {
                for (auto &i: coor) {
                    enemyAreaC[i.y][i.x] = CellState::Ship;
                }
            }
            ship1->setIsStage();

            *area1 = enemyAreaC;
        }
    }
}