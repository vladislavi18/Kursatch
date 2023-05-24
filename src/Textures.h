#ifndef KURSATCH3_TEXTURES_H
#define KURSATCH3_TEXTURES_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class Textures {
    Texture emptyTexture;
    Texture shipTexture;
    Texture hitTexture;
    Texture missTexture;

public:
    Textures() {
        if (!emptyTexture.loadFromFile(R"(D:\Program Files\CLionProjects\Kursatch3\resources/emptyTexture.png)")) {
            std::cerr << "Error load empty texture\n";
            throw std::exception();
        }

        if (!shipTexture.loadFromFile(R"(D:\Program Files\CLionProjects\Kursatch3\resources/shipTexture.png)")) {
            std::cerr << "Error load ship texture\n";
            throw std::exception();
        }

        if (!hitTexture.loadFromFile(R"(D:\Program Files\CLionProjects\Kursatch3\resources/hitTexture.png)")) {
            std::cerr << "Error load hit texture\n";
            throw std::exception();
        }

        if (!missTexture.loadFromFile(R"(D:\Program Files\CLionProjects\Kursatch3\resources/missTexture.png)")) {
            std::cerr << "Error load miss texture\n";
            throw std::exception();
        }
    }

    Texture &getEmptyTexture();

    Texture &getShipTexture();

    Texture &getHitTexture();

    Texture &getMissTexture();
};


#endif //KURSATCH3_TEXTURES_H
