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

Textures textures;
const int INF_MASS = -1;

class Controllable{
protected:
    sf::Vector2f coord;
    size_t width = 0;
    size_t height = 0;
    size_t health = 0;

    sf::Sprite sprite_;

    char *name = NULL;
    float mass = INF_MASS;

    List_Elem<Controllable> * list_elem = NULL;
public:
    int type = Textures::type_empty;


    Controllable(char *name, int type) : name(name), type(type) {
        sf::Texture *texture = textures.Get_Texture(this);
        sf::Sprite sprite(*texture);
        sprite_ = sprite;
        width = texture->getSize().x;
        height = texture->getSize().y;
        sprite_.setOrigin(width / 2, height / 2);
    }
    virtual ~Controllable() {
        free(name);
    }

    virtual void draw();
    bool intersection(Controllable &Body);
    float distance(Controllable &Body);
    virtual void dump() const;

    void live();
    void die();

    bool operator ==(const Controllable &right){
        return coord.x == right.coord.x && right.coord.y == coord.y && !strcmp(name, right.name);
    }

    bool operator !=(const Controllable &right) {
        return !(*this==right);
    }

};

class Movable : public Controllable {
protected:
    sf::Vector2f v;
    sf::Vector2f a;
    size_t v_max = 0;
public:
    Movable(char *name, int type) : Controllable (name, type) {}
    void move(List<Controllable> &objects);
    void collide(Controllable &Body);
    void collide(Movable &movable);
};

class Character : public Movable {
protected:
    enum types{

    };
    float angle = 0;
    size_t stamina = 0;
    size_t base_damage = 0;
    size_t cooldown = 0;
public:
    bool selected = false;


public:
    Character(char *name, int type) : Movable (name, type) {}

    void suffer(size_t damage);

    void draw() override;

    virtual void control() = 0;

    virtual void logic(List<Controllable> &objects) = 0;



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
    Super_Hero(char *name, int type) : Character(name, type){
        health = 100;
        stamina = 100;
        v_max = 100;
        cooldown = 50;
        mass = 100;
    }

    ~Super_Hero() {}

    void control() override;

    void logic(List<Controllable> &objects) override{

    }
};

class Enemy : public Character {
public:
    //Enemy() : Character(){}
    Enemy(char *name, int type) : Character(name, type) {
        health = 100;
        stamina = 100;
        coord.x = 1000;
        coord.y = 500;
        base_damage = 10;
        cooldown = 50;
        mass = 200;
    }
    void control() override{}

protected:
    int distance_to_attack = 50;
    int distance_to_see = 300;


    void attack(Character &Char);

    void follow(Character &Char);

    void logic(List<Controllable> &objects) override;
};
