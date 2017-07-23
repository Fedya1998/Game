//
// Created by fedya on 11.05.17.
//

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#endif

#include "Character.h"
#include <list.h>



float PhysF(float v0, float a, float time) {
    float v;
    if (v0 > 0) v = v0 + (a - 0.08) * time;
    if (v0 > 5) v = 5;
    return v;
}

float PhysR(float v0, float a, float time) {
    float v;
    if (v0 < 0) v = v0 + (-a + 0.08) * time;
    if (v0 < -5) v = -5;
    return v;
}

class Engine {
public:
    sf::Texture background_image;

    char bg_path[100] = "/home/fedya/Изображения/Game images/bg.jpg";

    void run();

    Engine() {
        background_image.loadFromFile(bg_path);
    };

    ~Engine() {};


    List<Character> *objects = NULL;
private:
    void logic();
};

void Engine::run() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "A Swagabitch game");
    //sf::Clock clock;
    window.clear();
    sf::Sprite background_sprite(background_image);
    window.draw(background_sprite);
    window.display();

    while (window.isOpen()) {
        window.clear();
        sf::Event event;

        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            break;

        //clock.restart();
        window.draw(background_sprite);

        //int time = (int) clock.getElapsedTime().asMicroseconds();
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



