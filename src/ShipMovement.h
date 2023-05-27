#ifndef KURSATCH3_SHIPMOVEMENT_H
#define KURSATCH3_SHIPMOVEMENT_H

#include "random"
#include "ship.h"

enum isShip1 {
    Sh,
    notSh
};

class ShipMovement {
    Area area;
    ship *ship1 = new ship(0, Vector2f(0, 0));

    bool isShip(Vector2f startCoordinates, float length);

public:
    ShipMovement(Area &area, ship *ship1) {
        this->area = area;
        this->ship1 = ship1;
    }

    ~ShipMovement() {
        delete ship1;
    }

    void moveShip(RenderWindow &window, Area &area1);

    void autoPlacementShips(Area &area1, std::vector<std::vector<isShip1>> &shipsArea);

    bool findCoordinate(int x, int y, std::vector<Vector2f> &coor, std::vector<std::vector<isShip1>> &shipsArea);

    bool findEmptyPlace(int startX, int startY, std::vector<std::vector<isShip1>> &shipsArea, std::vector<Vector2f> &coor);

    bool findEmptyPlaceForFourDecksShip(std::vector<std::vector<isShip1>> &shipsArea,
                                                      std::vector<Vector2f> &coor);
};


#endif //KURSATCH3_SHIPMOVEMENT_H
