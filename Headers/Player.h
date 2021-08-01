#pragma once
#include "SpaceObject.h"
using namespace sf;
class Player :
    public SpaceObject
{
public:

    Player(float size);

    void draw(RenderWindow& app);

    float getMaxSpeed() const;

    float getCooldown() const;

    void wasShot();

    void cool();

private:
    CircleShape player;
    const int MAX_SPEED = 15;
    float COOLDOWN_TIME = 15;
    float cooldown;
};

