//
// Created by fedya on 11.05.17.
//

#include <cstdlib>
#include <my_debug.h>
#include <ctime>

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#endif //GAME_CHARACTER_H



class Character{
protected:
    sf::Vector2f coord;
    sf::Vector2f v;
    sf::Vector2f a;
    int angle = 0;
    char * name = NULL;
    size_t health = 0;
    size_t stamina = 0;
    sf::Texture texture_;
    sf::Sprite sprite_;
public:
    Character(){}
    Character(char * name, char * img_path): name(name){
        texture_.loadFromFile(img_path);
        sf::Sprite sprite(texture_);
        sprite_ = sprite;
    }
    ~Character(){}
    void draw(sf::RenderWindow & window);
    virtual void move(){}
    void control();
    virtual void logic() = 0;
    void dump() const;
    bool operator == (const Character & right) const{
        return coord.x == right.coord.x && right.coord.y == coord.y && v.x == right.v.x && v.y == right.v.y && !strcmp(name, right.name);
    }
    bool operator != (const Character & right) const{
        return !(*this == right);
    }
};

void Character::dump() const{
    printFe("\nname %\nx %\ny %\nvx %\nvy %\nax %\nay %\n", name, coord.x, coord.y, v.x, v.y, a.x, a.y);
}

void Character::draw(sf::RenderWindow & window) {
    sprite_.setPosition(coord);
    window.draw(sprite_);
}

void Character::control() {

    float accel = 0.5;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        a.x = accel;
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            a.x = -accel;
        else {
            if (!IsEqual(v.x, 0, 0.9))
                a.x = -Sign(v.x);
            else a.x = 0;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        a.y = accel;
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            a.y = -accel;
        else {
            if (!IsEqual(v.y, 0, 0.9))
                a.y = -Sign(v.y);
            else a.y = 0;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        angle++;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        angle--;



    sprite_.setRotation(angle);
}

class Super_Hero : public Character{
public:

    Super_Hero() : Character(){}
    Super_Hero(char * name, char * img_path) : Character (name, img_path){}
    void logic(){};
    void move(){
        coord.x += v.x * 0.01;
        coord.y += v.y * 0.01;
        v.x += a.x;
        v.y += a.y;

        if (IsEqual(v.x, 0, 0.1))
            v.x = 0;
        if (IsEqual(v.y, 0, 0.1))
            v.y = 0;
    }
};

