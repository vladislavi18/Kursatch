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

//    Area area1 = *new Area();


//    Vector2f v = {0, 0};
//    Vector2f v1 = {0, 0};
//    Director director = *new Director();
//    ship ship1 = director.giveATask(3, v);
//    ship ship2 = director.giveATask(3, v1);
//    ship1.setDirection(Direction::Vertical);
//    ship1.shot();
//    ship1.setShip(area1);

//    ship2.setDirection(Direction::Vertical);
//    ship2.shot();
//    ship2.setShip(area1);

    Player *player = new Player(0);
    player->arrangeTheShipsAuto(&window);


    Player *player1 = new Player(1);
    player1->arrangeTheShipsAuto(&window);

    player->setEnemyArea(player1->getMyArea());
    player1->setEnemyArea(player->getMyArea());

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear(Color::White);

        player->Draw(&window);
        player1->Draw(&window);

        window.display();

        player->shot(&window);

        player->Draw(&window);
        player1->Draw(&window);

        player1->shipsIsAlive(window);

        window.display();
    }
    return 0;
}


