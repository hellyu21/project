#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Person{
	double x;
	double y;
	double speed = 150;
	int hearts = 3;
	int dops = 0;

	//спрайты
	Texture textureUp;
	Texture textureDown;
	Texture textureLeft;
	Texture textureRight;
	Sprite sprite;

	enum Character { CHIKA, KIKA };
	Character selectedCharacter;
public:
	Person() = default;

	void Setup(double scx, double scy) {
		x = scx / 2;
		y = scy / 2;

		switch (selectedCharacter) {
		case CHIKA:
			textureUp.loadFromFile("sprites\\CHIKAstraight.png");
			textureDown.loadFromFile("sprites\\CHIKAback.png");
			textureLeft.loadFromFile("sprites\\CHIKAleft.png");
			textureRight.loadFromFile("sprites\\CHIKAright.png");
			break;
		case KIKA:
			textureUp.loadFromFile("sprites\\KIKAstraight.png");
			textureDown.loadFromFile("sprites\\KIKAback.png");
			textureLeft.loadFromFile("sprites\\KIKAleft.png");
			textureRight.loadFromFile("sprites\\KIKAright.png");
			break;
		}

		sprite.setTexture(textureUp);
		sprite.setOrigin(textureUp.getSize().x / 2, textureUp.getSize().y);
		sprite.setScale(2, 2);
		sprite.setPosition(x, y);
	}

	~Person() = default;
	
	void SpeedChange(int delta) {
		speed += delta;
	}

	void Move(int i, double dt) {
		if (i == 1)//up
		{
			sprite.setTexture(textureDown);
			y -= speed * dt;
		}
		else if (i == 2) //down
		{
			sprite.setTexture(textureUp);
			y += speed * dt;
		}
		else if (i == 3) //left
		{
			sprite.setTexture(textureLeft);
			x -= speed * dt;
		}
		else if (i == 4) //right
		{
			sprite.setTexture(textureRight);
			x += speed * dt;
		}
		sprite.setPosition(x, y);
	}

	//геттеры и сеттеры
	double X() { return x; };
	double Y() { return y; };

	//не очень нужно
	int DOPS() { return dops; };
	int Hearts() { return hearts; };

	void plusDop() { dops++; }
	void Minusheart() { hearts--; };

	void typeCharacter(int i) {
		if (i == 1)
			selectedCharacter = CHIKA;
		if (i == 2)
			selectedCharacter = KIKA;
	}

	Sprite Get()
	{
		return sprite;
	}
};