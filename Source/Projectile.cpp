#include "Projectile.h"
#pragma once

    Projectile::Projectile(float x, float y, float angle)
    {
        this->radius = 5;
        sprite.setRadius(5);
        sprite.setFillColor(Color(255, 255, 0));
        sprite.setOutlineColor(Color(255, 255, 255));
        life = 1;
        this->setPos(x, y);
        this->setAngle(angle);
    }
    void Projectile::update(float W, float H)
    {
        dx = cos(angle * DegToRad) * 8;
        dy = sin(angle * DegToRad) * 8;
        changePos(dx, dy);
        if (this->x < 0 || this->x > W || this->y > H || this->y < 0)
        {
            life = 0;
        }
    }
    void Projectile::draw(RenderWindow& app)
    {

        sprite.setPosition(x, y);
        sprite.setRotation(angle);
        app.draw(sprite);
    }



