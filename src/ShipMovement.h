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
    std::vector<std::vector<CellState>> enemyAreaC;

    bool isShip(Vector2f startCoordinates, float length);

public:
    ShipMovement(Area &area, ship *ship1) {
        this->area = area;
        this->ship1 = ship1;
    }

    ShipMovement(std::vector<std::vector<CellState>> &areaC, ship *ship1) {
        this->enemyAreaC = areaC;
        this->ship1 = ship1;
    }

    ~ShipMovement() {
        delete ship1;
    }

    void moveShip(RenderWindow &window, Area &area1);

    void autoPlacementShips(Area &area1, std::vector<std::vector<isShip1>> &shipsArea, bool isBot);

    bool
    findEmptyPlace(int startX, int startY, std::vector<std::vector<isShip1>> &shipsArea, std::vector<Vector2f> &coor);

    void autoPlacementShips(std::vector<std::vector<CellState>> *area1, std::vector<std::vector<isShip1>> &shipsArea, bool isBot);

};


#endif //KURSATCH3_SHIPMOVEMENT_H
