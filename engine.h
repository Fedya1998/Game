//
// Created by fedya on 11.05.17.
//

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#endif

sf::RenderWindow window(sf::VideoMode(1920, 1080), "A Swagabitch game");

void Show_Kirill(){
    sf::Texture Kirill;
    Kirill.loadFromFile("/Users/gregpost/CLionProjects/TOPPRYGA/bg.jpg");
    sf::Sprite sprite(Kirill);
    window.draw(sprite);
    window.display();
}

bool FirstPress = true;
sf::Vector2i Start;
sf::Vector2i Now;

void Allot(sf::Sprite Allot_s) {
    if (FirstPress) {
        Start = sf::Mouse::getPosition(window);
        FirstPress = false;
    }
    Now = sf::Mouse::getPosition(window);
    if (Now.x > Start.x) {
        if (Now.y > Start.y) {
            Allot_s.setPosition(Start.x, Start.y);
            Allot_s.setTextureRect(sf::IntRect(0, 0, Now.x - Start.x, Now.y - Start.y));
        } else {
            Allot_s.setPosition(Start.x, Now.y);
            Allot_s.setTextureRect(sf::IntRect(0, 0, Now.x - Start.x, Start.y - Now.y));
        }
    } else {
        if (Now.y > Start.y) {
            Allot_s.setPosition(Now.x, Start.y);
            Allot_s.setTextureRect(sf::IntRect(0, 0, Start.x - Now.x, Now.y - Start.y));
        } else {
            Allot_s.setPosition(Now.x, Now.y);
            Allot_s.setTextureRect(sf::IntRect(0, 0, Start.x - Now.x, Start.y - Now.y));
        }
    }
    window.draw(Allot_s);
}

#include <list.h>
#include "body_functions.h"




class Engine {
public:
    sf::Texture background_image;
    sf::Texture Allot_t;

    char bg_path[100] = "/Users/gregpost/CLionProjects/TOPPRYGA/bg.jpg";

    void run();

    Engine(List<Physical_Body> &objects) :objects(objects) {
        background_image.loadFromFile(bg_path);
        Allot_t.loadFromFile("/Users/gregpost/CLionProjects/Копия TOPPRYGA/Allot.png");
    };

    ~Engine() {};


    List<Physical_Body> &objects;

private:
    void logic();
};

void Engine::run() {

    //sf::Clock clock;
    window.clear();
    sf::Sprite background_sprite(background_image);
    sf::Sprite Allot_s(Allot_t);
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
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            Allot(Allot_s);
        } else {
            if (!FirstPress) FirstPress = true;
        }

       // window.draw(health_line);
        //int time = (int) clock.getElapsedTime().asMicroseconds();
        for (auto elem = objects.first(); elem != objects.final(); elem++) {
            //elem.dump();
            auto object = (Character *) elem.data_;
            object->logic(objects);
            object->control();
            object->move((List <Movable> &)objects);
            object->draw();
            object->live(&elem);

        }
        window.display();
    }
}



