#ifndef KURSATCH3_PLAYER_H
#define KURSATCH3_PLAYER_H

#include "ShipMovement.h"
#include <SFML/Graphics.hpp>

class Player {
public:

    virtual void arrangeTheShipsAuto(RenderWindow *window) = 0;

    virtual void setEnemyArea(Area *enemyArea) = 0;

    virtual bool shipsIsAlive(RenderWindow &window) = 0;
};

class Player1 : public Player {
    std::vector<ship> ships;
    Area *myArea;
    Area *enemyArea;
    std::vector<std::vector<CellState>> enemyAreaC;

public:
    Player1() {
        Director *director = new Director();
        int decks = 4;
        int countShips = 1;
        while (decks > 0) {
            for (int j = 0; j < countShips; ++j) {
                ships.push_back(director->giveATask(decks, Vector2f(0, 0)));
            }
            countShips++;
            decks--;
        }
        myArea = new Area();
        enemyArea = new Area(Vector2f(myArea->getWidth() + myArea->getWidth() / 4, 0));
    }

    void setEnemyAreaC(std::vector<std::vector<CellState>> enemyAreaC);

    void Draw(RenderWindow *window);

    void shot(RenderWindow *window);

    void arrangeTheShips(RenderWindow *window);

    void arrangeTheShipsAuto(RenderWindow *window) override;

    void setEnemyArea(Area *enemyArea) override;

    bool shipsIsAlive(RenderWindow &window) override;

    Area *getMyArea();

    Area *getEnemyArea();

    int countAliveShips();
};

class moveCell {
    Vector2f coordinates;
    bool isStage = false;

public:
    moveCell(float i, float j) {
        coordinates = Vector2f(i, j);
    }

    void stage() {
        isStage = true;
    }

    Vector2f getCoordinates() {
        return coordinates;
    }
};

enum ShotState {
    Up,
    Down,
    Left,
    Right
};

class Bot : public Player {
    std::vector<ship> ships;
    Area *myArea;
    Area *enemyArea;
    std::vector<std::vector<CellState>> myAreaC;
    std::vector<moveCell> moves;
    bool isShip = false;
    ShotState shotState;
//    bool isUp = false;
//    bool isDown = false;
//    bool isLeft = false;
//    bool isRight = false;
    int countIsAliveEnemyShips;
    Vector2f prevCoor;
    Vector2f startCoor;
    CellState c = CellState::Empty;

public:
    Bot(Area *myArea, Area *enemyArea, int countIsAliveEnemyShips) {
        Director *director = new Director();
        int decks = 4;
        int countShips = 1;
        while (decks > 0) {
            for (int j = 0; j < countShips; ++j) {
                ships.push_back(director->giveATask(decks, Vector2f(0, 0)));
            }
            countShips++;
            decks--;
        }

        this->myArea = myArea;
        this->enemyArea = enemyArea;

        for (int i = 0; i < myArea->getSize().y; ++i) {
            std::vector<CellState> myAreaString;
            std::vector<CellState> enemyAreaString;
            for (int j = 0; j < myArea->getSize().x; ++j) {
                myAreaString.push_back((*myArea)[i][j].getState());
                enemyAreaString.push_back((*enemyArea)[i][j].getState());
            }
            this->myAreaC.push_back(myAreaString);
        }

        setVectorMoves();
        setVectorMoves(1);
        setVectorMoves(0);
        setVectorMoves(2);
        this->countIsAliveEnemyShips = countIsAliveEnemyShips;
    }

    void setVectorMoves(int value = 3);

    void Draw(RenderWindow *window);

    CellState shot(RenderWindow *window, int i, int j);

    void arrangeTheShipsAuto(RenderWindow *window) override;

    void setEnemyArea(Area *enemyArea) override;

    bool shipsIsAlive(RenderWindow &window) override;

    std::vector<std::vector<CellState>> GetMyArea();

    void moveBot(RenderWindow *window, int countAliveShips);
};


#endif
