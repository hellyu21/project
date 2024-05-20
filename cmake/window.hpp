#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <iostream>
#include "person.hpp"
#include "dop_za4et.hpp"
using namespace sf;
using namespace std;

//ошибки:
//если рестартишь игру,почему то вместо фона растянут твой персонаж
//при смерти все ломается.
//если игра длится дольше N времени,все ломается(но мб это из-за текстур,опять же.Все таки ошибки только с ними):(

//таски:
//звук воспроизвести (делала все как в 4 лабе, но почему то тут не хочет воспроизводиться звук)
//допы должны получить свою текстуру и отобразиться во время игры


//ДОСТИЖЕНИЯ:
//меню работает как надо,
// выбор персонажа делается
// игра играется
// итоги игры выводятся корректно(кол-во допов и время в игре),  ---теперь нет,игра ломается
// все кнопки во всех состояниях игры работают
int TouchBorder(Person& obj) {
    double x = obj.X();
    double y = obj.Y();
    
    if (x + 30 > 1600)
        return 4; // right
    else if (x - 30 < 0)
        return 3; // left
    else if (y + 50 > 900)
        return 2; //down
    else if (y - 50 < 0)
        return 1; //up
    else
        return 0;
}

class Game {
private:
    RenderWindow window;
    Person person;
    Zat zat;
    Dop dop2;
    float Time = 0;
    int scx = 1600;
    int scy = 900;
    int speed_creation = 5;
    int speed_zach = 140;
    
    enum  State { menu, choosecharacter, InGame, gameover1, gameover2 };//разные состояния игры
    State state;
    SoundBuffer buffer;
    Sound soundEffect;
    
   
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
            break;
        case InGame:
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
        background.setScale(0.75, 0.75);
        window.draw(background);

        //текст
        Text nameText;
        Font font;
        font.loadFromFile("font\\arial_narrow.ttf");
        nameText.setFont(font);
        nameText.setCharacterSize(55);
        nameText.setFillColor(Color::Black);
        string nameString = "Incredible adventure of a student!";
        nameText.setString(nameString);
        nameText.setPosition(800, 200);
        window.draw(nameText);

        //кнопка старт
        Texture startTexture;
        startTexture.loadFromFile("sprites\\start.png");
        Sprite startButton(startTexture);
        startButton.setPosition(100, 200);
        window.draw(startButton);

        //кнопка выход
        Texture exitT;
        exitT.loadFromFile("sprites\\QUIT.png");
        Sprite exitButton(exitT);
        exitButton.setPosition(100, 500);
        window.draw(exitButton);

        Text spaceText;
        spaceText.setFont(font);
        spaceText.setCharacterSize(60);
        spaceText.setFillColor(Color::Black);
        string spaceString = "Press SPACE to start";
        spaceText.setString(spaceString);
        spaceText.setPosition(800, 800);
        window.draw(spaceText);

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
        
        if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
            person.typeCharacter(1);//персонаж по умолчанию
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

           //текст
           Text chooseText;
           Font font;
           font.loadFromFile("font\\arial_narrow.ttf");
           chooseText.setFont(font);
           chooseText.setCharacterSize(40);
           chooseText.setFillColor(Color::Black);
           string chooseString = "Choose your character";
           chooseText.setString(chooseString);
           chooseText.setPosition(700, 100);
           window.draw(chooseText);

           //персонажи для выбора
           Texture chikat;
           chikat.loadFromFile("sprites\\CHIKAmenu.png");//Чика
           Sprite chika(chikat);
           chika.setPosition(550, 250);
           chika.setScale(5, 5);
           window.draw(chika);

           Texture kikat;
           kikat.loadFromFile("sprites\\KIKAmenu.png");//Кика
           Sprite kika(kikat);
           kika.setPosition(850, 250);
           kika.setScale(5, 5);
           window.draw(kika);

        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i mousePos = Mouse::getPosition(window);

            //проверка выбора персонажа CHIKA
            if (chika.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                person.typeCharacter(1);
                state = InGame;
            }

            //проверка выбора персонажа KIKA
            if (kika.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                person.typeCharacter(2);
                state = InGame;
            }
        }
        window.display();
    }
    
    void GameOver() {
        //фон
        Texture backgroundTexture;
        backgroundTexture.loadFromFile("sprites\\backGO.jpg");
        Sprite background(backgroundTexture);
        background.setScale(1.5, 1.5);
        window.draw(background);

        //кнопка выход
        Texture exitT;
        exitT.loadFromFile("sprites\\QUIT.png");
        Sprite exitButton(exitT);
        exitButton.setPosition(100, 600);
        window.draw(exitButton);

        //кнопка РЕСТАРТ
        Texture restartTexture;
        restartTexture.loadFromFile("sprites\\RESTART.png");
        Sprite restartButton(restartTexture);
        restartButton.setPosition(100, 400);
        window.draw(restartButton);

        Text dopsText;
        Text timeText;
        Font font;
        font.loadFromFile("font\\arial_narrow.ttf");

        dopsText.setFont(font);
        dopsText.setCharacterSize(30);
        dopsText.setFillColor(Color::Black);

        int dops = person.DOPS();
        string dopsString = "You have " + to_string(dops) + " dop(s).";
        dopsText.setString(dopsString);
        dopsText.setPosition(100, 100);

        timeText.setFont(font);
        timeText.setCharacterSize(30);
        timeText.setFillColor(Color::Black);
        string timeString = "Time in game: " + to_string(Time) + "seconds.";
        timeText.setString(timeString);
        timeText.setPosition(100, 250);
       
        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i mousePos = Mouse::getPosition(window);

            if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                state = gameover2;
            }
            if (restartButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                state = choosecharacter;
            }
        }
       
        window.draw(dopsText);
        window.draw(timeText);
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

        if ((xp - 30 < xd - 20) && (xd - 20 < xp + 30) 
            && (yp - 50 < yd - 20) && (yd - 20 < yp + 50))
            return true;
        else if ((xp - 30 < xd - 20) && (xd - 20 < xp + 30) 
            && (yp - 50 < yd + 20) && (yd + 20 < yp + 50))
            return true;
        else if ((xp - 30 < xd + 20) && (xd + 20 < xp + 30) 
            && (yp - 50 < yd + 20) && (yd + 20 < yp + 50))
            return true;
        else if ((xp - 30 < xd + 20) && (xd + 20 < xp + 30) 
            && (yp - 50 < yd - 20) && (yd - 20 < yp + 50))
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

        if (type == 1 && (xp - 30 < xz) && (xz < xp + 30) &&
            (yp - 50 < yz+40) && (yz + 40 < yp + 50))
            return true;
        else if (type == 2 && (xp - 30 < xz) && (xz < xp + 30) 
            && (yp - 50 < yz - 40) && (yz - 40 < yp + 50))
            return true;
        else if (type == 3 && (xp - 30 < xz + 40) && (xz + 40 < xp + 30) 
            && (yp - 50 < yz) && (yz < yp + 50))
            return true;
        else if (type == 4 && (xp - 30 < xz - 40) && (xz - 40 < xp + 30) 
            && (yp - 50 < yz) && (yz < yp + 50))
            return true;
        else
            return false;
    };

    void Life() {
        Clock clock;
        float doptimer = 0;
        float zachtimer = 0;
        float persontimer = 0;
        Dop dops[25];
        Zat zacheti[15];
        int dopcount = 0;
        int zachcount = 0;
        bool Gameover = 0;
        bool zvuk = 0; 

        Texture backgroundGAMETexture;
        backgroundGAMETexture.loadFromFile("sprites\\backGame.png");
        Sprite background(backgroundGAMETexture);
        
        //отрисовка жизней
        Texture heart3;
        heart3.loadFromFile("sprites\\3hearts.png");
        Sprite fullheart(heart3);

        Texture heart2;
        heart2.loadFromFile("sprites\\2hearts.png");
        Sprite twoheart(heart2);

        Texture heart1;
        heart1.loadFromFile("sprites\\1heart.png");
        Sprite oneheart(heart1);
        
        //допы
        Texture dooop;
        dooop.loadFromFile("sprites\\dop.png");
        Sprite dooop1(dooop);
        dooop1.setPosition(200, 30);
        dooop1.setScale(2, 2);

        Text dopsText;
        Font font;
        font.loadFromFile("font\\arial_narrow.ttf");
        dopsText.setFont(font);
        dopsText.setCharacterSize(30);
        dopsText.setFillColor(Color::Black);
        dopsText.setPosition(290, 30);

       

        while (window.isOpen() && !Gameover)
        {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
            }
            float dt = clock.getElapsedTime().asSeconds();
            clock.restart();
            Time += dt;
            doptimer += dt;
            persontimer += dt;
            zachtimer += dt;
            //buffer.loadFromFile("sprites\\time_dop.wav");
            //soundEffect.setBuffer(buffer); 
            //if (Time == 3 && !zvuk)
            //{
            //    soundEffect.play();//не воспроизводится..
            //    zvuk = 1;
            //}
            if (Time > 3 && doptimer > speed_creation && dopcount < 25) {
                Dop tmp;
                tmp.Setup();
                dops[dopcount] = tmp;
                tmp.~Dop();
                dopcount++;
                doptimer = 0;
            }

            if (Time > 3 && zachtimer > speed_creation && zachcount < 15) {
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
            window.draw(background);

            int hearts = person.Hearts();
            if (hearts == 3)
            {
                fullheart.setPosition(50, 30);
                fullheart.setScale(0.5, 0.5);
                window.draw(fullheart);
            }
            else if (hearts == 2)
            {
                twoheart.setPosition(50, 30);
                twoheart.setScale(0.5, 0.5);
                window.draw(twoheart);
            }
            else if (hearts == 1)
            {
                oneheart.setPosition(50, 30);
                oneheart.setScale(0.5, 0.5);
                window.draw(oneheart);
            }

            window.draw(dooop1);
            
            int dopes = person.DOPS();
            string dopsString = to_string(dopes);
            dopsText.setString(dopsString);
            window.draw(dopsText);

            for (int i = 0; i < zachcount; i++) {
                int typezat = zacheti[i].TYPE();
                if ((typezat == 1 && zacheti[i].Y() - 20 > 900) ||
                    (typezat == 2 && zacheti[i].Y() + 20 < 0) || 
                    (typezat == 3 && zacheti[i].X() - 20 > 1600) ||
                    (typezat == 4 && zacheti[i].X() + 20 < 0)) {
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
                    dops[dopcount - 1].~Dop();
                    dopcount--;
                    person.plusDop();
                }
                dops[i].Move(Time);
                window.draw(dops[i].Get());
            }
            window.draw(person.Get());
            window.display();

            if (Time > 5 && persontimer > 8 && Time < 20) {
                person.SpeedChange(1);
                speed_zach += 2;
                for (int i = 0; i < zachcount; i++) {
                    zacheti[i].setSpeed(speed_zach);
                }
                persontimer = 0;
            }

            if (Time >= 20 && persontimer > 8 && Time < 40) {
                person.SpeedChange(3);
                speed_zach += 3;
                for (int i = 0; i < zachcount; i++) {
                    zacheti[i].setSpeed(speed_zach);
                }
                speed_creation -= 0.001;
                persontimer = 0;
            }

            if (Time >= 40 && persontimer > 7 && Time < 60) {
                person.SpeedChange(3);
                speed_zach += 3;
                for (int i = 0; i < zachcount; i++) {
                    zacheti[i].setSpeed(speed_zach);
                }
                speed_creation -= 0.005;
                persontimer = 0;
            }

            if (Time >= 60 && persontimer > 6) {
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