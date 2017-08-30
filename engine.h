//
// Created by fedya on 11.05.17.
//

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H



sf::RenderWindow window(sf::VideoMode(1920, 1080), "A Swagabitch game");

#include <list.h>
#include "ctrl_functions.h"
#include <math.h>


sf::Vector2i Start;
sf::Vector2i Now;
sf::Vector2i Finish;
const sf::Vector2u size = window.getSize();
const sf::Vector2i block_size(120, 120);
const int width = 16, height = 9;


#include "Lee.h"
#include "Engine_h.h"


template<typename T>
double Distance(sf::Vector2<T> a, sf::Vector2<T> b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void Engine::run() {

    window.clear();
    sf::Sprite background_sprite(background_image);
    sf::Sprite Allot_s(Allot_t);

    window.draw(background_sprite);
    window.display();


    sf::Clock clock;

    while (window.isOpen()) {
        window.setSize(sf::Vector2u(width * 120, height * 120));

        clock.restart();

        window.clear();
        sf::Event event;

        while (window.pollEvent(event))

            if (event.type == sf::Event::Closed)
                window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            break;


        window.draw(background_sprite);


        long long time = clock.getElapsedTime().asMicroseconds();

        if (objects) {
            for (auto elem = objects->first(); elem != objects->final(); elem++) {
                //elem.dump();
                auto object = (Character *) elem.data_;
                object->logic();
                object->control();
                object->move();
                object->draw();
                object->live();
            }
        }
        window.display();

        for (;clock.getElapsedTime().asMicroseconds() - time < 5e4;){}

    }
}

void Engine::Load_Map(const char *map_name) {

}

void Engine::clear_blocks(){
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            blocks[i][j].path = LEE_EMPTY;
        }
    }
}


#endif