#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "ship battle");
    window.setFramerateLimit(60);
    Game *game = Game::getInstance();
    game->game(window);
}
