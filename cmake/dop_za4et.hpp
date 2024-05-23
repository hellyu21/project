#include <SFML/Graphics.hpp>


class Dop {
	double x;
	double y;
	double time;
	sf::Texture dop;
	sf::Sprite sprite;
public:
	Dop() = default;

	void Setup() {
		x = rand() % (1580 - 20 + 1) + 20;
		y = rand() % (880 - 20 + 1) + 20;
		dop.loadFromFile("sprites\\dop.png");
		sprite.setTexture(dop);
		sprite.setOrigin(dop.getSize().x / 2, dop.getSize().y/2);
		sprite.setPosition(x, y);
	}

	~Dop() = default;

	void Move(double time) {
		y += sin(time)*0.05;
		sprite.setPosition(x, y);
	}

	Dop operator=(Dop gotdop) {
		x = gotdop.x;
		y = gotdop.y;
		time = gotdop.time;
		dop.loadFromFile("sprites\\dop.png");
		sprite.setTexture(dop);
		return *this;
	}

	//геттеры и сеттеры
	double X() { return x; };
	double Y() { return y; };

	sf::Sprite Get() { return sprite; };
};

class Zat {
	double x = 0;
	double y = 0;
	int type;
	int speed = 140;

	//для зачета
	sf::Texture textureUp;
	sf::Texture textureDown;
	sf::Texture textureLeft;
	sf::Texture textureRight;

	sf::Sprite* sprite = nullptr;
public:
	Zat()
	{
		textureUp.loadFromFile("sprites\\ZACHup.png");
		textureDown.loadFromFile("sprites\\ZACHdown.png");
		textureLeft.loadFromFile("sprites\\ZACHleft.png");
		textureRight.loadFromFile("sprites\\ZACHRight.png");
	}

	Zat(const Zat& other) = delete;


	~Zat()
	{
		if (sprite != nullptr)
			delete sprite;
	}

	void Setup() {
		if (sprite != nullptr)
			delete sprite;
		sprite = new sf::Sprite;
		type = rand() % (4 - 1 + 1) + 1;
		if (type == 1) {//сверху
			x = rand() % (1580 - 20 + 1) + 20;
			y = 0;
			sprite->setTexture(textureDown);
			sprite->setOrigin(textureDown.getSize().x / 2, textureDown.getSize().y/2);
			sprite->setScale(2, 2);
			
		}
		if (type == 2) {//снизу
			x = rand() % (1580 - 20 + 1) + 20;
			y = 900;
			sprite->setTexture(textureUp);
			sprite->setOrigin(textureUp.getSize().x / 2, textureUp.getSize().y/2);
			sprite->setScale(2, 2);
		}
		if (type == 3) {//слева
			x = 0;
			y = rand() % (880 - 20 + 1) + 20;
			sprite->setTexture(textureRight);
			sprite->setOrigin(textureRight.getSize().x / 2, textureRight.getSize().y/2);
			sprite->setScale(2, 2);
		}
		if (type == 4) {//справа
			y = rand() % (880 - 20 + 1) + 20;
			x = 1600;
			sprite->setTexture(textureLeft);
			sprite->setOrigin(textureLeft.getSize().x / 2, textureLeft.getSize().y/2);
			sprite->setScale(2, 2);
		}
		sprite->setPosition(x, y);
	}

	Zat& operator=(Zat& gotzat)
	{
		x = gotzat.x;
		y = gotzat.y;
		speed = gotzat.speed;
		type = gotzat.type;
		textureUp = gotzat.textureUp;
		textureDown = gotzat.textureDown;
		textureLeft = gotzat.textureLeft;
		textureRight = gotzat.textureRight;

		sprite = new sf::Sprite;
		*sprite = *(gotzat.sprite);
		return *this;
	}

	void Move(int type, double dt) {
		if (type == 1)//сверху вниз
		{
			sprite->setTexture(textureDown);
			y += speed * dt;
		}
		if (type == 2)//снизу вверх
		{
			sprite->setTexture(textureUp);
			y -= speed * dt;
		}
		if (type == 3)//слева направо
		{
			sprite->setTexture(textureRight);
			x += speed * dt;
		}
			
		if (type == 4)//справа налево
		{
			sprite->setTexture(textureLeft);
			x -= speed * dt;
		}
			
		sprite->setPosition(x, y);
	}

	sf::Sprite* Get() { return sprite; };
	int TYPE() { return type; };
	double X() { return x; };
	double Y() { return y; };
	void setSpeed(int gspeed) { speed = gspeed; };
};

