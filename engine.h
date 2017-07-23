//
// Created by fedya on 11.05.17.
//

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#endif

#include "Character.h"
#include <list.h>

class Engine{
public:
    void run();
    Engine(){};
    ~Engine(){};


    List <Character> * objects = NULL;
private:
    void logic();
};

void Engine::run(){
    for (auto elem = objects->first(); elem != objects->final(); elem++) {
        elem.dump();
        auto object = elem.data_;
        object->control();
        printFe("------------ % -----------\n\n", object->test());
    }
}



