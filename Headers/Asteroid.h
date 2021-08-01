#pragma once
#include "Player.h"

class Asteroid :
    public SpaceObject
{
public:

    Asteroid(float W, float H, Player& player);
    Asteroid(float x, float y,int size,float radius);

    void update(float W, float H);

    void draw(RenderWindow& app);
    bool colission(SpaceObject* a, SpaceObject* b);

private:
    CircleShape sprite;
    std::vector<std::pair<float, float>> shapes;
    const int POINTS = 12;
    const int RADIUS = 60;
};


