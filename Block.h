//
// Created by fedya on 30.08.17.
//

#ifndef GAME_BLOCK_H
#define GAME_BLOCK_H



class Block {
public:
    sf::Vector2i point_pos;

    int path = LEE_EMPTY;

    int surface = Textures::type_empty;
    Controllable * afloat = NULL;


    Block() {}
    ~Block(){}
};

#endif //GAME_BLOCK_H

