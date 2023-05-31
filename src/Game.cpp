//
// Created by Acer on 31.05.2023.
//

#include "Game.h"

void Game::game(RenderWindow &window) {
    Player1 *player = new Player1();
    player->arrangeTheShipsAuto(&window);

    int countAliveShips = player->countAliveShips();
    Bot *bot = new Bot(player->getEnemyArea(), player->getMyArea(), countAliveShips);
    bot->arrangeTheShipsAuto(&window);

    player->setEnemyAreaC(bot->GetMyArea());

    setState(new gameState(player, bot));
    bool isMovePlayer = true;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        state1->handle(window);

        bool isAlivePlayer = player->shipsIsAlive(window);
        bool isAliveBot = bot->shipsIsAlive(window);
        if (!isAlivePlayer)
            setState(new endGameState(sf::Text("You are lose, Bot wins", font, 48)));
        else if (!isAliveBot)
            setState(new endGameState(sf::Text("Bot lose? You Win!", font, 48)));
    }
}

void Game::setState(state *newState) {
    state1 = newState;
}

void gameState::handle(RenderWindow &window) {
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

    int countAliveShips = player->countAliveShips();
    if (!isMovePlayer) {
        CellState c = bot->moveBot(&window, countAliveShips);
        if (c == CellState::Miss)
            isMovePlayer = true;

    }

    window.display();
}

void endGameState::handle(RenderWindow &window) {
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(window.getSize().x / 2 - text.getGlobalBounds().width / 2,
                     window.getSize().y / 2 - text.getGlobalBounds().height / 2);

    window.clear(Color::White);
    window.draw(text);
    window.display();
    sleep(seconds(5));
    window.close();
}
