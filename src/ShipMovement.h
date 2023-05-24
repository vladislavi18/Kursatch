#ifndef KURSATCH3_SHIPMOVEMENT_H
#define KURSATCH3_SHIPMOVEMENT_H

#include <iostream>
#include "ship.h"

class ShipMovement {
    Area area;
    ship ship1 = *new ship(0, Vector2f(0, 0));

    bool isShip(Vector2f startCoordinates, float length);

public:
    ShipMovement(Area &area, ship &ship1) {
        this->area = area;
        this->ship1 = ship1;
    }

    void moveShip(RenderWindow &window, Area &area1, ship &ship2);
};


#endif //KURSATCH3_SHIPMOVEMENT_H
