#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Dop {
	double x;
	double y;
	double time;
	Texture doP;
	Sprite sprite;
	

public:
	Dop() = default;
	//�� ����� ���������� ���:(
	void Setup() {
		x = rand() % (1580 - 20 + 1) + 20;
		y = rand() % (880 - 20 + 1) + 20;
		doP.loadFromFile("sprites\\dop.png");
		sprite.setTexture(doP);
		sprite.setOrigin(doP.getSize().x / 2, doP.getSize().y/2);
		/*sprite.setScale(0.25, 0.25);*/
		sprite.setPosition(x, y);
	}

	~Dop() = default;

	void Move(double time) {
		y += sin(time)*0.05;
		sprite.setTexture(doP);
		sprite.setPosition(x, y);
	}

	Dop operator=(Dop gotdop) {
		x = gotdop.x;
		y = gotdop.y;
		time = gotdop.time;
		sprite = gotdop.sprite;
		return *this;
	}

	//������� � �������
	double X() { return x; };
	double Y() { return y; };

	Sprite Get()
	{
		return sprite;
	}
};
//������ ��� ���� ����� �����
class Zat {
	double x = 0;
	double y = 0;
	int type;
	int speed = 140;

	//��� ������
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
		if (type == 1) {//������
			x = rand() % (1580 - 20 + 1) + 20;
			sprite.setTexture(textureDown);
			sprite.setOrigin(textureDown.getSize().x / 2, textureDown.getSize().y/2);
			sprite.setScale(2, 2);
			
		}
		if (type == 2) {//�����
			x = rand() % (1580 - 20 + 1) + 20;
			y = 900;
			sprite.setTexture(textureUp);
			sprite.setOrigin(textureUp.getSize().x / 2, textureUp.getSize().y/2);
			sprite.setScale(2, 2);
		}
		if (type == 3) {//�����
			y = rand() % (880 - 20 + 1) + 20;
			sprite.setTexture(textureRight);
			sprite.setOrigin(textureRight.getSize().x / 2, textureRight.getSize().y/2);
			sprite.setScale(2, 2);
		}
		if (type == 4) {//������
			y = rand() % (880 - 20 + 1) + 20;
			x = 1600;
			sprite.setTexture(textureLeft);
			sprite.setOrigin(textureLeft.getSize().x / 2, textureLeft.getSize().y/2);
			sprite.setScale(2, 2);
		}
		sprite.setPosition(x, y);
	}

	void Move(int type, double dt) {
		if (type == 1)//������ ����
		{
			sprite.setTexture(textureDown);
			y += speed * dt;
		}
		if (type == 2)//����� �����
		{
			sprite.setTexture(textureUp);
			y -= speed * dt;
		}
		if (type == 3)//����� �������
		{
			sprite.setTexture(textureRight);
			x += speed * dt;
		}
			
		if (type == 4)//������ ������
		{
			sprite.setTexture(textureLeft);
			x -= speed * dt;
		}
			
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