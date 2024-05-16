#include <SFML/Graphics.hpp>
#include "window.hpp"
#include <ctime>


int main()
{
    srand(time(0));
    Game adventure;
    adventure.Setup();

    adventure.Life();

    return 0;
}