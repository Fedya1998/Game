//
// Created by fedya on 11.05.17.
//

#include <cstdlib>
#include <my_debug.h>
#include <ctime>
#include <cmath>
#include <list_h.h>
#include <SFML/Graphics.hpp>

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#endif //GAME_CHARACTER_H

const int INF_MASS = -1;

class Physical_Body {
protected:
    sf::Vector2f coord;
    size_t width = 0;
    size_t height = 0;
    char *name = NULL;
    sf::Texture texture_;
    sf::Sprite sprite_;
    int mass = INF_MASS;
public:
    Physical_Body(char *name, char *img_path) : name(name) {
        texture_.loadFromFile(img_path);
        sf::Sprite sprite(texture_);
        sprite_ = sprite;
        width = texture_.getSize().x;
        height = texture_.getSize().y;
        sprite_.setOrigin(width / 2, height / 2);
    }
    virtual ~Physical_Body() {
        free(name);
    }
    virtual void draw();
    bool intersection(Physical_Body &Body);
    float distance(Physical_Body &Body);
    virtual void dump() const;

    bool operator ==(const Physical_Body &right){
        return coord.x == right.coord.x && right.coord.y == coord.y && !strcmp(name, right.name);
    }

    bool operator !=(const Physical_Body &right) {
        return !(*this==right);
    }

};

class Movable : public Physical_Body {
protected:
    sf::Vector2f v;
    sf::Vector2f a;
    size_t v_max = 0;
public:
    Movable(char *name, char *img_path) : Physical_Body (name, img_path) {}
    void move(List<Movable> &objects);
    void collide(Physical_Body &Body);
};

class Character : public Movable {
protected:
    float angle = 0;
    size_t health = 0;
    size_t stamina = 0;
    size_t base_damage = 0;
    size_t cooldown = 0;
public:
    Character(char *name, char *img_path) : Movable (name, img_path) {}



    void suffer(size_t damage);

    void draw() override;

    virtual void control() = 0;

    virtual void logic(List<Physical_Body> &objects) = 0;

    void live(List_Elem<Physical_Body> * elem);

    virtual void die(List_Elem<Physical_Body> *elem) = 0;

    void dump() const override;

    bool operator==(const Character &right) const {
        return coord.x == right.coord.x && right.coord.y == coord.y && v.x == right.v.x && v.y == right.v.y &&
               !strcmp(name, right.name);
    }

    bool operator!=(const Character &right) const {
        return !(*this == right);
    }
};

class Super_Hero : public Character {
public:
    Super_Hero(char *name, char *img_path) : Character(name, img_path) {
        health = 100;
        stamina = 100;
        v_max = 100;
        cooldown = 50;
    }

    //~Super_Hero() {}

    void control() override;

    void logic(List<Physical_Body> &objects) override{

    }

    void die(List_Elem<Physical_Body> *elem) override;
};

class Enemy : public Character {
public:
    //Enemy() : Character(){}
    Enemy(char *name, char *img_path) : Character(name, img_path) {
        health = 100;
        stamina = 100;
        coord.x = 1000;
        coord.y = 500;
        base_damage = 10;
        cooldown = 50;
    }
    void control() override{}

protected:
    int distance_to_attack = 50;
    int distance_to_see = 300;


    void attack(Character &Char);

    void follow(Character &Char);

    void logic(List<Physical_Body> &objects) override;

    void die(List_Elem<Physical_Body> *elem) override;
};
