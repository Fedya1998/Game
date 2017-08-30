//
// Created by fedya on 24.07.17.
//

#include <list.h>
#include "Controllable.h"

#ifndef GAME_BODY_FUNCTIONS_H
#define GAME_BODY_FUNCTIONS_H



void Controllable::draw() {
    sprite_.setPosition(coord);
    window.draw(sprite_);
}

float Controllable::distance(Controllable &Body) {
    return sqrt(pow(coord.x - Body.coord.x, 2) + pow(coord.y - Body.coord.y, 2));
}

bool Controllable::intersection(Controllable &Body) {
    return 2 * fabsf(coord.x - Body.coord.x) < width + Body.width &
           2 * fabsf(coord.y - Body.coord.y) < height + Body.height;
}

void Controllable::dump() const {
    printFe("name %\nx %\ny %\n", name, coord.x, coord.y);
}

void Controllable::live() {
    if (health <= 0)
        die();
}

void Controllable::die() {
    delete list_elem;
}



void Movable::move() {

    sf::Vector2f coord_old(coord);
    coord.x += v.x * 0.01;
    coord.y += v.y * 0.01;
    bool collision = false;
    auto objects = *(list_elem->header_);

    for (auto elem = objects.first(); elem != objects.final(); elem++){
        auto object = elem.data_;
        if (intersection(* object)){
            if (collision | object == this)
                continue;
            printf("Pizdec intersection sooqa with\n");
            object->dump();
            coord = coord_old;
            collide(* object);
            collision = true;
        }

    }


    if (sqrtf(powf(v.x + a.x, 2) + powf(v.y + a.y, 2)) < v_max) {
        v.x += a.x;
        v.y += a.y;
    }

    if (IsEqual(v.x, 0, 1))
        v.x = 0;
    if (IsEqual(v.y, 0, 1))
        v.y = 0;
}

void Movable::collide(Controllable &Body) {
    const float alpha = 0.5;//This part of energy goes to deformation and other shit
    v *= sqrtf(1 - alpha);//We've met a wall
}

void Movable::collide(Movable &Body) {
    const float alpha = 0.5;//This part of energy goes to deformation and other shit
    sf::Vector2f v_old = v;
    const float gamma = mass / Body.mass;
    v = (gamma * v_old + Body.v) * (1 / 2 / (gamma + 1)) * (1 - sqrtf((1 - alpha * (gamma + 1)) * gamma));
    Body.v = gamma * v_old + Body.v - gamma * v;
}

void Character::dump() const{
    printFe("\nname %\nx %\ny %\nvx %\nvy %\nax %\nay %\n", name, coord.x, coord.y, v.x, v.y, a.x, a.y);
    printFe("health %\nstamina %\n", health, stamina);
}

void Character::draw(){
    Controllable::draw();

}

void Character::control() {//Sets destination vector

}

void Character::suffer(size_t damage) {
    health -= damage;
}

void Super_Hero::control() {

    const float accel = 1.5;
    const float accel_friction = 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        a.x = accel - accel_friction * Sign(v.x);
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            a.x = -accel - accel_friction * Sign(v.x);
        else {
            if (!IsEqual(v.x, 0, 0.9))
                a.x = -accel_friction * Sign(v.x);
            else a.x = 0;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        a.y = accel - accel_friction * Sign(v.y);
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            a.y = -accel - accel_friction * Sign(v.y);
        else {
            if (!IsEqual(v.y, 0, 0.9))
                a.y = -accel_friction * Sign(v.y);
            else a.y = 0;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        angle += 0.4;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        angle -= 0.4;


    sprite_.setRotation(angle);
}


void Enemy::attack(Character &Char) {
    Char.suffer(base_damage);
}

void Enemy::logic() {
    /*Super_Hero &Hero = (Super_Hero &) *objects[0].data_;
    if (distance(Hero) < distance_to_see)
        follow(Hero);
    if (distance(Hero) < distance_to_attack) {
        //printFe("Ready to attack\n");
        attack(Hero);
    }*/
}

void Enemy::follow(Character &Char) {

}



#endif //GAME_BODY_FUNCTIONS_H