//
// Created by fedya on 09.08.17.
//
#ifndef GAME_TEXTURES_H
#define GAME_TEXTURES_H

#include <SFML/Graphics.hpp>
using namespace std;

string Images_Dir("/Users/MyMac/CLionProjects/Images/");



class Texture_Names{
public:
    Texture_Names(){};
    virtual ~Texture_Names(){};
protected:
#define tex(name, what)\
    string name##_path = #name;

#include "textures_and_paths.h"
#undef tex
};

class Textures : public Texture_Names{
public:
    enum types{
#define tex(name, num) type_##name,
#include "textures_passable.txt"
        type_passable,
#include "textures_impassable.txt"
        type_impassable,
#include "textures_other.txt"
#undef tex
        type_empty
    };

#define tex(name, what) sf::Texture name##_texture;

#include "textures_and_paths.h"
#undef tex

    Textures(){
#define tex(name, what) name##_path += '.';\
        name##_path += #what;\
        name##_texture.loadFromFile(Images_Dir + name##_path);\

#include "textures_and_paths.h"
#undef tex
    };
    ~Textures() = default;


    sf::Texture * Get_Texture(int type){
        switch (type){
#define tex(name, what) case type_##name : {return & name##_texture;}

#include "textures_and_paths.h"
#undef tex
            default:{
                return NULL;
            };
        }
    }
};

Textures textures;

#endif //GAME_TEXTURES_H
