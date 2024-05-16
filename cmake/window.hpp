#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include "person.hpp"
#include "dop_za4et.hpp"
using namespace sf;

int TouchBorder(Person& obj) {
    double x = obj.X();
    double y = obj.Y();
    
    if (x + 15 > 1600)
        return 4; // right
    else if (x - 15 < 0)
        return 3; // left
    else if (y + 25 > 900)
        return 2; //down
    else if (y - 25 < 0)
        return 1; //up
    else
        return 0;
}

class Game {
    RenderWindow window;
    int scx = 1600;
    int scy = 900;
    Person person;
    double speed_creation = 5;
   
public:
    void Menu(){
        //перекинуть создание окна из сетап
    }

    void MiniMenu() {

    }
    void Setup(){
        window.create(VideoMode(scx, scy), "Incredible adventure of a student!");

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

    bool TouchZat(Person& person, Zat& zach) {
        double xp = person.X();
        double yp = person.Y();
        double xz = zach.X();
        double yz = zach.Y();
        int type = zach.TYPE();

        if (type == 1 && (xp - 15 < xz) && (xz < xp + 15) && (yp - 25 < yz+20) && (yz + 20 < yp + 25))
            return true;
        else if (type == 2 && (xp - 15 < xz) && (xz < xp + 15) && (yp - 25 < yz - 20) && (yz - 20 < yp + 25))
            return true;
        else if (type == 3 && (xp - 15 < xz + 20) && (xz + 20 < xp + 15) && (yp - 25 < yz) && (yz < yp + 25))
            return true;
        else if (type == 4 && (xp - 15 < xz - 20) && (xz - 20 < xp + 15) && (yp - 25 < yz) && (yz < yp + 25))
            return true;
        else
            return false;
    };

    void Life() {
        Clock clock;
        float time = 0;
        float doptimer = 0;
        float zachtimer = 0;
        float persontimer = 0;
        Dop dops[12];
        Zat zacheti[12];
        int dopcount = 0;
        int zachcount = 0;
        bool gameover = 0;

        while (window.isOpen() && !gameover)
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            float dt = clock.getElapsedTime().asSeconds();
            clock.restart();
            time += dt;
            doptimer += dt;
            persontimer += dt;
            zachtimer += dt;

            //возможный звук
            if (time > 3 && doptimer > speed_creation && dopcount < 12) {
                Dop tmp;
                tmp.Setup();
                dops[dopcount] = tmp;
                tmp.~Dop();
                dopcount++;
                doptimer = 0;
            }

            if (time > 3 && zachtimer > speed_creation && zachcount < 12) {
                Zat tmp;
                tmp.Setup();
                zacheti[zachcount] = tmp;
                tmp.~Zat();
                zachcount++;
                zachtimer = 0;
            }

            int touch = TouchBorder(person);
            if (!touch) {
                if (Keyboard::isKeyPressed(Keyboard::W))
                    person.Move(1, dt);
                if (Keyboard::isKeyPressed(Keyboard::S))
                    person.Move(2, dt);
                if (Keyboard::isKeyPressed(Keyboard::A))
                    person.Move(3, dt);
                if (Keyboard::isKeyPressed(Keyboard::D))
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
            for (int i = 0; i < zachcount; i++) {
                int typezat = zacheti[i].TYPE();
                if ((typezat == 1 && zacheti[i].Y() - 20 > 900) || (typezat == 2 && zacheti[i].Y() + 20 < 0) || (typezat ==3 && zacheti[i].X() - 20 > 1600) || (typezat == 4 && zacheti[i].X() + 20 < 0)) {
                    zacheti[i] = zacheti[zachcount - 1];
                    typezat = zacheti[zachcount - 1].TYPE();
                    zacheti[zachcount - 1].~Zat();
                    zachcount--;
                }
                if (TouchZat(person, zacheti[i])) {
                    zacheti[i] = zacheti[zachcount - 1];
                    typezat = zacheti[zachcount - 1].TYPE();
                    zacheti[zachcount - 1].~Zat();
                    zachcount--;
                    person.Minusheart();
                    if (person.Hearts() == 0) {
                        window.clear();
                        gameover = 1;
                    }
                }
                zacheti[i].Move(typezat, dt);
                window.draw(zacheti[i].Get());
            }

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
            window.draw(person.Get());
            window.display();

            if (time >10 && persontimer > 2) {
                person.SpeedChange(10);
                speed_creation -= 0.05;
                persontimer = 0;
            }
        }

    }

    void GameOver(){
        while (window.isOpen()) {
            window.draw(person.Get());
        }
    }
};