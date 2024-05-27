#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Person{
protected:
	double x;
	double y;
	double speed = 200;
	
	int hearts = 3;
	int dops = 0;
	int way = 1;

	//спрайты
	sf::Texture menu;
	sf::Texture textureUp;
	sf::Texture textureDown;
	sf::Texture textureLeft;
	sf::Texture textureRight;
	sf::Sprite sprite;
public:
	Person() = default;

	Person(const Person &other) = default;

	virtual void Setup(double scx, double scy) = 0;
	/*{
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
		case MV:
			textureUp.loadFromFile("sprites\\MVstraight.png");
			textureDown.loadFromFile("sprites\\MVback.png");
			textureLeft.loadFromFile("sprites\\MVleft.png");
			textureRight.loadFromFile("sprites\\MVright.png");

			spriteMV.setTexture(textureUp);
			spriteMV.setOrigin(textureUp.getSize().x / 2, textureUp.getSize().y / 2);
			spriteMV.setScale(2.5, 2.5);
			spriteMV.setPosition(x, y);
			break;
		}

	}*/

	~Person() = default;
	
	void SpeedChange(int delta) {
		speed += delta;
	}

	virtual void Move(int i, double dt, float timer) = 0;
	//{
	//	switch (selectedCharacter) {
	//	case CHIKA:
	//		if (i == 1)//up
	//		{
	//			spriteChika.setTexture(textureDown);
	//			y -= speed * dt;
	//		}
	//		else if (i == 2) //down
	//		{
	//			spriteChika.setTexture(textureUp);
	//			y += speed * dt;
	//		}
	//		else if (i == 3) //left
	//		{
	//			spriteChika.setTexture(textureLeft);
	//			x -= speed * dt;
	//		}
	//		else if (i == 4) //right
	//		{
	//			spriteChika.setTexture(textureRight);
	//			x += speed * dt;
	//		}
	//		spriteChika.setPosition(x, y);
	//		break;
	//	case KIKA:
	//		if (i == 1)//up
	//		{
	//			spriteKika.setTexture(textureDown);
	//			y -= speed * dt;
	//		}
	//		else if (i == 2) //down
	//		{
	//			spriteKika.setTexture(textureUp);
	//			y += speed * dt;
	//		}
	//		else if (i == 3) //left
	//		{
	//			spriteKika.setTexture(textureLeft);
	//			x -= speed * dt;
	//		}
	//		else if (i == 4) //right
	//		{
	//			spriteKika.setTexture(textureRight);
	//			x += speed * dt;
	//		}
	//		spriteKika.setPosition(x, y);
	//		break;
	//	case MV:
	//		if (i == 1)//up
	//		{
	//			spriteMV.setTexture(textureDown);
	//			y -= speed * dt;
	//		}
	//		else if (i == 2) //down
	//		{
	//			spriteMV.setTexture(textureUp);
	//			y += speed * dt;
	//		}
	//		else if (i == 3) //left
	//		{
	//			spriteMV.setTexture(textureLeft);
	//			x -= speed * dt;
	//		}
	//		else if (i == 4) //right
	//		{
	//			spriteMV.setTexture(textureRight);
	//			x += speed * dt;
	//		}
	//		spriteMV.setPosition(x, y);
	//		break;
	//	}
	//}

	//геттеры и сеттеры
	double X() { return x; }
	double Y() { return y; }

	int DOPS() { return dops; }
	int Hearts() { return hearts; }

	void plusDop() { dops++; }
	void Minusheart() { hearts--; }

	void nullDop() {dops = 0;}
	void nullHearts() { hearts = 3; }
	void defSpeed() { speed = 200; }

	sf::Sprite Get(){ 
		return sprite;
	}
};

class Chika : public Person {
public:
	void Setup(double scx, double scy) override {
		x = scx;
		y = scy;

		menu.loadFromFile("sprites\\CHIKAmenu.png");
		textureUp.loadFromFile("sprites\\CHIKAstraight.png");
		textureDown.loadFromFile("sprites\\CHIKAback.png");
		textureLeft.loadFromFile("sprites\\CHIKAleft.png");
		textureRight.loadFromFile("sprites\\CHIKAright.png");

		sprite.setTexture(menu);
		sprite.setOrigin(menu.getSize().x / 2, menu.getSize().y / 2);
		sprite.setScale(2, 2);
		sprite.setPosition(x, y);
	}

	void Move(int i, double dt, float timer) override{
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
};

class Kika : public Person {
public:
	void Setup(double scx, double scy) override {
		x = scx;
		y = scy;
		menu.loadFromFile("sprites\\KIKAmenu.png");
		textureUp.loadFromFile("sprites\\KIKAstraight.png");
		textureDown.loadFromFile("sprites\\KIKAback.png");
		textureLeft.loadFromFile("sprites\\KIKAleft.png");
		textureRight.loadFromFile("sprites\\KIKAright.png");

		sprite.setTexture(menu);
		sprite.setOrigin(menu.getSize().x / 2, menu.getSize().y / 2);
		sprite.setScale(2, 2);
		sprite.setPosition(x, y);
	}

	void Move(int i, double dt, float timer) override {
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
};

class MV : public Person {
public:
	void Setup(double scx, double scy) override {
		x = scx;
		y = scy;
		menu.loadFromFile("sprites\\MVmenu.png");
		textureUp.loadFromFile("sprites\\MVstraight.png");
		textureDown.loadFromFile("sprites\\MVback.png");
		textureLeft.loadFromFile("sprites\\MVleft.png");
		textureRight.loadFromFile("sprites\\MVright.png");

		sprite.setTexture(menu);
		sprite.setOrigin(menu.getSize().x / 2, menu.getSize().y / 2);
		sprite.setScale(2, 2);
		sprite.setPosition(x, y);
	}

	void Move(int i, double dt, float timer) override {
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
};