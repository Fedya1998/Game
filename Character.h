//
// Created by fedya on 11.05.17.
//

#include <cstdlib>
#include <my_debug.h>

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#endif //GAME_CHARACTER_H


class Character{

public:
    //protected:
    int x = 0;
    int y = 0;
    int vx = 0;
    int vy = 0;
    char * name = NULL;
    size_t health = 0;
    size_t stamina = 0;
public:
    Character(){}
    ~Character(){}
    void draw();
    void move();
    void logic();
    void control(){
        Gde;
    }
    void dump() const;
    virtual int test() = 0;
    bool operator == (const Character & right) const{
        return x == right.x && right.y == y && vx == right.vx && vy == right.vy && !strcmp(name, right.name);
    }
    bool operator != (const Character & right) const{
        return !(*this == right);
    }
};

void Character::dump() const{
    printFe("\nx %\ny %\nvx %\nvy %\nname %\n", x, y, vx, vy, name);
}

class Super_Hero : public Character{
public:
    Super_Hero() : Character(){}
    int test(){
        return 1;
    }
};



