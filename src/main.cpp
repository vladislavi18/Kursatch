#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;


int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    Text text;
    Font font;
    font.loadFromFile(R"(D:\Program Files\CLionProjects\Kursatch3\fonts/arialmt.ttf)");
    text.setFont(font);
    text.setString("Морской бой");

    sf::RenderWindow window(sf::VideoMode(800, 800), "ship battle");
    window.setFramerateLimit(60);
    Textures textures = *new Textures();


    Cell cell1 = *new Cell(0.f, 0.f, CellState::Ship);
    Cell cell2 = *new Cell(32.f, 0.f, CellState::Empty);
    Cell cell3 = *new Cell(64.f, 0.f, CellState::Hit);
    Cell cell4 = *new Cell(96.f, 0.f, CellState::Miss);

    Player1 *player = new Player1();
    player->arrangeTheShipsAuto(&window);

    int countAliveShips = player->countAliveShips();
    Bot *bot = new Bot(player->getEnemyArea(), player->getMyArea(), countAliveShips);
    bot->arrangeTheShipsAuto(&window);

    player->setEnemyAreaC(bot->GetMyArea());

    bool isMovePlayer = true;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(Color::White);

        player->Draw(&window);
        bot->Draw(&window);

        window.display();

        if (isMovePlayer) {
            CellState c = player->shot(&window);
            if (c == CellState::Miss)
                isMovePlayer = false;
        }

        player->Draw(&window);
        bot->Draw(&window);

        sleep(seconds(1));

        countAliveShips = player->countAliveShips();
        if (!isMovePlayer) {
            CellState c = bot->moveBot(&window, countAliveShips);
            if (c == CellState::Miss)
                isMovePlayer = true;
        }

        player->shipsIsAlive(window);
        bot->shipsIsAlive(window);

        window.display();
    }
    return 0;
}


