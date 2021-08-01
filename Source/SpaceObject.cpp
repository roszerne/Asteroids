#include "SpaceObject.h"
using namespace sf;


    SpaceObject::SpaceObject()
	{
		this->x = 0;
		this->y = 0;
		this->dx = 0;
		this->dy = 0;
		this->angle = 0;
		this->size = 0;
		this->radius = 0;
		this->life = 0;

	}
	Sprite  SpaceObject::getSprite() const
	{
		return sprite;
	}
	void  SpaceObject::setPos(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	void  SpaceObject::setAngle(float angle)
	{
		this->angle = angle;
	}
	void  SpaceObject::setLife(int life)
	{
		this->life = life;
	}
	void  SpaceObject::changeAngle(float ang)
	{
		this->angle += ang;
	}
	void  SpaceObject::changePos(float x, float y)
	{
		this->x += x;
		this->y += y;
	}
	float  SpaceObject::getAngle() const
	{
		return this->angle;
	}
	int  SpaceObject::getSize() const
	{
		return this->size;
	}
	float  SpaceObject::getRadius() const
	{
		return this->radius;
	}


