#include <SFML/Graphics.hpp>
#include "window.hpp"
#include <ctime>


int main()
{
    srand(time(0));
    Game adventure;
    //adventure menu:(record*) start-->choose character,exit(esc/кнопка-выход)
    //подменю:choose character--нажимаю-запускает сетап и лайф


    adventure.Setup();

    adventure.Life();

   // adventure.GameOver();

    return 0;
}