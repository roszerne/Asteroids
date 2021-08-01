#pragma once
#include "SpaceObject.h"
class Projectile :
    public SpaceObject
{
public: 
    Projectile(float x, float y, float angle);

    void update(float W, float H);

    void draw(RenderWindow& app);

private:
    CircleShape sprite;
    const float DegToRad = 0.0175f;
};

