//
// Created by fedya on 30.08.17.
//

#ifndef GAME_ENGINE_H_H
#define GAME_ENGINE_H_H


class Mysh {
private:
    bool FirstPress;

public:
    void Allot(sf::Sprite Allot_s) {
        if (FirstPress) {
            Start = sf::Mouse::getPosition(window);
            FirstPress = false;
        }
        Now = sf::Mouse::getPosition(window);
        if (Now.x > Start.x) {
            if (Now.y > Start.y) {
                Allot_s.setPosition(Start.x, Start.y);
                Allot_s.setTextureRect(sf::IntRect(0, 0, Now.x - Start.x, Now.y - Start.y));
            } else {
                Allot_s.setPosition(Start.x, Now.y);
                Allot_s.setTextureRect(sf::IntRect(0, 0, Now.x - Start.x, Start.y - Now.y));
            }
        } else {
            if (Now.y > Start.y) {
                Allot_s.setPosition(Now.x, Start.y);
                Allot_s.setTextureRect(sf::IntRect(0, 0, Start.x - Now.x, Now.y - Start.y));
            } else {
                Allot_s.setPosition(Now.x, Now.y);
                Allot_s.setTextureRect(sf::IntRect(0, 0, Start.x - Now.x, Start.y - Now.y));
            }
        }
        window.draw(Allot_s);
    }
};


class Engine : public Mysh {
public:
    sf::Texture background_image;
    Block blocks[width][height];
    sf::Texture Allot_t;

    std::string bg_path = Images_Dir + "bg.png";

    virtual void run();

    Engine() {
        objects = new List<Controllable>;


        blocks[0][0].point_pos.x = block_size.x / 2;
        blocks[0][0].point_pos.y = block_size.y / 2;
        for (int i = 0, j = 0; i < height; i++) {
            if ((i != 0) || (j != 0)) {
                blocks[i][0].point_pos.y = blocks[i - 1][0].point_pos.y + block_size.y;
                blocks[i][0].point_pos.x = blocks[i - 1][0].point_pos.x;
            }
            for (j = 1; j < width; j++) {
                if ((i != 0) || (j != 0)) {
                    blocks[i][j].point_pos.x = blocks[i][j - 1].point_pos.x + block_size.x;
                    blocks[i][j].point_pos.y = blocks[i][j - 1].point_pos.y;
                }
            }
        }

        background_image.loadFromFile(bg_path);
        Allot_t.loadFromFile(Images_Dir + "texture.png");

    };

    void Load_Map(const char * map_name);

    ~Engine() {
        delete objects;
    };

    List<Controllable> *objects = NULL;

    void clear_blocks();
};

#endif //GAME_ENGINE_H_H



