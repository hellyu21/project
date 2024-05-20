#include <SFML/Graphics.hpp>
//штуки,с которыми ошибки
//#include <SFML/OpenGL.hpp>
using namespace sf;
using namespace std;

class Dop {
	double x;
	double y;
	double time;
	Texture dop;
	Sprite sprite1;
public:
	Dop() = default;
	//не хочет отрисовать доп:(
	void Setup() {
		sprite1.setTexture(dop);
		sprite1.setOrigin(dop.getSize().x / 2, dop.getSize().y/2);
		x = rand() % (1580 - 40 + 1) + 40;
		y = rand() % (880 - 40 + 1) + 40;
		sprite1.setPosition(x, y);
	}

	~Dop()=default;

	void Move(double time) {
		y += sin(time)*0.05;
		sprite1.setTexture(dop);
		sprite1.setPosition(x, y);
	}

	Dop operator=(Dop gotdop) {
		x = gotdop.x;
		y = gotdop.y;
		time = gotdop.time;
		sprite1 = gotdop.sprite1;
		return *this;
	}

	//геттеры и сеттеры
	double X() { return x; }
	double Y() { return y; }
	Sprite Get(){ return sprite1; }
};

class Zat {
	double x = 0;
	double y = 0;
	int type;
	int speed = 120;

	Texture textureUp;
	Texture textureDown;
	Texture textureLeft;
	Texture textureRight;

	Sprite sprite;
public:
	Zat() = default;

	~Zat() = default;
	void Setup() {
		textureUp.loadFromFile("sprites\\ZACHup.png");
		textureDown.loadFromFile("sprites\\ZACHdown.png");
		textureLeft.loadFromFile("sprites\\ZACHleft.png");
		textureRight.loadFromFile("sprites\\ZACHRight.png");
		type = rand() % (4 - 1 + 1) + 1;
		if (type == 1) {//сверху
			x = rand() % (1580 - 20 + 1) + 20;
			sprite.setTexture(textureDown);
			sprite.setOrigin(textureDown.getSize().x / 2, textureDown.getSize().y/2);
			sprite.setScale(2, 2);
			
		}
		if (type == 2) {//снизу
			x = rand() % (1580 - 20 + 1) + 20;
			y = 900;
			sprite.setTexture(textureUp);
			sprite.setOrigin(textureUp.getSize().x / 2, textureUp.getSize().y/2);
			sprite.setScale(2, 2);
		}
		if (type == 3) {//слева
			y = rand() % (880 - 20 + 1) + 20;
			sprite.setTexture(textureRight);
			sprite.setOrigin(textureRight.getSize().x / 2, textureRight.getSize().y/2);
			sprite.setScale(2, 2);
		}
		if (type == 4) {//справа
			y = rand() % (880 - 20 + 1) + 20;
			x = 1600;
			sprite.setTexture(textureLeft);
			sprite.setOrigin(textureLeft.getSize().x / 2, textureLeft.getSize().y/2);
			sprite.setScale(2, 2);
		}
		sprite.setPosition(x, y);
	}

	void Move(int type, double dt) {
		if (type == 1)//сверху вниз
		{
			sprite.setTexture(textureDown);
			y += speed * dt;
		}
		if (type == 2)//снизу вверх
		{
			sprite.setTexture(textureUp);
			y -= speed * dt;
		}
		if (type == 3)//слева направо
		{
			sprite.setTexture(textureRight);
			x += speed * dt;
		}
			
		if (type == 4)//справа налево
		{
			sprite.setTexture(textureLeft);
			x -= speed * dt;
		}
			
		sprite.setPosition(x, y);
	}

	Sprite Get() { return sprite; }
	int TYPE() { return type; }
	double X() { return x; }
	double Y() { return y; }
	void setSpeed(int gspeed) { speed = gspeed; }
};