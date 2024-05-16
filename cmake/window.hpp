#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include "person.hpp"
#include "dop_za4et.hpp"

int TouchBorder(Person& obj) {
    double x = obj.X();
    double y = obj.Y();
    
    if (x + 15 > GetSystemMetrics(SM_CXSCREEN))
        return 4; // right
    else if (x - 15 < 0)
        return 3; // left
    else if (y + 25 > GetSystemMetrics(SM_CYSCREEN))
        return 2; //down
    else if (y - 25 < 0)
        return 1; //up
    else
        return 0;
}

class Game {
    sf::RenderWindow window;
    int scx = 1600;
    int scy = 900;
    Person person;
    double speed_creation = 5;
   
public:
    void Setup(){
        window.create(sf::VideoMode(scx, scy), "Incredible adventure of a student!");

        person.Setup(scx, scy);
    }

    bool TouchDop(Person& person, Dop& dop){
        double xp = person.X();
        double yp = person.Y();
        double xd = dop.X();
        double yd = dop.Y();

        if ((xp - 15 < xd - 10) && (xd - 10 < xp + 15) && (yp - 25 < yd - 10) && (yd - 10 < yp + 25))
            return true;
        else if ((xp - 15 < xd - 10) && (xd - 10 < xp + 15) && (yp - 25 < yd + 10) && (yd + 10 < yp + 25))
            return true;
        else if ((xp - 15 < xd + 10) && (xd + 10 < xp + 15) && (yp - 25 < yd + 10) && (yd + 10 < yp + 25))
            return true;
        else if ((xp - 15 < xd + 10) && (xd + 10 < xp + 15) && (yp - 25 < yd - 10) && (yd - 10 < yp + 25))
            return true;
        else
            return false;
    };

    void Life() {
        sf::Clock clock;
        float time = 0;
        float timer = 0;
        Dop dops[12];
        int dopcount = 0;

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            float dt = clock.getElapsedTime().asSeconds();
            clock.restart();
            time += dt;
            timer += dt;

            if (time > 3 && int(speed_creation*10) == int(timer*10) && dopcount < 12) {
                Dop tmp;
                tmp.Setup();
                dops[dopcount] = tmp;
                tmp.~Dop();
                dopcount++;
                timer = 0;
            }

            int touch = TouchBorder(person);
            if (!touch) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    person.Move(1, dt);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    person.Move(2, dt);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    person.Move(3, dt);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    person.Move(4, dt);
            }
            else if (touch == 1)
                person.Move(2, dt);
            else if (touch == 2)
                person.Move(1, dt);
            else if (touch == 3)
                person.Move(4, dt);
            else if (touch == 4)
                person.Move(3, dt);


            window.clear();
            for (int i = 0; i < dopcount; i++) {
                if (TouchDop(person, dops[i])) {
                    dops[i] = dops[dopcount-1];
                    dops[dopcount-1].~Dop();
                    dopcount--;
                    person.plusDop();
                }
                dops[i].Move(time);
                window.draw(dops[i].Get());
            }
            std::cout << person.DOPS() << std::endl;
            window.draw(person.Get());
            window.display();

            if (time > 20 && int(time) % 2 == 0) {
                person.SpeedChange(0.05);
                speed_creation -= 0.01;
            }
        }

    }
};