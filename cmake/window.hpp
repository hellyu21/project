#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <string>
#include "person.hpp"
#include "dop_za4et.hpp"


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
    sf::RenderWindow window;
    Chika person;
    Zat zat;
    Dop dop2;
    float Time = 0;
    int scx = 1600;
    int scy = 900;
    float speed_creation = 5;
    int speed_zach = 140;

    std::string records[11];
    int n = 0;
    
    enum  State { menu, choosecharacter, InGame, gameover};//разные состояния игры
    State state;
public:
   
    Game() { 
        srand(time(0));
        window.create(sf::VideoMode(scx, scy), "Incredible adventure of a student!");
        state = menu;
    }

    void run() {
        while (window.isOpen()) {
            processEvents();
            update();
        }
    }

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
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
            state = gameover;
            break;
        case gameover:
            GameOver();//рестарт/выход
            break;
        }
    }

    void Menu() {
        //фон
        sf::Texture backgroundMenuTexture; 
        backgroundMenuTexture.loadFromFile("sprites\\backMenu.png"); 
        sf::Sprite background(backgroundMenuTexture);
        background.setScale(0.75, 0.75);
        window.draw(background);

        //текст
        sf::Text nameText; 
        sf::Font font; 
        font.loadFromFile("font\\Trick.ttf");
        nameText.setFont(font);
        nameText.setCharacterSize(70);
        nameText.setOutlineThickness(15);
        nameText.setOutlineColor(sf::Color(250,149,18));
        nameText.setFillColor(sf::Color::Black);
        std::string nameString = "Incredible\nadventure\nof a student!"; 
        nameText.setString(nameString);
        nameText.setPosition(800, 200);
        window.draw(nameText);     

        //кнопка старт
        sf::Texture startTexture;
        startTexture.loadFromFile("sprites\\start.png");
        sf::Sprite startButton(startTexture);
        startButton.setPosition(100, 200);
        window.draw(startButton);   

        //кнопка выход
        sf::Texture exitT;
        exitT.loadFromFile("sprites\\QUIT.png");
        sf::Sprite exitButton(exitT);
        exitButton.setPosition(100, 500);
        window.draw(exitButton);

        sf::Text spaceText;
        spaceText.setFont(font);
        spaceText.setCharacterSize(60);
        spaceText.setFillColor(sf::Color::Black);
        spaceText.setOutlineThickness(10);
        spaceText.setOutlineColor(sf::Color(250,149,18));
        std:: string spaceString = "Press SPACE to start";
        spaceText.setString(spaceString);
        spaceText.setPosition(800, 800);
        window.draw(spaceText);

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
            else if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    state = choosecharacter;
                else if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space) {
                    state = choosecharacter;
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }
      
        window.display();
    };

    void ChooseCharacter() {
          //фон
           sf::Texture backgroundCCTexture;
           backgroundCCTexture.loadFromFile("sprites\\backMenu.png");
           sf::Sprite ccback(backgroundCCTexture);
           ccback.setScale(0.75, 0.75);
           window.draw(ccback);

           //текст
           sf::Text chooseText;
           sf::Text num1;
           sf::Text num2;
           sf::Font font;
           font.loadFromFile("font\\Trick.ttf");
           chooseText.setFont(font); 
           chooseText.setCharacterSize(40);
           chooseText.setOutlineThickness(5);
           chooseText.setOutlineColor(sf::Color(250,149,18));
           chooseText.setFillColor(sf::Color::Black);
           std::string chooseString = "Choose your character";
           chooseText.setString(chooseString);
           chooseText.setPosition(500, 100); 
           window.draw(chooseText);

           num1.setFont(font);
           num1.setCharacterSize(40);
           num1.setOutlineThickness(5);
           num1.setOutlineColor(sf::Color(250, 149, 18));
           num1.setFillColor(sf::Color::Black);
           std::string num1s = "Chika";
           num1.setString(num1s);
           num1.setPosition(550, 550);
           window.draw(num1);

           num2.setFont(font); 
           num2.setCharacterSize(40); 
           num2.setOutlineThickness(5); 
           num2.setOutlineColor(sf::Color(250, 149, 18)); 
           num2.setFillColor(sf::Color::Black); 
           std::string num2s = "Kika";
           num2.setString(num2s);
           num2.setPosition(850, 550); 
           window.draw(num2);

           //персонажи для выбора
           sf::Texture chikat;
           chikat.loadFromFile("sprites\\CHIKAmenu.png");//Чика
           sf::Sprite chika(chikat);
           chika.setPosition(550, 250);
           chika.setScale(5, 5);
           window.draw(chika);

           sf::Texture kikat;
           kikat.loadFromFile("sprites\\KIKAmenu.png");//Кика
           sf::Sprite kika(kikat);
           kika.setPosition(850, 250);
           kika.setScale(5.5, 5.5);
           window.draw(kika);
         
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
            {
                if (chika.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    //person.typeCharacter(1);
                    state = InGame;
                }
                else if (kika.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    //person.typeCharacter(2);
                    state = InGame;
                }
            }
            else if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    state = menu;
        }
        window.display();
    }
    
    void GameOver() {
        //фон
        sf::Texture backgroundTexture;
        backgroundTexture.loadFromFile("sprites\\backGO.jpg");
        sf::Sprite background(backgroundTexture);
        background.setScale(1.5, 1.5);
        window.draw(background);
       
        //кнопка выход
        sf::Texture exitT;
        exitT.loadFromFile("sprites\\QUIT.png");
        sf::Sprite exitButton(exitT);
        exitButton.setPosition(100, 600);
        window.draw(exitButton);
       
        //кнопка рестарт
        sf::Texture restartTexture;
        restartTexture.loadFromFile("sprites\\RESTART.png");
        sf::Sprite restartButton(restartTexture);
        restartButton.setPosition(100, 400);
        window.draw(restartButton);
      
        sf::Text dopsText;
        sf::Text timeText;
        sf::Font font;
        font.loadFromFile("font\\Trick.ttf");
        dopsText.setFont(font);
        dopsText.setCharacterSize(30);
        dopsText.setOutlineThickness(3);
        dopsText.setOutlineColor(sf::Color(250,149,18));
        dopsText.setFillColor(sf::Color::Black);
        int dops = person.DOPS();
        std::string dopsString = "You have " + std::to_string(dops) + " dop(s).";
        if (dops == 0)
            dopsString += "\nIt's sad :(";
        if (0 < dops && dops < 8)
            dopsString += "\nIt's bad -_-";
        if (8 <= dops && dops < 18)
            dopsString += "\nNot bad :/";
        if (18 <= dops && dops < 30)
            dopsString += "\nPretty good :)";
        if (30 <= dops && dops < 50)
            dopsString += "\nGreat :3";
        if (50 <= dops)
            dopsString += "\nInsane!!! ()-()";
        dopsText.setString(dopsString);
        dopsText.setPosition(100, 100);
        window.draw(dopsText);

        timeText.setFont(font);
        timeText.setCharacterSize(30);
        timeText.setOutlineThickness(3);
        timeText.setOutlineColor(sf::Color(250,149,18));
        timeText.setFillColor(sf::Color::Black);
        int timeIn = round(Time);
        std::string timeString = "Time in game: " + std::to_string(timeIn) + " seconds.";
        timeText.setString(timeString);
        timeText.setPosition(100, 250);
        window.draw(timeText);

        sf::Text recordText;
        recordText.setFont(font);
        recordText.setCharacterSize(30);
        recordText.setOutlineThickness(3);
        recordText.setOutlineColor(sf::Color(250, 149, 18));
        recordText.setFillColor(sf::Color::Black);
        std::string recordString = "RECORDS\n1. ";
        for (int i = 0; i < 9; i++) {
            recordString += records[i] + "\n" + std::to_string(i + 2) + ". ";
        }
        recordString += records[9];

        recordText.setString(recordString);
        recordText.setPosition(900, 100);
        window.draw(recordText);

        sf::Text secret;
        secret.setFont(font);
        secret.setCharacterSize(15);
        secret.setOutlineThickness(3);
        secret.setOutlineColor(sf::Color(250, 149, 18));
        secret.setFillColor(sf::Color::Black);
        std::string secretstr = "In game -> press space";
        secret.setString(secretstr);
        secret.setPosition(1350, 870);
        window.draw(secret);

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event)) { 
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == event.MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) 
            { 
                if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    window.close();
                else if (restartButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) 
                    state = choosecharacter;
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }            
            }
        }
        window.display();
    }

    void Setup(){person.Setup(scx, scy);}

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

    int count(std::string str) {
        int n = 0;
        for (int i = 0; i < str.size(); i++)
            if (str[i] == '\ ')
                n = i;
        std::string tmp = "";
        for (int i = 0; i < n + 1; i++) {
            tmp += str[i];
        }
        n = atoi(tmp.c_str());
        return n;
    }

    void Records() {
        std::ifstream in("sprites\\Records.txt");
        if (!in.is_open()) {
            std::cout << "Error file" << std::endl;
        }

        in >> n;
        std::string tmp;
        getline(in, tmp);
        for (int i = 0; i < n; i++)
            getline(in, records[i]);

        if (n != 10) 
            for (int i = n; i < 10; i++)
                records[i] = "0";

        int curdop = person.DOPS(); 
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
        auto str = oss.str();
        records[n] = std::to_string(curdop) + " " + str;
        for (int i = n; i >= 1; i--) {
            int dopsup = count(records[i-1]);
            int dopsdown = count(records[i]);
            if (dopsup < dopsdown) {
                std::string tmp = records[i];
                records[i] = records[i - 1];
                records[i - 1] = tmp;
            }
        }

        n = 10;
        in.close();


        std::ofstream out("sprites\\Records.txt");
        out << n << "\n";
        for (int i = 0; i < n; i++)
            out << records[i] << "\n";
        out.close();
    }

    void Life() {
        sf::Clock clock;
        float doptimer = 0;
        float zachtimer = 0;
        float persontimer = 0;
        float steptimer = 0;
        float backtimer = 0;
        Dop dops[25];
        Zat zacheti[15];
        int dopcount = 0;
        int zachcount = 0;
        bool Gameover = 0;
        bool flag = 1;
        int LastTime = 0;

        //обнуляем допы, сердца, и время
        Time = 0;
        person.nullDop();
        person.nullHearts();
        person.defSpeed();

        float speed_creation = 5;
        int speed_zach = 200;

        sf::Music music;
        music.openFromFile("sprites\\time_dop.wav");
        sf::Music sound;
        sound.openFromFile("sprites\\MV.wav");
        sound.setLoop(true);

        //фон
        sf::Texture backgroundGAMETexture;
        backgroundGAMETexture.loadFromFile("sprites\\backGame.png");
        sf::Sprite background(backgroundGAMETexture);
        
        //отрисовка жизней
        sf::Texture heart3;
        heart3.loadFromFile("sprites\\3hearts.png");
        sf::Sprite fullheart(heart3);

        sf::Texture heart2;
        heart2.loadFromFile("sprites\\2hearts.png");
        sf::Sprite twoheart(heart2);

        sf::Texture heart1;
        heart1.loadFromFile("sprites\\1heart.png");
        sf::Sprite oneheart(heart1);
        
        //счетчик допов
        sf::Texture dooop;
        dooop.loadFromFile("sprites\\dop.png");
        sf::Sprite dooop1(dooop);
        dooop1.setPosition(250, 40);
        dooop1.setScale(2, 2);

        sf::Text dopsText;
        sf::Font font;
        font.loadFromFile("font\\Trick.ttf");
        dopsText.setFont(font);
        dopsText.setCharacterSize(30);
        dopsText.setOutlineThickness(3);
        dopsText.setOutlineColor(sf::Color::White);
        dopsText.setFillColor(sf::Color::Black);
        dopsText.setPosition(350, 60);
       
        while (window.isOpen() && !Gameover)
        {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::KeyPressed)
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        Gameover = 1;
                        sound.stop();
                        Records();
                    }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                //person.typeCharacter(3);
                person.Setup(scx, scy);
                sound.play();
                window.draw(person.Get());
            }

            float dt = clock.getElapsedTime().asSeconds();
            clock.restart();
            Time += dt;
            doptimer += dt;
            persontimer += dt;
            zachtimer += dt;
            backtimer += dt;
            steptimer += dt;

            if (Time > 2.65  && flag) {
                music.play();
                flag = 0;
            }
            if (Time > 3 && doptimer > speed_creation && dopcount < 25) {
                dops[dopcount].Setup();
                dopcount++;
                doptimer = 0;
            }

            if (Time > 3 && zachtimer > speed_creation && zachcount < 15) {
                zacheti[zachcount].Setup();
                zachcount++;
                zachtimer = 0;
            }

            int touch = TouchBorder(person);
            if (!touch) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    person.Move(1, dt, steptimer);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    person.Move(2, dt, steptimer);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    person.Move(3, dt, steptimer);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    person.Move(4, dt, steptimer);
            }
            else if (touch == 1)
                person.Move(2, dt, steptimer);
            else if (touch == 2)
                person.Move(1, dt, steptimer);
            else if (touch == 3)
                person.Move(4, dt, steptimer);
            else if (touch == 4)
                person.Move(3, dt, steptimer);

            window.clear();
            if (/*person.typeCharacter() == 3 && */backtimer > 0.4) {
                int r = rand() % (250 - 0 + 1) + 0;
                int g = rand() % (250 - 0 + 1) + 0;
                int b = rand() % (250 - 0 + 1) + 0;
                background.setColor(sf::Color(r, g, b));
                backtimer = 0;
            }
            window.draw(background);

            int hearts = person.Hearts();
            if (hearts == 3)
            {
                fullheart.setPosition(50, 50);
                fullheart.setScale(0.75, 0.75);
                window.draw(fullheart);
            }
            else if (hearts == 2)
            {
                twoheart.setPosition(50, 50);
                twoheart.setScale(0.75, 0.75);
                window.draw(twoheart);
            }
            else if (hearts == 1)
            {
                oneheart.setPosition(50, 50);
                oneheart.setScale(0.75, 0.75);
                window.draw(oneheart);
            }
            window.draw(dooop1);

            int dopes = person.DOPS();
            std::string dopsString = std::to_string(dopes);
            dopsText.setString(dopsString);
            window.draw(dopsText);
            for (int i = 0; i < zachcount; i++) {
                int typezat = zacheti[i].TYPE();
                if ((typezat == 1 && zacheti[i].Y() - 20 > 900) ||
                    (typezat == 2 && zacheti[i].Y() + 20 < 0) || 
                    (typezat == 3 && zacheti[i].X() - 20 > 1600) ||
                    (typezat == 4 && zacheti[i].X() + 20 < 0)) {
                    zacheti[i] = zacheti[zachcount - 1];
                    zachcount--;
                }
            }

            for (int i = 0; i < zachcount; i++) {
                if (TouchZat(person, zacheti[i])) {
                    zacheti[i] = zacheti[zachcount - 1];
                    zachcount--;
                    person.Minusheart();
                    if (person.Hearts() == 0) {
                        window.clear();
                        Gameover = 1;
                        sound.stop();
                        Records();
                    }
                }
            }

            for (int i = 0; i < zachcount; i++) {
                int typezat = zacheti[i].TYPE();
                zacheti[i].Move(typezat, dt);
                window.draw(*zacheti[i].Get());
            }

            for (int i = 0; i < dopcount; i++) {
                if (TouchDop(person, dops[i])) {
                    dops[i] = dops[dopcount-1];
                    dopcount--;
                    person.plusDop();
                }
                dops[i].Move(Time);
                window.draw(dops[i].Get());
            }
            window.draw(person.Get());
           

            if (Time > 5 && persontimer > 5 && Time < 20) {
                person.SpeedChange(4);
                speed_zach += 8;
                for (int i = 0; i < zachcount; i++) {
                    zacheti[i].setSpeed(speed_zach);
                }
                persontimer = 0;
            }

            if (Time >= 20 && persontimer > 2 && LastTime != round(Time)) {
                LastTime = round(Time);
                person.SpeedChange(4);
                speed_zach += 5;
                for (int i = 0; i < zachcount; i++) {
                    zacheti[i].setSpeed(speed_zach);
                }
                if (speed_creation > 1)
                    speed_creation -= 0.2;
                persontimer = 0;
            }
            window.display();
        }
    }
};