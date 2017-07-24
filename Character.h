//
// Created by fedya on 11.05.17.
//

#include <cstdlib>
#include <my_debug.h>
#include <ctime>
#include <cmath>
#include <list_h.h>

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#endif //GAME_CHARACTER_H


class Character {
protected:
    sf::Vector2f coord;
    sf::Vector2f v;
    sf::Vector2f a;
    float angle = 0;
    char *name = NULL;
    size_t health = 0;
    size_t stamina = 0;
    size_t base_damage = 0;
    sf::Texture texture_;
    sf::Sprite sprite_;
public:
    Character() {}

    Character(char *name, char *img_path) : name(name) {
        texture_.loadFromFile(img_path);
        sf::Sprite sprite(texture_);
        sprite_ = sprite;
    }

    ~Character() {
        free(name);
    }

    float distance(Character &Char);

    void suffer(size_t damage);

    void draw();

    void move();

    virtual void control() = 0;

    virtual void logic(List<Character> &objects) = 0;

    void live(List_Elem<Character> * elem);

    virtual void die(List_Elem<Character> *elem) = 0;

    void dump() const;

    bool operator==(const Character &right) const {
        return coord.x == right.coord.x && right.coord.y == coord.y && v.x == right.v.x && v.y == right.v.y &&
               !strcmp(name, right.name);
    }

    bool operator!=(const Character &right) const {
        return !(*this == right);
    }
};

void Character::dump() const {
    printFe("\nname %\nx %\ny %\nvx %\nvy %\nax %\nay %\n", name, coord.x, coord.y, v.x, v.y, a.x, a.y);
    printFe("health %\nstamina %\n", health, stamina);
}

void Character::draw() {
    sprite_.setPosition(coord);
    window.draw(sprite_);
}

void Character::move() {
    coord.x += v.x * 0.01;
    coord.y += v.y * 0.01;
    v.x += a.x;
    v.y += a.y;

    if (IsEqual(v.x, 0, 0.1))
        v.x = 0;
    if (IsEqual(v.y, 0, 0.1))
        v.y = 0;
}


float Character::distance(Character &Char) {
    return (float) sqrt(pow(coord.x - Char.coord.x, 2) + pow(coord.y - Char.coord.y, 2));
}

void Character::live(List_Elem<Character> * elem) {
    if (health <= 0)
        die(elem);
}

void Character::suffer(size_t damage) {
    health -= damage;
}




class Super_Hero : public Character {
public:

    Super_Hero() : Character() {
        health = 100;
        stamina = 100;
    }

    Super_Hero(char *name, char *img_path) : Character(name, img_path) {
        health = 100;
        stamina = 100;
    }

    //~Super_Hero() {}

    void control();

    void logic(List<Character> &objects) {}

    void die(List_Elem<Character> *elem);
};

void Super_Hero::die(List_Elem<Character> *elem) {
    Show_Kirill();
    getchar();
}

void Super_Hero::control() {

    const float accel = 0.5;

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
        angle += 0.4;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        angle -= 0.4;


    sprite_.setRotation(angle);
}



class Enemy : public Character {
public:
    //Enemy() : Character(){}
    Enemy(char *name, char *img_path) : Character(name, img_path) {
        health = 100;
        stamina = 100;
        coord.x = 1000;
        coord.y = 500;
        base_damage = 10;
    }
    void control(){}

protected:
    int distance_to_attack = 50;
    int distance_to_see = 300;


    void attack(Character &Char);

    void follow(Character &Char);

    void logic(List<Character> &objects);

    void die(List_Elem<Character> *elem);
};

void Enemy::attack(Character &Char) {
    Char.suffer(base_damage);
}

void Enemy::logic(List<Character> &objects) {
    Super_Hero &Hero =  (Super_Hero &) *objects[0].data_;
    if (distance(Hero) < distance_to_see)
        follow(Hero);
    if (distance(Hero) < distance_to_attack) {
        //printFe("Ready to attack\n");
        attack(Hero);
    }
}

void Enemy::die(List_Elem<Character> *elem) {
    delete (List_Elem<Enemy> *) elem;
}

void Enemy::follow(Character &Char) {

}


