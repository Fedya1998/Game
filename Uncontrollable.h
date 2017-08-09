//
// Created by fedya on 09.08.17.
//



#ifndef GAME_UNCONTROLLABLE_H
#define GAME_UNCONTROLLABLE_H

#endif //GAME_UNCONTROLLABLE_H

Textures textures;
class Uncontrollable{
protected:
    sf::Vector2f coord;
    size_t width = 0;
    size_t height = 0;

    sf::Sprite sprite_;
public:
    int type = Textures::type_empty;
    Uncontrollable(int type) : type(type) {
        sf::Texture * texture = textures.Get_Texture(this);
        sf::Sprite sprite(*texture);
        sprite_ = sprite;
        width = texture->getSize().x;
        height = texture->getSize().y;
        sprite_.setOrigin(width / 2, height / 2);
    }

    virtual ~Uncontrollable() {}

    virtual void draw(){}
    virtual void dump() const{}

    bool operator ==(const Uncontrollable &right){
        return coord.x == right.coord.x && right.coord.y == coord.y;
    }

    bool operator !=(const Uncontrollable &right) {
        return !(*this==right);
    }

};

#include "textures.h"