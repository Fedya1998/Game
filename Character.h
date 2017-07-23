//
// Created by fedya on 11.05.17.
//

#include <cstdlib>
#include <my_debug.h>

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#endif //GAME_CHARACTER_H



class Character{
protected:
    sf::Vector2i coord;
    sf::Vector2i v;
    sf::Vector2i a;
    int angle = 0;
    char * name = NULL;
    size_t health = 0;
    size_t stamina = 0;
    sf::Sprite sprite_;
public:
    Character(){}
    Character(char * name, sf::Texture texture): name(name), sprite_(texture){}
    ~Character(){}
    void draw(sf::RenderWindow window);
    void move();
    void control();
    virtual void logic() = 0;
    void dump() const;
    /*bool operator == (const Character & right) const{
        return x == right.x && right.y == y && vx == right.vx && vy == right.vy && !strcmp(name, right.name);
    }
    bool operator != (const Character & right) const{
        return !(*this == right);
    }
     */
};

void Character::dump() const{
    printFe("\nx %\ny %\nvx %\nvy %\nname %\n", coord.x, coord.y, v.x, v.y, name);
}

void Character::draw(sf::RenderWindow window) {
    window.draw(sprite_);
}

void Character::control() {
#define my_key(key, what, number) \
    if (sf::Keyboard::isKeyPressed(key)) what = number;\
    else what = 0;
#include "not_to_copypaste.h"
#undef my_key

    sprite_.setRotation(angle);
}

class Super_Hero : public Character{
public:
    Super_Hero() : Character(){}
    Super_Hero(char * name, sf::Texture texture) : Character (name, texture){}
    void logic(){};
};

