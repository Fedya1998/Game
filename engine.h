//
// Created by fedya on 11.05.17.
//

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#endif

#include "Character.h"
#include <list.h>

class Engine {
public:
    sf::RenderWindow window;
    sf::Texture background_image;
    char bg_path[] = "/home/fedya/Изображения/Wallpapers/1lec598puuE.jpg";

    void run();

    Engine(): window(sf::VideoMode(1920, 1080), "A Swagabitch game"){
        background_image.loadFromFile(bg_path);
    };

    ~Engine() {};


    List<Character> *objects = NULL;
private:
    void logic();
};

void Engine::run() {
    window.clear();
    sf::Sprite background_sprite(background_image);
    window.draw(background_sprite);
    window.display();

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            break;

        for (auto elem = objects->first(); elem != objects->final(); elem++) {
            //elem.dump();
            auto object = elem.data_;
            object->control();
            object->move();
            object->draw(window);
        }
        window.display();
    }
}



