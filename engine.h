//
// Created by fedya on 11.05.17.
//

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#endif

sf::RenderWindow window(sf::VideoMode(1920, 1080), "A Swagabitch game");

#include <list.h>
#include "Controllable.h"
#include <math.h>


sf::Vector2i Start;
sf::Vector2i Now;
sf::Vector2i Finish;
const sf::Vector2u size = window.getSize();
const sf::Vector2i block_size(120, 120);
const int width = 16, height = 9;



#include "Lee.h"


template<typename T>
double Distance(sf::Vector2<T> a, sf::Vector2<T> b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}


/*
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

    void create(Point blocks[][width]) {
        if (FirstPress2) {
            for (int i = 0, j = 0; i < height; i++)
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

    void Wave(Point blocks[][width]) {//Зачем в таких местах писать class? Так делают только в структурах, когда не знают про typedef
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

    void GoBack(Point blocks[][width]) {
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

    void ShowJorney(Point blocks[][width]) {
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

*/
class Mysh {
    bool FirstPress;

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
    Block blocks[width][height];
    sf::Texture Allot_t;

    std::string bg_path = Images_Dir + "bg.png";

    virtual void run();

    Engine() {
        objects = new List<Controllable>;


        blocks[0][0].point_pos.x = block_size.x / 2;
        blocks[0][0].point_pos.y = block_size.y / 2;
        for (int i = 0, j = 0; i < height; i++) {
            if ((i != 0) || (j != 0)) {
                blocks[i][0].point_pos.y = blocks[i - 1][0].point_pos.y + block_size.y;
                blocks[i][0].point_pos.x = blocks[i - 1][0].point_pos.x;
            }
            for (j = 1; j < width; j++) {
                if ((i != 0) || (j != 0)) {
                    blocks[i][j].point_pos.x = blocks[i][j - 1].point_pos.x + block_size.x;
                    blocks[i][j].point_pos.y = blocks[i][j - 1].point_pos.y;
                }
            }
        }

        background_image.loadFromFile(bg_path);
        Allot_t.loadFromFile(Images_Dir + "texture.png");

    };

    void Load_Map(const char * map_name);

    ~Engine() {
        delete objects;
    };

    List<Controllable> *objects = NULL;

private:
    //void logic();

    void clear_blocks();
};


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


