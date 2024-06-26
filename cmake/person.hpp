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
	sf::Texture textureUp1;
	sf::Texture textureDown1;
	sf::Texture textureLeft1;
	sf::Texture textureRight1;

	sf::Texture textureUp2;
	sf::Texture textureDown2;
	sf::Texture textureLeft2;
	sf::Texture textureRight2;

	sf::Texture textureUpS;
	sf::Texture textureDownS;
	sf::Texture textureLeftS;
	sf::Texture textureRightS;

	sf::Sprite spriteChika;
	sf::Sprite spriteKika;
	sf::Sprite spriteMV;

	enum Character { CHIKA, KIKA, MV };
	Character selectedCharacter;
public:
	Person() = default;

	Person(const Person &other) = default;

	void Setup(double scx, double scy) {
		x = scx;
		y = scy;

		switch (selectedCharacter) {
		case CHIKA:
			menu.loadFromFile("sprites\\CHIKAstraightStop.png");
			textureUp1.loadFromFile("sprites\\CHIKAstraight.png");
			textureDown1.loadFromFile("sprites\\CHIKAback.png");
			textureLeft1.loadFromFile("sprites\\CHIKAleft.png");
			textureRight1.loadFromFile("sprites\\CHIKAright.png");

			textureUp2.loadFromFile("sprites\\CHIKAstraight2.png");
			textureDown2.loadFromFile("sprites\\CHIKAback2.png");
			textureLeft2.loadFromFile("sprites\\CHIKAleft2.png");
			textureRight2.loadFromFile("sprites\\CHIKAright2.png");

			textureUpS.loadFromFile("sprites\\CHIKAstraightStop.png");
			textureDownS.loadFromFile("sprites\\CHIKAbackStop.png");
			textureLeftS.loadFromFile("sprites\\CHIKAleftStop.png");
			textureRightS.loadFromFile("sprites\\CHIKArightStop.png");

			spriteChika.setTexture(menu);
			spriteChika.setOrigin(menu.getSize().x / 2, menu.getSize().y / 2);
			spriteChika.setScale(2, 2);
			spriteChika.setPosition(x, y);
			break;
		case KIKA:
			menu.loadFromFile("sprites\\KIKAstraightStop.png");
			textureUp1.loadFromFile("sprites\\KIKAstraight.png");
			textureDown1.loadFromFile("sprites\\KIKAback.png");
			textureLeft1.loadFromFile("sprites\\KIKAleft.png");
			textureRight1.loadFromFile("sprites\\KIKAright.png");

			textureUp2.loadFromFile("sprites\\KIKAstraight2.png");
			textureDown2.loadFromFile("sprites\\KIKAback2.png");
			textureLeft2.loadFromFile("sprites\\KIKAleft2.png");
			textureRight2.loadFromFile("sprites\\KIKAright2.png");

			textureUpS.loadFromFile("sprites\\KIKAstraightStop.png");
			textureDownS.loadFromFile("sprites\\KIKAbackStop.png");
			textureLeftS.loadFromFile("sprites\\KIKAleftStop.png");
			textureRightS.loadFromFile("sprites\\KIKArightStop.png");

			spriteKika.setTexture(menu);
			spriteKika.setOrigin(menu.getSize().x / 2, menu.getSize().y / 2);
			spriteKika.setScale(2, 2);
			spriteKika.setPosition(x, y);
			break;
		case MV:
			textureUp1.loadFromFile("sprites\\MVstraight.png");
			textureDown1.loadFromFile("sprites\\MVback.png");
			textureLeft1.loadFromFile("sprites\\MVleft.png");
			textureRight1.loadFromFile("sprites\\MVright.png");

			textureUp2.loadFromFile("sprites\\MVstraight2.png");
			textureDown2.loadFromFile("sprites\\MVback2.png");
			textureLeft2.loadFromFile("sprites\\MVleft2.png");
			textureRight2.loadFromFile("sprites\\MVright2.png");

			textureUpS.loadFromFile("sprites\\MVstraightStop.png");
			textureDownS.loadFromFile("sprites\\MVbackStop.png");
			textureLeftS.loadFromFile("sprites\\MVleftStop.png");
			textureRightS.loadFromFile("sprites\\MVrightStop.png");

			spriteMV.setTexture(textureUpS);
			spriteMV.setOrigin(textureUpS.getSize().x / 2, textureUpS.getSize().y / 2);
			spriteMV.setScale(2.5, 2.5);
			spriteMV.setPosition(x, y);
			break;
		}

	}

	~Person() = default;
	
	void SpeedChange(int delta) {
		speed += delta;
	}

	void Move(int i, double dt, bool timer) {
		switch (selectedCharacter) {
		case CHIKA:
			if (i == 1 && timer)//up
			{
				spriteChika.setTexture(textureDown1);
				y -= speed * dt;
			}
			else if (i == 1 && !timer) {
				spriteChika.setTexture(textureDown2);
				y -= speed * dt;
			}
			else if (i == 2 && timer) //down
			{
				spriteChika.setTexture(textureUp1);
				y += speed * dt;
			}
			else if (i == 2 && !timer) //down
			{
				spriteChika.setTexture(textureUp2);
				y += speed * dt;
			}
			else if (i == 3 && timer) //left
			{
				spriteChika.setTexture(textureLeft1);
				x -= speed * dt;
			}
			else if (i == 3 && !timer) //left
			{
				spriteChika.setTexture(textureLeft2);
				x -= speed * dt;
			}
			else if (i == 4 && timer) //right
			{
				spriteChika.setTexture(textureRight1);
				x += speed * dt;
			}
			else if (i == 4 && !timer) //right
			{
				spriteChika.setTexture(textureRight2);
				x += speed * dt;
			}
			spriteChika.setPosition(x, y);
			break;
		case KIKA:
			if (i == 1 && timer)//up
			{
				spriteKika.setTexture(textureDown1);
				y -= speed * dt;
			}
			else if (i == 1 && !timer) {
				spriteKika.setTexture(textureDown2);
				y -= speed * dt;
			}
			else if (i == 2 && timer) //down
			{
				spriteKika.setTexture(textureUp1);
				y += speed * dt;
			}
			else if (i == 2 && !timer) //down
			{
				spriteKika.setTexture(textureUp2);
				y += speed * dt;
			}
			else if (i == 3 && timer) //left
			{
				spriteKika.setTexture(textureLeft1);
				x -= speed * dt;
			}
			else if (i == 3 && !timer) //left
			{
				spriteKika.setTexture(textureLeft2);
				x -= speed * dt;
			}
			else if (i == 4 && timer) //right
			{
				spriteKika.setTexture(textureRight1);
				x += speed * dt;
			}
			else if (i == 4 && !timer) //right
			{
				spriteKika.setTexture(textureRight2);
				x += speed * dt;
			}
			spriteKika.setPosition(x, y);
			break;
		case MV:
			if (i == 1 && timer)//up
			{
				spriteMV.setTexture(textureDown1);
				y -= speed * dt;
			}
			else if (i == 1 && !timer) {
				spriteMV.setTexture(textureDown2);
				y -= speed * dt;
			}
			else if (i == 2 && timer) //down
			{
				spriteMV.setTexture(textureUp1);
				y += speed * dt;
			}
			else if (i == 2 && !timer) //down
			{
				spriteMV.setTexture(textureUp2);
				y += speed * dt;
			}
			else if (i == 3 && timer) //left
			{
				spriteMV.setTexture(textureLeft1);
				x -= speed * dt;
			}
			else if (i == 3 && !timer) //left
			{
				spriteMV.setTexture(textureLeft2);
				x -= speed * dt;
			}
			else if (i == 4 && timer) //right
			{
				spriteMV.setTexture(textureRight1);
				x += speed * dt;
			}
			else if (i == 4 && !timer) //right
			{
				spriteMV.setTexture(textureRight2);
				x += speed * dt;
			}
			spriteMV.setPosition(x, y);
			break;
		}
	}

	void Stop(int type) {
		switch (selectedCharacter) {
		case CHIKA:
			if (type == 1) spriteChika.setTexture(textureDownS);
			if (type == 2) spriteChika.setTexture(textureUpS);
			if (type == 3) spriteChika.setTexture(textureLeftS);
			if (type == 4) spriteChika.setTexture(textureRightS);
		case KIKA:
			if (type == 1) spriteKika.setTexture(textureDownS);
			if (type == 2) spriteKika.setTexture(textureUpS);
			if (type == 3) spriteKika.setTexture(textureLeftS);
			if (type == 4) spriteKika.setTexture(textureRightS);
		case MV:
			if (type == 1) spriteMV.setTexture(textureDownS);
			if (type == 2) spriteMV.setTexture(textureUpS);
			if (type == 3) spriteMV.setTexture(textureLeftS);
			if (type == 4) spriteMV.setTexture(textureRightS);
		}
	}

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

	int typeCharacter() {
		switch (selectedCharacter) {
		case CHIKA:
			return 1;
			break;
		case KIKA:
			return 2;
			break;
		case MV:
			return 3;
			break;
		}
	}
	void typeCharacter(int i) {
		if (i == 1)
			selectedCharacter = CHIKA;
		if (i == 2)
			selectedCharacter = KIKA;
		if (i == 3)
			selectedCharacter = MV;
	}

	sf::Sprite Get(){ 
		switch (selectedCharacter) {
		case CHIKA:
			return spriteChika;
			break;
		case KIKA:
			return spriteKika;
			break;
		case MV:
			return spriteMV;
			break;
		}
	}
};