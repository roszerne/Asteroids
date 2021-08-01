#include "Player.h"
using namespace sf;

    Player::Player(float size)
    {
        this->size = size;
        this->radius = size;
        this->cooldown = 0;
        player.setRadius(size);
        player.setPointCount(3);
        player.setFillColor(Color(0, 0, 0));
        player.setOutlineColor(Color(255, 255, 255));
        player.setOutlineThickness(10);
    }
    void  Player::draw(RenderWindow& app)
    {
        player.setPosition(x, y);
        player.setRotation(angle);
        app.draw(player);
    }
    float  Player::getMaxSpeed() const
    {
        return this->MAX_SPEED;
    }

    float Player::getCooldown() const
    {
        return this->cooldown;
    }

    void Player::wasShot()
    {
        this->cooldown = COOLDOWN_TIME;
    }

    void Player::cool()
    {
        if (this->cooldown > 0)
            this->cooldown--;
    }
