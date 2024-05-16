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

	RectangleShape shape;
public:
	Person() = default;

	void Setup(double scx, double scy) {
		x = scx / 2;
		y = scy / 2;

		//тут все для CHIKA,исправлю,чтобы отдельно были персонажи
		textureUp.loadFromFile("sprites\\CHIKAstraight.png");
		textureDown.loadFromFile("sprites\\CHIKAback.png");
		textureLeft.loadFromFile("sprites\\CHIKAleft.png");
		textureRight.loadFromFile("sprites\\CHIKAright.png");
		
		sprite.setTexture(textureUp);
		sprite.setOrigin(textureUp.getSize().x / 2, textureUp.getSize().y);
		sprite.setPosition(x, y);
		/*shape.setOrigin(15, 25);
		shape.setSize(Vector2f(30, 50));
		shape.setPosition(x, y);*/
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

	Sprite Get()
	{
		return sprite;
	}
};