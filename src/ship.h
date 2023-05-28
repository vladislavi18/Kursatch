#ifndef KURSATCH3_SHIP_H
#define KURSATCH3_SHIP_H

#include <iostream>
#include "Area.h"
#include <SFML/Graphics.hpp>

using namespace sf;

enum Direction {
    Horizontal,
    Vertical
};

class ship {
    int length;
    std::vector<Vector2f> coordinates;
    float textureSize = 32;
    Direction direction = Horizontal;
    bool isStage = false;
    bool isAlive = true;

public:
    ship(int length, Vector2f startPos) {
        this->length = length;
        setCoordinate(startPos);
    }

    void setIsStage();

    bool getIsStage();

    void setCoordinate(Vector2f startPos);

    void deleteShip(Area &area);

    int getLength();

    int getDirection();

    void setShip(Area &area);

    void setDirection(Direction newDirection);

    void Update();

    bool IsAlive(Area area);

    std::vector<Vector2f> getCoordinates();

};


class Builder {
    ship *ship1 = new ship(0, Vector2f(0, 0));
    int numberOfDecks;

    ship buildTheShip(Vector2f startPos);

public:
    Builder(int numberOfDecks, Vector2f startPos) {
        this->numberOfDecks = numberOfDecks;
        *ship1 = buildTheShip(startPos);
    }

    ~Builder() {
        delete ship1;
    }

    ship getShip();
};

class Director {
    Builder *builder = new Builder(0, Vector2f(0, 0));

public:
    ~Director() {
        delete builder;
    }

    ship giveATask(int numberOfDecks, Vector2f startPos) {
        builder = new Builder(numberOfDecks, startPos);
        return builder->getShip();
    }
};

#endif //KURSATCH3_SHIP_H
