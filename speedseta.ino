
#include "game.h"

void setup()
{
    tela.begin();
    setup_hardware();
    randomSeed(analogRead(5));
    menu();
    // setup_game_variaveis();
}
void loop()
{
    speed_seta();
}