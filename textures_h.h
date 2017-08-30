//
// Created by fedya on 30.08.17.
//

#ifndef GAME_TEXTURES_H_H
#define GAME_TEXTURES_H_H

#include <SFML/Graphics/Texture.hpp>

using namespace std;
string Images_Dir("/Users/MyMac/CLionProjects/Images/");


class Controllable;

using namespace std;
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


class Textures : public Texture_Names {
public:
    enum types {
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
    ~Textures() override {};

    sf::Texture *Get_Texture(Controllable *obj);

    sf::Texture *Get_Texture(int type);
};

Textures textures;

#endif //GAME_TEXTURES_H_H
