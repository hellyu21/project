#include <SFML/Graphics.hpp>
#include <iostream>

class Person{
	double x;
	double y;
	double speed = 150;
	int hearts = 3;
	int dops = 0;
	sf::RectangleShape shape;
public:
	Person() = default;

	void Setup(double scx, double scy) {
		x = scx / 2;
		y = scy / 2;
		shape.setOrigin(15, 25);
		shape.setSize(sf::Vector2f(30, 50));
		shape.setPosition(x, y);
	}

	~Person() = default;

	void SpeedChange(int delta) {
		speed += delta;
	}

	void Move(int i, double dt) {
		if (i == 1)//up
			y -= speed * dt;
		else if (i == 2) //down
			y += speed * dt;
		else if (i == 3) //left
			x -= speed * dt;
		else if (i == 4) //right
			x += speed * dt;
		shape.setPosition(x, y);
	}

	//геттеры и сеттеры
	double X() { return x; };
	double Y() { return y; };
	int DOPS() { return dops; };

	void plusDop() { dops++; }

	sf::RectangleShape Get()
	{
		return shape;
	}
};