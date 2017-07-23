#define NDEBUG

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

    List <Character> super_list;
    char img_path[100] = "/home/fedya/Изображения/Game images/Kirill.jpg";
    char * name1 = (char *) calloc(sizeof(char), strlen("Kirill") + 1);
    strcpy(name1, "Kirill");
    super_list.append(new Super_Hero(name1, img_path));

    Engine engine = Engine();
    engine.objects = &super_list;

    engine.run();
    free(name1);

    return 0;
}