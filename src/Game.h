//
// Created by Acer on 31.05.2023.
//

#ifndef KURSATCH3_GAME_H
#define KURSATCH3_GAME_H

#include "Player.h"

class state {
public:
    virtual void handle(RenderWindow &window) = 0;
};

class gameState : public state {
    Player1 *player;
    Bot *bot;
    bool isMovePlayer = true;
public:
    gameState(Player1 *player, Bot *bot) {
        this->player = player;
        this->bot = bot;
    }

    void handle(RenderWindow &window) override;
};

class endGameState : public state {
    sf::Text text;
public:
    endGameState(sf::Text text) {
        this->text = text;
    }

    void handle(RenderWindow &window) override;
};

class Game {
    sf::Font font;
private:
    state *state1;

    Game() {
        if (!font.loadFromFile(R"(D:\Program Files\CLionProjects\Kursatch3\fonts/arialmt.ttf)")) {
            // Обработка ошибки загрузки шрифта
            throw EXIT_FAILURE;
        }
    }

    ~Game() {}

public:
    // Метод для получения единственного экземпляра класса
    static Game *getInstance() {
        static auto *instance = new Game();
        return instance;
    }

    void setState(state *newState);

    void game(RenderWindow &window);
};


#endif //KURSATCH3_GAME_H
