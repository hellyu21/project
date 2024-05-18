#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include "person.hpp"
#include "dop_za4et.hpp"
using namespace sf;
using namespace std;


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
private:
    RenderWindow window;
    Person person;
    int scx = 1600;
    int scy = 900;
    int speed_creation = 5;
    int speed_zach = 140;
    enum  State { menu, choosecharacter, InGame, gameover1, gameover2 };//разные состояния игры
    State state;
    
   
public:
   
    Game() { 
        srand(time(0));
        window.create(VideoMode(scx, scy), "Incredible adventure of a student!");
        state = menu;
    }

    void run() {
        while (window.isOpen()) {
            processEvents();
            update();
        }
    }
    void processEvents() {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
    }
    
    void update() {//смена режима без закрытие окна
        switch (state) {
        case menu:
            Menu();
            break;
        case choosecharacter:
            ChooseCharacter();
            //проработать,чтобы выбор происходил и соотв.спрайты персонажу присваивались
            break;
        case InGame:
            game();//фон
            Setup();//персонаж
            Life();//игра
            state = gameover1;
            break;
        case gameover1:
            GameOver();//рестарт/выход
            break;
        case gameover2:
            window.close();
            break;
        }
    }

    void Menu() {
        //фон
        Texture backgroundMenuTexture;
        backgroundMenuTexture.loadFromFile("sprites\\backMenu.png");
        Sprite background(backgroundMenuTexture);
        background.setScale(0.75f, 0.75f);
        window.draw(background);

        //кнопка старт (спрайт временный)
        Texture startTexture;
        startTexture.loadFromFile("sprites\\start.png");
        Sprite startButton(startTexture);
        startButton.setPosition(100, 200);
        window.draw(startButton);

        //кнопка выход (спрайт временный)
        Texture exitT;
        exitT.loadFromFile("sprites\\exit.png");
        Sprite exitButton(exitT);
        exitButton.setPosition(200, 300);
        exitButton.setScale(0.5, 0.5);
        window.draw(exitButton);

        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i mousePos = Mouse::getPosition(window);

            //проверка кнопки "старт"
            if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                state = choosecharacter;
            }

            //проверка кнопки "выход"
            if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                state = gameover2;
            }
        }
        //временно,пока не работает как надо
        if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
            state = InGame;
        }
        window.display();
    };

    void ChooseCharacter() {
          //фон
           Texture backgroundCCTexture;
           backgroundCCTexture.loadFromFile("sprites\\backMenu.png");
           Sprite ccback(backgroundCCTexture);
           ccback.setScale(0.75, 0.75);
           window.draw(ccback);

           //персонажи для выбора
           Texture chikat;
           chikat.loadFromFile("sprites\\CHIKAstraight.png");//Чика
           Sprite chika(chikat);
           chika.setPosition(450, 250);//ЕЩЕ ИЗМЕНИМ
           chika.setScale(2, 2);
           window.draw(chika);


           Texture kikat;
           kikat.loadFromFile("sprites\\CHIKAleft.png");//Кика(файл поменять)
           Sprite kika(kikat);
           kika.setPosition(450, 250);//ЕЩЕ ИЗМЕНИМ
           kika.setScale(2, 2);
           window.draw(kika);

        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i mousePos = Mouse::getPosition(window);

            //проверка выбора персонажа CHIKA
            if (chika.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                selectedCharacter = CHIKA;
                state = InGame;
            }

            //проверка выбора персонажа KIKA
            if (kika.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                selectedCharacter = KIKA;
                state = InGame;
            }
        }
        window.display();
    }//доработать,персонажи не выбираются
    void game() {
        //фон
        Texture backgroundGAMETexture;
        backgroundGAMETexture.loadFromFile("sprites\\backGAME.jpg");
        Sprite background(backgroundGAMETexture);
        background.setScale(0.75, 0.75);

        //отрисовка сердец
        Texture heart3;
        heart3.loadFromFile("sprites\\heartFull.png");
        Sprite fullheart(heart3);

        Texture heart2;
        heart2.loadFromFile("sprites\\2hearts.png");
        Sprite twoheart(heart2);

        Texture heart1;
        heart1.loadFromFile("sprites\\1heart.png");
        Sprite oneheart(heart1);

        switch (hearts) {
        case 3:
            fullheart.setPosition(200, 300);
            fullheart.setScale(0.5, 0.5);
            window.draw(fullheart);
            break;
        case 2:
            twoheart.setPosition(200, 300);
            twoheart.setScale(0.5, 0.5);
            window.draw(twoheart);
            break;
        case 1:
            oneheart.setPosition(200, 300);
            oneheart.setScale(0.5, 0.5);
            window.draw(oneheart);
            break;
        }

        //кол-во допов в углу надо еще
        Texture dooop;
        dooop.loadFromFile("sprites\\dop.jpg");
        Sprite dooop1(dooop);
        dooop1.setPosition(100, 300);
        dooop1.setScale(0.5, 0.5);
        window.draw(dooop1);
        //и само количество надо еще вывести на экран,но с этим проблема

        window.display();
    }
    void GameOver() {
        //фон
        Texture backgroundTexture;
        backgroundTexture.loadFromFile("sprites\\backGO.jpg");
        Sprite background(backgroundTexture);
        background.setScale(0.75, 0.75);

        Text dopsText;
        Text timeText;
        Font font;
        font.loadFromFile("font\\arial.ttf");

        dopsText.setFont(font);
        timeText.setFont(font);
        dopsText.setCharacterSize(30);
        timeText.setCharacterSize(30);
        dopsText.setFillColor(Color::Red);
        timeText.setFillColor(Color::Red);

        int dops = person.DOPS();
        string dopsString = "You have " + to_string(dops) + " dops";
        dopsText.setString(dopsString);
        dopsText.setPosition(100, 100);

        string dopsString = "Time in game: " + to_string(time);
        dopsText.setString(dopsString);
        dopsText.setPosition(100, 100);
       
        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i mousePos = Mouse::getPosition(window);

            if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                state = gameover2;
            }
            if (RestartButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                state = choosecharacter;
            }
        }
        window.draw(background);
        window.draw(dopsText);
        window.display();
    }
    void Setup(){     
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
        Dop dops[25];
        Zat zacheti[15];
        int dopcount = 0;
        int zachcount = 0;
        bool Gameover = 0;

        while (window.isOpen() && !Gameover)
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

            //возможный звук "настало время выдавать допы"
            if (time > 3 && doptimer > speed_creation && dopcount < 25) {
                Dop tmp;
                tmp.Setup();
                dops[dopcount] = tmp;
                tmp.~Dop();
                dopcount++;
                doptimer = 0;
            }

            if (time > 3 && zachtimer > speed_creation && zachcount < 15) {
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
                        Gameover = 1;
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

            if (time > 5 && persontimer > 8 && time < 20) {
                person.SpeedChange(1);
                speed_zach += 2;
                for (int i = 0; i < zachcount; i++) {
                    zacheti[i].setSpeed(speed_zach);
                }
                persontimer = 0;
            }

            if (time >= 20 && persontimer > 8 && time < 40) {
                person.SpeedChange(3);
                speed_zach += 3;
                for (int i = 0; i < zachcount; i++) {
                    zacheti[i].setSpeed(speed_zach);
                }
                speed_creation -= 0.001;
                persontimer = 0;
            }

            if (time >= 40 && persontimer > 7 && time < 60) {
                person.SpeedChange(3);
                speed_zach += 3;
                for (int i = 0; i < zachcount; i++) {
                    zacheti[i].setSpeed(speed_zach);
                }
                speed_creation -= 0.005;
                persontimer = 0;
            }

            if (time >= 60 && persontimer > 6) {
                person.SpeedChange(3);
                speed_zach += 3;
                for (int i = 0; i < zachcount; i++) {
                    zacheti[i].setSpeed(speed_zach);
                }
                speed_creation -= 0.005;
                persontimer = 0;
            }
        }

    }
};