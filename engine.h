//
// Created by fedya on 11.05.17.
//

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#endif

sf::RenderWindow window(sf::VideoMode(1920, 1080), "A Swagabitch game");

std::string Images_Dir("/Users/gregpost/CLionProjects/Копия TOPPRYGA/");

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
sf::Vector2u size = window.getSize();
const unsigned int width = size.x / 120, height = size.y / 120;


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
        block_tex.loadFromFile(Images_Dir + "wall.png");
        sf::Sprite sprite(block_tex);
        block_spr = sprite;
        int Block_width = block_tex.getSize().x;
        int Block_height = block_tex.getSize().y;
        block_spr.setOrigin(Block_width / 2, Block_height / 2);
    }

    void Create(class Point blocks[][width]) {

        float max = 1000000;
        if (FirstPress1) {
            sf::Vector2i vector(sf::Mouse::getPosition(window).y / 120, sf::Mouse::getPosition(window).x / 120); // переделал
            FocusOn = vector;
            if (blocks[FocusOn.x][FocusOn.y].passable) {
                blocks[FocusOn.x][FocusOn.y].passable = false;
                block_spr.setPosition(blocks[FocusOn.x][FocusOn.y].point_pos.x,
                                      blocks[FocusOn.x][FocusOn.y].point_pos.y);
            } else
                blocks[FocusOn.x][FocusOn.y].passable = true;
        }
        FirstPress1 = false;
    }

    void ShowBlocks(class Point blocks[][width]) {
        int i, j;
        for (i = 0; i < height; i++)
            for (j = 0; j < width; j++)
                if (blocks[i][j].passable == false) {
                    block_spr.setPosition(blocks[i][j].point_pos.x, blocks[i][j].point_pos.y);
                    window.draw(block_spr);
                }
    }
};


class Traveler : public Point {
public:

    sf::Vector2i FocusOn;
    sf::Texture travel_tex;
    sf::Sprite travel_spr;

    sf::Vector2i Start, Finish;

    Traveler() {
        travel_tex.loadFromFile(Images_Dir + "path.png");
        sf::Sprite sprite(travel_tex);
        travel_spr = sprite;
        int width = travel_tex.getSize().x;
        int height = travel_tex.getSize().y;
        travel_spr.setOrigin(width / 2, height / 2);
    }

    void create(class Point blocks[][width]) {
        int i, j;
        float min = 1000000;
        if (FirstPress2) {
            for (i = 0; i < height; i++)
                for (j = 0; j < width; j++)
                    blocks[i][j].partOfJorney = false;

            sf::Vector2i vector(sf::Mouse::getPosition(window).y / 120,
                                sf::Mouse::getPosition(window).x / 120);
            FocusOn = vector;

            if ((blocks[FocusOn.x][FocusOn.y].passable) && !StartSet) {
                travel_spr.setPosition(blocks[FocusOn.x][FocusOn.y].point_pos.x,
                                       blocks[FocusOn.x][FocusOn.y].point_pos.y);
                Start = FocusOn;
                StartSet = true;
                blocks[FocusOn.x][FocusOn.y].wave = 0;
            } else if (StartSet && (blocks[FocusOn.x][FocusOn.y].passable)) {
                StartSet = false;
                Finish = FocusOn;
            }

        }
        // printf("Start: %d %d\nFinish: %d %d\n", Start.x, Start.y, Finish.x, Finish.y);
        FirstPress2 = false;
    }

    void Wave(/*class*/ Point blocks[][width]) {//Зачем в таких местах писать class? Так делают только в структурах, когда не знают про typedef
        int OgrSv = 0;
        do {
            OgrSv++;
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if ((blocks[i][j].wave >= 0) && (blocks[i][j].passable)) {//Попроще
                        if ((blocks[i - 1][j].wave < 0) && blocks[i - 1][j].passable)
                            blocks[i - 1][j].wave = blocks[i][j].wave + 1;
                        if ((blocks[i][j - 1].wave < 0) && blocks[i][j - 1].passable)
                            blocks[i][j - 1].wave = blocks[i][j].wave + 1;
                        if ((blocks[i + 1][j].wave < 0) && blocks[i + 1][j].passable)
                            blocks[i + 1][j].wave = blocks[i][j].wave + 1;
                        if ((blocks[i][j + 1].wave < 0) && blocks[i][j + 1].passable)
                            blocks[i][j + 1].wave = blocks[i][j].wave + 1;
                    }
                }
            }
            if (OgrSv > height * width / 2) break;
        } while (blocks[Finish.x][Finish.y].wave == -1);
    }

    void GoBack(class Point blocks[][width]) {
        blocks[Finish.x][Finish.y].partOfJorney = true;
        int OgrSv = 0;
        do {
            OgrSv++;
            if (blocks[Finish.x][Finish.y - 1].wave - blocks[Finish.x][Finish.y].wave == -1) {
                Finish.y = Finish.y - 1;
                blocks[Finish.x][Finish.y].partOfJorney = true;
            } else if (blocks[Finish.x][Finish.y + 1].wave - blocks[Finish.x][Finish.y].wave == -1) {
                Finish.y = Finish.y + 1;
                blocks[Finish.x][Finish.y].partOfJorney = true;
            } else if (blocks[Finish.x - 1][Finish.y].wave - blocks[Finish.x][Finish.y].wave == -1) {
                Finish.x = Finish.x - 1;
                blocks[Finish.x][Finish.y].partOfJorney = true;
            } else if (blocks[Finish.x + 1][Finish.y].wave - blocks[Finish.x][Finish.y].wave == -1) {
                Finish.x = Finish.x + 1;
                blocks[Finish.x][Finish.y].partOfJorney = true;
            }
            if (OgrSv > height * width / 2) break;
        } while (Finish != Start);
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                blocks[i][j].wave = -1;
    }

    void ShowJorney(class Point blocks[][width]) {
        int i, j;
        for (i = 0; i < height; i++)
            for (j = 0; j < width; j++)
                if (blocks[i][j].partOfJorney) {
                    travel_spr.setPosition(blocks[i][j].point_pos.x, blocks[i][j].point_pos.y);
                    window.draw(travel_spr);
                }
        travel_spr.setPosition(blocks[Start.x][Start.y].point_pos.x, blocks[Start.x][Start.y].point_pos.y);
        window.draw(travel_spr);
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
    Point blocks[height][width];
    Block AlgoritmLi;

    std::string bg_path = Images_Dir + "bg.jpg";

    void run();

    Engine(List<Physical_Body> &objects) : objects(objects) {
        blocks[0][0].point_pos.x = 60;
        blocks[0][0].point_pos.y = 60;
        for (int i = 0, j = 0; i < height; i++) {
            if ((i != 0) || (j != 0)) {
                blocks[i][0].point_pos.y = blocks[i - 1][0].point_pos.y + 120;
                blocks[i][0].point_pos.x = blocks[i - 1][0].point_pos.x;
            }
            for (j = 1; j < width; j++) {
                if ((i != 0) || (j != 0)) {
                    blocks[i][j].point_pos.x = blocks[i][j - 1].point_pos.x + 120;
                    blocks[i][j].point_pos.y = blocks[i][j - 1].point_pos.y;
                }
            }
        }
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                if (((i < 1) || (i > 7)) || ((j < 1) || (j > 14)))
                    blocks[i][j].passable = false;

        background_image.loadFromFile(bg_path);
        Allot_t.loadFromFile(Images_Dir + "texture.png");

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
        window.setSize(sf::Vector2u(width * 120, height * 120));
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
            if (StartSet) {
                bob.create(blocks);
            } else {
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



