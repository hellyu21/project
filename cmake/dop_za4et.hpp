#include <SFML/Graphics.hpp>
using namespace sf;

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
	RectangleShape shape;
public:
	Zat() = default;

	~Zat() = default;

	void Setup() {
		type = rand() % (4 - 1 + 1) + 1;
		if (type == 1) {
			x = rand() % (1580 - 20 + 1) + 20;
			shape.setOrigin(2, 20);
			shape.setSize(Vector2f(4, 40));
		}
		if (type == 2) {
			x = rand() % (1580 - 20 + 1) + 20;
			y = 900;
			shape.setOrigin(2, 20);
			shape.setSize(Vector2f(4, 40));
		}
		if (type == 3) {
			y = rand() % (880 - 20 + 1) + 20;
			shape.setOrigin(20, 2);
			shape.setSize(Vector2f(40, 4));
		}
		if (type == 4) {
			y = rand() % (880 - 20 + 1) + 20;
			x = 1600;
			shape.setOrigin(20, 2);
			shape.setSize(Vector2f(40, 4));
		}
		shape.setPosition(x, y);
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
		shape.setPosition(x, y);
	}

	RectangleShape Get()
	{
		return shape;
	}

	int TYPE() { return type; };
	double X() { return x; };
	double Y() { return y; };
};