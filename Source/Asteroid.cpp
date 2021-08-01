#include "Asteroid.h"
#include "math.h"
#pragma once

    Asteroid::Asteroid(float W, float H, Player& player)
    {

        this->radius = RADIUS;
        this->size = POINTS;
        sprite.setRadius(RADIUS);
        sprite.setFillColor(Color(0, 0, 0));
        sprite.setOutlineColor(Color(255, 255, 255));
        sprite.setOutlineThickness(5);
        sprite.setPointCount(POINTS);

         do 
         {
        this->x = 0 + ((float)rand()) / (float)RAND_MAX * (W - 0);
        this->y = 0 + ((float)rand()) / (float)RAND_MAX * (H - 0);
           } while (colission(this,&player));

        this->dx = rand() % 6 - 3;
        this->dy = rand() % 6 - 3;
        this->angle = 0;
        this->life = 1;
    }
    Asteroid::Asteroid(float x, float y, int size, float radius)
    {
        this->radius = round(radius *2/3 );
        this->size = round(size *2/3);
        sprite.setRadius(this->radius);
        sprite.setFillColor(Color(0, 0, 0));
        sprite.setOutlineColor(Color(255, 255, 255));
        sprite.setOutlineThickness(5);
        sprite.setPointCount(this->size);

        this->x = x;
        this->y = y;

        this->dx = rand() % 6 - 3;
        this->dy = rand() % 6 - 3;
        this->angle = 0;
        this->life = 1;
    }
    void Asteroid::update(float W, float H)
    {
        x += dx;
        y += dy;
        if (x > W) x = 0;
        if (x < 0) x = W;
        if (y > H) y = 0;
        if (y < 0) y = H;

    }
    void  Asteroid::draw(RenderWindow& app)
    {
        sprite.setPosition(x, y);
        sprite.setRotation(angle);
        app.draw(sprite);
    }
    bool Asteroid::colission(SpaceObject* a, SpaceObject* b)
    {
        return (b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y) <
            (a->getRadius() + b->getRadius()+150) * (a->getRadius() + b->getRadius()+150);

    }


