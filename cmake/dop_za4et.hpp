#include <SFML/Graphics.hpp>
//штуки,с которыми ошибки
//#include "OpenGL.hpp"//находитс€ в ext/sfml/include/sfml
using namespace sf;
using namespace std;

class Dop {
	double x;
	double y;
	double time;
	Texture dop;
	Sprite sprite1;
public:
	Dop() = default;
	//не хочет отрисовать доп:(
	void Setup() {
		dop.loadFromFile("sprites\\dop.png");
		if (!dop.loadFromFile("sprites\\dop.png")) {
			cout<<"Error of loading texture for DOP"; //Ќ≈“” ”¬≈ƒќћЋ≈Ќ»я “ј ќ√ќ,¬—≈ «ј√–”∆ј≈“—я!ѕросто не хочет примен€тьс€...
		}

		sprite1.setTexture(dop);
		sprite1.setOrigin(dop.getSize().x / 2, dop.getSize().y/2);
		/*sprite1.setScale(0.25, 0.25);*/
		//sprite1.setScale(2, 2);
		x = rand() % (1580 - 40 + 1) + 40;
		y = rand() % (880 - 40 + 1) + 40;
		sprite1.setPosition(x, y);
	}

	~Dop()=default;

	void Move(double time) {
		y += sin(time)*0.05;
		sprite1.setTexture(dop);
		sprite1.setPosition(x, y);
	}

	Dop operator=(Dop gotdop) {
		x = gotdop.x;
		y = gotdop.y;
		time = gotdop.time;
		sprite1 = gotdop.sprite1;
		return *this;
	}

	//далее все в разработке.ѕытаюсь очищать пам€ть от текстур удаленных объектов
	//удаление текстуры
	/*void ReleaseTexture(Texture& texture) {
		GLuint textureID = texture.getNativeHandle();

		if (textureID != 0) {
			glDeleteTextures(1, &textureID);
		}
	}
	Texture& GetTextureDop() {
		return dop;
	}*/

	//геттеры и сеттеры
	double X() { return x; };
	double Y() { return y; };


	

	Sprite Get()
	{
		return sprite1;
	}
};

class Zat {
	double x = 0;
	double y = 0;
	int type;
	int speed = 140;

	//дл€ зачета
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
		if (type == 1) {//сверху
			x = rand() % (1580 - 20 + 1) + 20;
			sprite.setTexture(textureDown);
			sprite.setOrigin(textureDown.getSize().x / 2, textureDown.getSize().y/2);
			sprite.setScale(2, 2);
			
		}
		if (type == 2) {//снизу
			x = rand() % (1580 - 20 + 1) + 20;
			y = 900;
			sprite.setTexture(textureUp);
			sprite.setOrigin(textureUp.getSize().x / 2, textureUp.getSize().y/2);
			sprite.setScale(2, 2);
		}
		if (type == 3) {//слева
			y = rand() % (880 - 20 + 1) + 20;
			sprite.setTexture(textureRight);
			sprite.setOrigin(textureRight.getSize().x / 2, textureRight.getSize().y/2);
			sprite.setScale(2, 2);
		}
		if (type == 4) {//справа
			y = rand() % (880 - 20 + 1) + 20;
			x = 1600;
			sprite.setTexture(textureLeft);
			sprite.setOrigin(textureLeft.getSize().x / 2, textureLeft.getSize().y/2);
			sprite.setScale(2, 2);
		}
		sprite.setPosition(x, y);
	}

	void Move(int type, double dt) {
		if (type == 1)//сверху вниз
		{
			sprite.setTexture(textureDown);
			y += speed * dt;
		}
		if (type == 2)//снизу вверх
		{
			sprite.setTexture(textureUp);
			y -= speed * dt;
		}
		if (type == 3)//слева направо
		{
			sprite.setTexture(textureRight);
			x += speed * dt;
		}
			
		if (type == 4)//справа налево
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

	//далее все в разработке.ѕытаюсь очищать пам€ть от текстур удаленных объектов
	//Texture& GetTextureZACH() {
	//	if (type == 1) {
	//		return textureDown;
	//	}
	//	else if (type == 2) {
	//		return textureUp;
	//	}
	//	else if (type == 3) {
	//		return textureRight;
	//	}
	//	else if (type == 4) {
	//		return textureLeft;
	//	}
	//}
	////удаление текстуры (в процессе разработки.ѕытаюсь это применить)
	//void ReleaseTexture(Texture& texture) {
	//	GLuint textureID = texture.getNativeHandle();

	//	if (textureID != 0) {
	//		glDeleteTextures(1, &textureID);
	//	}
	//}

	int TYPE() { return type; };
	double X() { return x; };
	double Y() { return y; };
	void setSpeed(int gspeed) { speed = gspeed; };
};