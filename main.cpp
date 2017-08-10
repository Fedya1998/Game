#define DEBUG

#include <printFe.h>
#include <super_table.h>
#include <my_functions.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>


#include "engine.h"

//using namespace std;



int main() {

    List <Controllable> super_list;
    /*
    char img_path[100] = "/home/fedya/Изображения/Game images/deer.png";
    char * name1 = (char *) calloc(sizeof(char), strlen("Kirill") + 1);
    strcpy(name1, "Kirill");
    super_list.append(new Super_Hero(name1, img_path));

    char img_path2[100] = "/home/fedya/Изображения/Game images/zombie.png";
    char * name2 = (char *) calloc(sizeof(char), strlen("Zombie") + 1);
    strcpy(name2, "Zombie");
    super_list.append(new Enemy(name2, img_path2));
     */

    Engine engine = Engine();

    engine.run();

    return 0;
}