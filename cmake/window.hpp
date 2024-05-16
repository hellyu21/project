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
    //int maxScore;
    //int currentScore = 0;
    RenderWindow window;
    Person person;
    int scx = 1600;
    int scy = 900;
    double speed_creation = 5;
    enum  State { menu, choosecharacter, InGame, GameOver };//разные состояния игры
    State state;
    
   
public:
   
    Game() {
        srand(time(0));
        state = menu;
        //maxScore = loadMaxScore(); //грузим максимальный рекорд из файла
        window.create(VideoMode(scx, scy), "Incredible adventure of a student!");
    }

    void run() {
        while (window.isOpen()) {
            processEvents();
            update();
            render();
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
            state = choosecharacter;
            break;
        case choosecharacter:
            //проработать,чтобы выбор происходил и соотв.спрайты персонажу присваивались
            state = InGame;
            break;
        case InGame:
            Setup();
            Life();
            state = GameOver;
            break;
        case GameOver:
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
            }
            break;
        }
    }
   
    void render() {//тут прорисовка всех режимов, почти готово, надо только координаты кнопок прикинуть
        window.clear();
        if (state == menu) {
            //фон
            Texture backgroundTexture;
            backgroundTexture.loadFromFile("sprites\\backMenu.png");
            Sprite background(backgroundTexture);
            background.setScale(0.75, 0.75);
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

            //добавить рекорды

        }
        else if (state == choosecharacter)
        {
            //фон
            Texture backgroundTexture;
            backgroundTexture.loadFromFile("sprites\\backMenu.png");
            Sprite background(backgroundTexture);
            background.setScale(0.75, 0.75);
            window.draw(background);

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
        }
        else if (state == InGame) {
            //фон
            Texture backgroundTexture;
            Sprite background(backgroundTexture);
            background.setScale(0.75, 0.75);
            backgroundTexture.loadFromFile("sprites\\backGAME.jpg");
        }
        else if (state == GameOver) {//добавить еще кнопку выхода?? +результаты игры (время в игре, количество допов, рекорд*)
            //фон
            Texture backgroundTexture;
            Sprite background(backgroundTexture);
            background.setScale(0.75, 0.75);
            backgroundTexture.loadFromFile("sprites\\backGO.jpg");
            //кнопки надо?
            //данные по игре добавить
        }
        window.display();
    }
    //все что дальше в комментах надо доработать

    void Menu() {
        sleep(milliseconds(5000));
        //if (Mouse::isButtonPressed(Mouse::Left)) {
        //    Vector2i mousePos = Mouse::getPosition(window);

        //    // Проверка нажатия на кнопку "Start"
        //    if (mousePos.x >= 0 && mousePos.x <= 0 && mousePos.y >= 0 && mousePos.y <= 0) {//циферки подогнать как установим кнопки в нужном месте
        //        state = ChooseCharacter;
        //    }

        //    //проверку кнопки "выход"
        //    if (mousePos.x >= 0 && mousePos.x <= 0 && mousePos.y >= 0 && mousePos.y <= 0) {//циферки подогнать как установим кнопки в нужном месте
        //        state = GameOver;
        //    }
        //}
    };//доработать по координатам

    //void ChooseCharacter() {//еще подредачу координаты
    //    if (Mouse::isButtonPressed(Mouse::Left)) {
    //        Vector2i mousePos = Mouse::getPosition(window);

    //        //проверка выбора персонажа CHIKA
    //        if (mousePos.x >=  && mousePos.x <=  && mousePos.y >=  && mousePos.y <= ) {
    //            
    //            state = InGame;
    //           //установить спрайты этого персонажа
    //        }

    //        //проверка выбора персонажа KIKA
    //        if (mousePos.x >=  && mousePos.x <=  && mousePos.y >=  && mousePos.y <= ) {
    //            state = InGame;
    //            //установить спрайты этого персонажа
    //        }
    //    }
    //}//доработать

    void Setup(){
  
      //  window.create(VideoMode(scx, scy), "Incredible adventure of a student!");
     
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

    //то что дальше в комментах--на  перспективу,мб все таки сделаем,пригодится
   /* int loadMaxScore() {
        int score = 0;
        ifstream file("Record.txt");
        if (file.is_open()) {
            file >> score;
            file.close();
        }
        return score;
    }

    void saveMaxScore(int score) {
        ofstream file("Record.txt");
        if (file.is_open()) {
            file << score;
            file.close();
        }
    }*/

   /* void GameOver(){
        while (window.isOpen()) {
            window.draw(person.Get());
        }
    }*/
   
};