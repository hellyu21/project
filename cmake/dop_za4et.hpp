#include <SFML/Graphics.hpp>

class Dop {
	double x;
	double y;
	double time;
	sf::CircleShape shape;
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

	sf::CircleShape Get()
	{
		return shape;
	}
};