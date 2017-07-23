#define DEBUG

#include <printFe.h>
#include <super_table.h>
#include <my_functions.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>


#include "engine.h"


using namespace std;

int main() {
    List <Character> super_list;
    super_list.append(new Super_Hero());
    super_list.append(new Super_Hero());
    char * name1 = (char *) calloc(sizeof(char), strlen("Kek") + 1);
    char * name2 = (char *) calloc(sizeof(char), strlen("Kek2") + 1);
    strcpy(name1, "Kek");
    strcpy(name2, "Kek2");
    super_list[0].data_->name = name1;
    super_list[1].data_->name = name2;
    Engine engine = Engine();
    engine.objects = &super_list;
    engine.run();
    free(name1);
    free(name2);
    return 0;
}