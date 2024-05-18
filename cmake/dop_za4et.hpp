#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Dop {
	double x;
	double y;
	double time;
	CircleShape shape;

	

public:
	Dop() = default;

	void Setup() {
		x = rand() % (1580 - 20 + 1) + 20;
		y = rand() % (880 - 20 + 1) + 20;
		shape.setOrigin(10, 10);
		shape.setRadius(10);
		shape.setPosition(x, y);
	}

	~Dop() = default;

	void Move(double time) {
		y += sin(time)*0.05;
		shape.setPosition(x, y);
	}

	Dop operator=(Dop gotdop) {
		x = gotdop.x;
		y = gotdop.y;
		time = gotdop.time;
		shape = gotdop.shape;
		return *this;
	}

	//геттеры и сеттеры
	double X() { return x; };
	double Y() { return y; };

	CircleShape Get()
	{
		return shape;
	}
};

class Zat {
	double x = 0;
	double y = 0;
	int type;
	int speed = 140;

	//для зачета
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
			sprite.setOrigin(textureDown.getSize().x / 2, textureDown.getSize().y);
			
		}
		if (type == 2) {//снизу
			x = rand() % (1580 - 20 + 1) + 20;
			y = 900;
			sprite.setTexture(textureUp);
			sprite.setOrigin(textureUp.getSize().x / 2, textureUp.getSize().y);
		}
		if (type == 3) {//слева
			y = rand() % (880 - 20 + 1) + 20;
			sprite.setTexture(textureRight);
			sprite.setOrigin(textureRight.getSize().x / 2, textureRight.getSize().y);
		}
		if (type == 4) {//справа
			y = rand() % (880 - 20 + 1) + 20;
			x = 1600;
			sprite.setTexture(textureLeft);
			sprite.setOrigin(textureLeft.getSize().x / 2, textureLeft.getSize().y);
		}
		sprite.setPosition(x, y);
	}

	void Move(int type, double dt) {
		if (type == 1)//сверху вниз
			y += speed * dt;
		if (type == 2)//снизу вверх
			y -= speed * dt;
		if (type == 3)//слева направо
			x += speed * dt;
		if (type == 4)//справа налево
			x -= speed * dt;
		sprite.setPosition(x, y);
	}

	Sprite Get()
	{
		return sprite;
	};

	int TYPE() { return type; };
	double X() { return x; };
	double Y() { return y; };
	void setSpeed(int gspeed) { speed = gspeed; };
};