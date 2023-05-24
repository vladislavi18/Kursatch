//
// Created by Acer on 21.05.2023.
//

#include "ship.h"

int ship::getLength() {
    return length;
}

int ship::getDirection() {
    return direction;
}

void ship::setShip(Area &area) {
    area.setShipByCoordinates(coordinates);
}

void ship::deleteShip(Area &area) {
    area.deleteShipByCoordinates(coordinates);
}

void ship::setCoordinate(Vector2f startPos) {
    coordinates.clear();
    coordinates.push_back(startPos);
    Vector2f curPos = startPos;
    for (int i = 1; i < length; ++i) {
        if (direction == Direction::Horizontal)
            curPos.x++;
        else
            curPos.y++;

        coordinates.push_back(curPos);
    }
}

void ship::setIsStage() {
    isStage = true;
}

void ship::Update() {
    setCoordinate(coordinates[0]);
}

void ship::setDirection(Direction newDirection) {
    direction = newDirection;
}

std::vector<Vector2f> ship::getCoordinates() {
    return coordinates;
}

bool ship::getIsStage() {
    return isStage;
}

ship Builder::buildTheShip(Vector2f startPos) {
    return ship{numberOfDecks, startPos};
}

ship Builder::getShip() {
    return *ship1;
}
