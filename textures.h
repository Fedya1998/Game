//
// Created by fedya on 09.08.17.
//
#ifndef GAME_TEXTURES_H
#define GAME_TEXTURES_H

#include <SFML/Graphics.hpp>

using namespace std;



#include "textures_h.h"



sf::Texture * Textures::Get_Texture(Controllable * obj) {
    Get_Texture(obj->type);
}


sf::Texture * Textures::Get_Texture(int type){
    switch (type){
#define tex(name, what) case type_##name : {return & name##_texture;}

#include "textures_and_paths.h"
#undef tex
        default:{
            return NULL;
        };
    }
}




#endif //GAME_TEXTURES_H
