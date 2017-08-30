//
// Created by fedya on 30.08.17.
//

#ifndef GAME_LEE_H
#define GAME_LEE_H

#endif //GAME_LEE_H

enum Lee{
    LEE_EMPTY
};

#include "Block.h"



int Spread_path(sf::Vector2i start, sf::Vector2i dest, Block blocks[width][height]) ;

List<sf::Vector2i> * Find_Path(sf::Vector2i start, sf::Vector2i dest, Block blocks[width][height]) ;

sf::Vector2i deltas[4] = {(1, 0), (0, 1), (-1, 0), (0, -1)};

List<sf::Vector2i> * Lee(sf::Vector2i start, sf::Vector2i dest, Block blocks [width][height]){
    int length = Spread_path(start, dest, blocks);
    if (length == LEE_EMPTY)
        return NULL;
    return Find_Path(start, dest, blocks);

}

int Spread_path(sf::Vector2i start, sf::Vector2i dest, Block blocks[width][height]) {
    int length = 0;
    bool stop = true;
    
    do {
        stop = true;
        length++;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (blocks[i][j].path == length) {
                    for (int k = 0; k < 4; k++){
                        if (blocks[i + deltas[k].x][j + deltas[k].y].path == LEE_EMPTY &
                                blocks[i + deltas[k].x][j + deltas[k].y].surface < Textures::type_passable &
                                blocks[i + deltas[k].x][j + deltas[k].y].afloat->type != Textures::type_building){
                            blocks[i + deltas[k].x][j + deltas[k].y].path = length;
                            stop = false;
                        }
                    }
                }
            }
        }
    } while (!stop & blocks[Finish.x][Finish.y].path == LEE_EMPTY);
    if (blocks[Finish.x][Finish.y].path == LEE_EMPTY)
        return LEE_EMPTY;
    return length;
}

List<sf::Vector2i> * Find_Path(sf::Vector2i start, sf::Vector2i dest, Block blocks[width][height]) {
    List<sf::Vector2i> * journey_list = new List<sf::Vector2i>;
    int length = blocks[dest.x][dest.y].path;
    journey_list->append(new sf::Vector2i(dest));
    List_Elem<sf::Vector2i> * elem = journey_list->first_;
    while (length > 0)
    {

        length--;
        sf::Vector2i now = dest;
        for (int k = 0; k < 4; k++) {
            now += deltas[k];
            if (now.x >=0 && now.y >=0 && now.x < width && now.y < height && blocks[now.x][now.y].path == length) {
                dest = now;
                break;
            }
        }
        elem = elem->add_before(new sf::Vector2i(now));
    }

    return journey_list;
}
