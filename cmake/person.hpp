#include <SFML/Graphics.hpp>
#include <iostream>

class Person{
	double x;
	double y;
	double speed = 140;
	
	int hearts = 3;
	int dops = 0;

	//спрайты
	sf::Texture menu;
	sf::Texture textureUp;
	sf::Texture textureDown;
	sf::Texture textureLeft;
	sf::Texture textureRight;
	sf::Sprite spriteChika;
	sf::Sprite spriteKika;

	enum Character { CHIKA, KIKA };
	Character selectedCharacter;
public:
	Person() = default;

	void Setup(double scx, double scy) {
		x = scx / 2;
		y = scy / 2;

		switch (selectedCharacter) {
		case CHIKA:
			menu.loadFromFile("sprites\\CHIKAmenu.png");
			textureUp.loadFromFile("sprites\\CHIKAstraight.png");
			textureDown.loadFromFile("sprites\\CHIKAback.png");
			textureLeft.loadFromFile("sprites\\CHIKAleft.png");
			textureRight.loadFromFile("sprites\\CHIKAright.png");

			spriteChika.setTexture(menu);
			spriteChika.setOrigin(menu.getSize().x / 2, menu.getSize().y / 2);
			spriteChika.setScale(2, 2);
			spriteChika.setPosition(x, y);
			break;
		case KIKA:
			menu.loadFromFile("sprites\\KIKAmenu.png");
			textureUp.loadFromFile("sprites\\KIKAstraight.png");
			textureDown.loadFromFile("sprites\\KIKAback.png");
			textureLeft.loadFromFile("sprites\\KIKAleft.png");
			textureRight.loadFromFile("sprites\\KIKAright.png");

			spriteKika.setTexture(menu);
			spriteKika.setOrigin(menu.getSize().x / 2, menu.getSize().y / 2);
			spriteKika.setScale(2, 2);
			spriteKika.setPosition(x, y);
			break;
		}

	}

	~Person() = default;
	
	void SpeedChange(int delta) {
		speed += delta;
	}

	void Move(int i, double dt) {
		switch (selectedCharacter) {
		case CHIKA:
			if (i == 1)//up
			{
				spriteChika.setTexture(textureDown);
				y -= speed * dt;
			}
			else if (i == 2) //down
			{
				spriteChika.setTexture(textureUp);
				y += speed * dt;
			}
			else if (i == 3) //left
			{
				spriteChika.setTexture(textureLeft);
				x -= speed * dt;
			}
			else if (i == 4) //right
			{
				spriteChika.setTexture(textureRight);
				x += speed * dt;
			}
			spriteChika.setPosition(x, y);
			break;
		case KIKA:
			if (i == 1)//up
			{
				spriteKika.setTexture(textureDown);
				y -= speed * dt;
			}
			else if (i == 2) //down
			{
				spriteKika.setTexture(textureUp);
				y += speed * dt;
			}
			else if (i == 3) //left
			{
				spriteKika.setTexture(textureLeft);
				x -= speed * dt;
			}
			else if (i == 4) //right
			{
				spriteKika.setTexture(textureRight);
				x += speed * dt;
			}
			spriteKika.setPosition(x, y);
			break;
		}
	}

	//геттеры и сеттеры
	double X() { return x; }
	double Y() { return y; }

	//не очень нужно
	int DOPS() { return dops; }
	int Hearts() { return hearts; }

	void plusDop() { dops++; }
	void Minusheart() { hearts--; }

	void nullDop() {dops = 0;}
	void nullHearts() { hearts = 3; }


	void typeCharacter(int i) {
		if (i == 1)
			selectedCharacter = CHIKA;
		if (i == 2)
			selectedCharacter = KIKA;
	}

	sf::Sprite Get(){ 
		switch (selectedCharacter) {
		case CHIKA:
			return spriteChika;
			break;
		case KIKA:
			return spriteKika;
			break;
		}
	}
};