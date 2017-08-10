//
// Created by fedya on 11.05.17.
//

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#endif

const sf::Vector2u My_Resolution(1920, 1080);
const sf::Vector2u Square_Size(48, 48);
const sf::Vector2u Grid_Size(My_Resolution.x / Square_Size.x, My_Resolution.y / Square_Size.y);

sf::RenderWindow window(sf::VideoMode(My_Resolution.x, My_Resolution.y), "A Swagabitch game");

void Show_Kirill(){
    sf::Texture Kirill;
    Kirill.loadFromFile("/home/fedya/Изображения/Game images/Kirill.jpg");
    sf::Sprite sprite(Kirill);
    window.draw(sprite);
    window.display();
}

#include <list.h>
#include "body_functions.h"

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


class Engine {
public:
    sf::Texture background_image;
    sf::Texture Allot_t;
    char bg_path[100] = "/home/fedya/Изображения/Game images/bg.jpg";

private:
    unsigned grid[Grid_Size.x][Grid_Size.y];

public:
    void run();

    Engine(List<Physical_Body> &objects) :objects(objects) {
        background_image.loadFromFile(bg_path);
        Allot_t.loadFromFile("/home/fedya/Изображения/Game images/texture.jpg");
    };
    void Find_Path(sf::Vector2i start, sf::Vector2i dest);

    ~Engine() {};

    List<Physical_Body> &objects;

private:
    void logic();
};

void Engine::run() {
    enum {
        GRID_BLANK = -1,
        GRID_WALL = -2,
        GRID_OCCUPIED_BY_CHAR = -10
    };

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

        //int time = (int) clock.getElapsedTime().asMicroseconds();
        //sf::Vector2i mouse_pos
        for (auto elem = objects.first(); elem != objects.final(); elem++) {
            //elem.dump();
            auto object = (Character *) elem.data_;
            object->logic(objects);
            if (object->selected)
                object->control();
            object->move((List <Movable> &)objects);
            object->draw();
            object->live(&elem);

        }
        window.display();
    }
}

void Engine::Find_Path(sf::Vector2i start, sf::Vector2i dest) {
    unsigned grid_now[Grid_Size.x][Grid_Size.y];
    for (int i = 0; i < Grid_Size.x * Grid_Size.y; i++)
        grid_now[i] = grid[i];

    sf::Vector2i deltas [4] = {(1, 0), (0, 1), (-1, 0), (0, -1)};
    unsigned length = 0;

    bool stop = true;
    while (stop) {
        stop = false;
        for (int x = 0; x < Grid_Size.x; x++) {
            for (int y = 0; y < Grid_Size.y; y++) {
                if (grid[x][y] == length){
                    for (int i = 0; i < 4; i++){
                        sf::Vector2i square_now(x,y);
                        square_now += deltas[i];
                        if (square_now.x > 0 & square_now.y > 0 &
                            square_now.x < Grid_Size.x & square_now.y < Grid_Size.y &
                            grid_now[square_now.x][square_now.y] == GRID_BLANK){
                            stop = true;
                            grid_now[square_now.x][square_now.y] = length + 1;
                        }
                    }
                }
            }
        }
        length++;
    }


}




