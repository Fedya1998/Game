//
// Created by fedya on 11.05.17.
//

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#endif

sf::RenderWindow window(sf::VideoMode(1920, 1080), "A Swagabitch game");

std::string Images_Dir("/home/fedya/Изображения/Game images/");

void Show_Kirill() {
    sf::Texture Kirill;
    Kirill.loadFromFile(Images_Dir + "Kirill.jpg");
    sf::Sprite sprite(Kirill);
    window.draw(sprite);
    window.display();
}

#include <list.h>
#include "body_functions.h"


sf::Vector2i Start;
sf::Vector2i Now;
sf::Vector2i Finish;


bool FirstPress = true, FirstPress1 = true, FirstPress2 = true, StartSet = false;


template<typename T>
double Distance(sf::Vector2<T> a, sf::Vector2<T> b) {//Теперь работает для любых векторов. Например, sf::Vector2i, sf::Vector2f (но они оба должны быть одинакового типа)
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}


class Point {
public:
    int wave = -1;
    sf::Vector2i point_pos;
    bool passable = true,//Указатель на то, что на блоке (тип сделать лучше как physical_body, т.к. тогда не будет проблем, если там то, что наследуется из тела)
            allotment = false,
            partOfJorney = false;
};


class Block {
public:
    sf::Vector2i FocusOn;
    sf::Texture block_tex;
    sf::Sprite block_spr;

    Block() {
        block_tex.loadFromFile(Images_Dir + "wall.jpg");
        sf::Sprite sprite(block_tex);
        block_spr = sprite;
        int width = block_tex.getSize().x;
        int height = block_tex.getSize().y;
        block_spr.setOrigin(width / 2, height / 2);
    }

    void Create(class Point blocks[][16]) {

        float max = 1000000;
        if (FirstPress1) {
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 16; j++) {
                    //Убрать это
                    if (Distance(sf::Mouse::getPosition(window), blocks[i][j].point_pos) < max) {
                        max = Distance(sf::Mouse::getPosition(window), blocks[i][j].point_pos);
                        sf::Vector2i vector(i, j);
                        FocusOn = vector;
                    }
                }
            if (blocks[FocusOn.x][FocusOn.y].passable) {
                blocks[FocusOn.x][FocusOn.y].passable = false;
                block_spr.setPosition(blocks[FocusOn.x][FocusOn.y].point_pos.x,
                                      blocks[FocusOn.x][FocusOn.y].point_pos.y);
            } else
                blocks[FocusOn.x][FocusOn.y].passable = true;
        }
        FirstPress1 = false;
    }

    void ShowBlocks(class Point blocks[][16]) {
        int i, j;
        for (i = 0; i < 9; i++)
            for (j = 0; j < 16; j++)
                if (blocks[i][j].passable == false) {
                    block_spr.setPosition(blocks[i][j].point_pos.x, blocks[i][j].point_pos.y);
                    window.draw(block_spr);
                }
        //sf::Vector2i vector(0, 0);
        //FocusOn = vector;
    }
};


class Traveler : public Point {
public:

    sf::Vector2i FocusOn;
    sf::Texture travel_tex;
    sf::Sprite travel_spr;

    sf::Vector2i Start, Finish;

    Traveler() {
        travel_tex.loadFromFile(Images_Dir + "path.jpg");
        sf::Sprite sprite(travel_tex);
        travel_spr = sprite;
        int width = travel_tex.getSize().x;
        int height = travel_tex.getSize().y;
        travel_spr.setOrigin(width / 2, height / 2);
    }

    void create(class Point blocks[][16]) {
        int i, j;
        float min = 1000000;
        if (FirstPress2) {
            for (i = 0; i < 9; i++)
                for (j = 0; j < 16; j++) {
                    if (!StartSet)
                        blocks[i][j].partOfJorney = false;
                    if (Distance(sf::Mouse::getPosition(window), blocks[i][j].point_pos) < min) {//Это всё тоже
                        min = Distance(sf::Mouse::getPosition(window), blocks[i][j].point_pos);
                        sf::Vector2i vector(i, j);
                        FocusOn = vector;
                    }
                }
            if ((blocks[FocusOn.x][FocusOn.y].passable) && !StartSet) {
                travel_spr.setPosition(blocks[FocusOn.x][FocusOn.y].point_pos.x,
                                       blocks[FocusOn.x][FocusOn.y].point_pos.y);
                Start = FocusOn;
                StartSet = true;
                blocks[FocusOn.x][FocusOn.y].wave = 0;
            } else if (StartSet && (blocks[FocusOn.x][FocusOn.y].passable)) {
                StartSet = false;
                sf::Vector2i vector(FocusOn.x, FocusOn.y);
                Finish = vector;
            }

        }
        FirstPress2 = false;
    }

    void Wave(/*class*/ Point blocks[][16]) {//Зачем в таких местах писать class? Так делают только в структурах, когда не знают про typedef
        for (int k = 0; k < 400; k++) {
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 16; j++) {
                    if ((blocks[i][j].wave >= 0) && (blocks[i][j].passable)) {//Попроще
                        if ((blocks[i - 1][j].wave < 0) && blocks[i - 1][j].passable)
                            blocks[i - 1][j].wave = blocks[i][j].wave + 1;
                        if ((blocks[i][j - 1].wave < 0) && blocks[i][j - 1].passable)
                            blocks[i][j - 1].wave = blocks[i][j].wave + 1;
                        if ((blocks[i + 1][j].wave < 0) && blocks[i + 1][j].passable)
                            blocks[i + 1][j].wave = blocks[i][j].wave + 1;
                        if ((blocks[i][j + 1].wave < 0) && blocks[i][j + 1].passable)
                            blocks[i][j + 1].wave = blocks[i][j].wave + 1;
//                      if ((blocks[i - 1][j - 1].wave < 0) && blocks[i - 1][j - 1].passable)
//                          blocks[i - 1][j - 1].wave = blocks[i][j].wave + 1;
//                      if ((blocks[i - 1][j + 1].wave < 0) && blocks[i - 1][j + 1].passable)
//                          blocks[i - 1][j + 1].wave = blocks[i][j].wave + 1;
//                      if ((blocks[i + 1][j - 1].wave < 0) && blocks[i + 1][j - 1].passable)
//                          blocks[i + 1][j - 1].wave = blocks[i][j].wave + 1;
//                      if ((blocks[i + 1][j + 1].wave < 0) && blocks[i + 1][j + 1].passable)
//                          blocks[i + 1][j + 1].wave = blocks[i][j].wave + 1;
                    }
                }
            }
        }
    }

    void GoBack(class Point blocks[][16]) {
        int k;
        for (k = 0; k < 1000; k++) {
            if (blocks[Finish.x][Finish.y - 1].wave - blocks[Finish.x][Finish.y].wave == -1) {
                Finish.y = Finish.y - 1;
                travel_spr.setPosition(blocks[Finish.x][Finish.y].point_pos.x, blocks[Finish.x][Finish.y].point_pos.y);
                blocks[Finish.x][Finish.y].partOfJorney = true;
            } else if (blocks[Finish.x][Finish.y + 1].wave - blocks[Finish.x][Finish.y].wave == -1) {
                Finish.y = Finish.y + 1;
                travel_spr.setPosition(blocks[Finish.x][Finish.y].point_pos.x, blocks[Finish.x][Finish.y].point_pos.y);
                blocks[Finish.x][Finish.y].partOfJorney = true;
            } else if (blocks[Finish.x - 1][Finish.y].wave - blocks[Finish.x][Finish.y].wave == -1) {
                Finish.x = Finish.x - 1;
                travel_spr.setPosition(blocks[Finish.x][Finish.y].point_pos.x, blocks[Finish.x][Finish.y].point_pos.y);
                blocks[Finish.x][Finish.y].partOfJorney = true;
            } else if (blocks[Finish.x + 1][Finish.y].wave - blocks[Finish.x][Finish.y].wave == -1) {
                Finish.x = Finish.x + 1;
                travel_spr.setPosition(blocks[Finish.x][Finish.y].point_pos.x, blocks[Finish.x][Finish.y].point_pos.y);
                blocks[Finish.x][Finish.y].partOfJorney = true;
            } //else
//            if (blocks[Finish.x - 1][Finish.y - 1].wave - blocks[Finish.x][Finish.y].wave == -1) {
//                Finish.y = Finish.y - 1;
//                Finish.x = Finish.x - 1;
//                travel_spr.setPosition(blocks[Finish.x][Finish.y].point_pos.x, blocks[Finish.x][Finish.y].point_pos.y);
//                blocks[Finish.x][Finish.y].partOfJorney = true;
//            } else
//            if (blocks[Finish.x + 1][Finish.y - 1].wave - blocks[Finish.x][Finish.y].wave == -1) {
//                Finish.y = Finish.y - 1;
//                Finish.x = Finish.x + 1;
//                travel_spr.setPosition(blocks[Finish.x][Finish.y].point_pos.x, blocks[Finish.x][Finish.y].point_pos.y);
//                blocks[Finish.x][Finish.y].partOfJorney = true;
//            } else
//            if (blocks[Finish.x - 1][Finish.y + 1].wave - blocks[Finish.x][Finish.y].wave == -1) {
//                Finish.y = Finish.y + 1;
//                Finish.x = Finish.x - 1;
//                travel_spr.setPosition(blocks[Finish.x][Finish.y].point_pos.x, blocks[Finish.x][Finish.y].point_pos.y);
//                blocks[Finish.x][Finish.y].partOfJorney = true;
//            } else
//            if (blocks[Finish.x + 1][Finish.y + 1].wave - blocks[Finish.x][Finish.y].wave == -1) {
//                Finish.y = Finish.y + 1;
//                Finish.x = Finish.x + 1;
//                travel_spr.setPosition(blocks[Finish.x][Finish.y].point_pos.x, blocks[Finish.x][Finish.y].point_pos.y);
//                blocks[Finish.x][Finish.y].partOfJorney = true;
//            }
        }
    }

    void ShowJorney(class Point blocks[][16]) {
        int i, j;
        for (i = 0; i < 9; i++)
            for (j = 0; j < 16; j++)
                if (blocks[i][j].partOfJorney) {
                    travel_spr.setPosition(blocks[i][j].point_pos.x, blocks[i][j].point_pos.y);
                    window.draw(travel_spr);
                }
    }
};


class Mysh {

public:
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
};


class Engine : public Mysh {
public:


    sf::Texture background_image;
    sf::Texture Allot_t;
    Point blocks[9][16];
    Block AlgoritmLi;

    std::string bg_path = Images_Dir + "bg.jpg";

    void run();

    Engine(List<Physical_Body> &objects) : objects(objects) {

        blocks[0][0].point_pos.x = 60;
        blocks[0][0].point_pos.y = 60;
        for (int i = 0, j = 0; i < 9; i++) {
            if ((i != 0) || (j != 0)) {
                blocks[i][0].point_pos.y = blocks[i - 1][0].point_pos.y + 120;
                blocks[i][0].point_pos.x = blocks[i - 1][0].point_pos.x;
            }
            for (j = 1; j < 16; j++) {
                if ((i != 0) || (j != 0)) {
                    blocks[i][j].point_pos.x = blocks[i][j - 1].point_pos.x + 120;
                    blocks[i][j].point_pos.y = blocks[i][j - 1].point_pos.y;
                }
            }
        }
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 16; j++)
                if (((i < 1) || (i > 7)) || ((j < 1) || (j > 14)))
                    blocks[i][j].passable = false;

        background_image.loadFromFile(bg_path);
        Allot_t.loadFromFile(Images_Dir + "texture.jpg");

    };

    ~Engine() {};


    List<Physical_Body> &objects;

private:
    void logic();

};


void Engine::run() {

    Traveler bob;
    window.clear();
    sf::Sprite background_sprite(background_image);
    sf::Sprite Allot_s(Allot_t);

    window.draw(background_sprite);
    window.display();



    ////
    sf::Clock clock;
    ////
    while (window.isOpen()) {
        ////
        clock.restart();
        ////
        window.clear();
        sf::Event event;

        while (window.pollEvent(event))

            if (event.type == sf::Event::Closed)
                window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            break;


        window.draw(background_sprite);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            Allot(Allot_s);
            bob.create(blocks);
            if (!StartSet) {
                bob.Wave(blocks);
                bob.GoBack(blocks);
            }
        } else {
            if (!FirstPress) {
                FirstPress = true;
                FirstPress2 = true;
            }
        }

        bob.ShowJorney(blocks);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            AlgoritmLi.Create(blocks);
        } else {
            if (!FirstPress1)
                FirstPress1 = true;
        }
        AlgoritmLi.ShowBlocks(blocks);

        ////
        long long time = clock.getElapsedTime().asMicroseconds();
        ////
        for (auto elem = objects.first(); elem != objects.final(); elem++) {
            //elem.dump();
            auto object = (Character *) elem.data_;
            object->logic(objects);
            object->control();
            //object->move((List <Movable> &)objects);
            //object->draw();
            //object->live(&elem);
        }
        window.display();
        ////
        for (;clock.getElapsedTime().asMicroseconds() - time < 5e4;){}
        ////
    }
}



