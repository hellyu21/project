#include <SFML/Graphics.hpp>
#include "window.hpp"
#include <ctime>
#include <fstream>


int main()
{
    Game adventure;
    //adventure menu:(record*) start-->choose character,exit(esc/кнопка-выход)
    //подменю:choose character--нажимаю-запускает сетап и лайф

    Game();
   //adventure.Setup();

    //adventure.Life();

   // adventure.GameOver();

    adventure.run();

    return 0;
}