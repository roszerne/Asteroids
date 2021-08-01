#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace sf;

#pragma once
class SpaceObject
{
public:
		SpaceObject();
		Sprite getSprite() const;
		virtual void draw(RenderWindow& app)
		{
			sprite.setPosition(x, y);
			sprite.setRotation(angle);
			app.draw(sprite);
		}
		void setPos(float x, float y);

		void setAngle(float angle);

		void setLife(int life);

		void changeAngle(float ang);

		void changePos(float x, float y);

		float getAngle() const;

		int getSize() const;

		float getRadius() const;

	virtual void update(float W, float H) {};
	virtual int getLife() const { return this->life; };

	float x;
	float y;
protected:
	Texture texture;
	Sprite sprite;
	int size;
	float radius;
	int life;
	float angle;
	float dx;
	float dy;
	
};

