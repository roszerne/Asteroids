#include "SpaceObject.h"
#include "Player.h"
#include "Asteroid.h"
#include "Projectile.h"
using namespace sf;

// parameters
Player player(20);
const int W = 1700;
const int H = 1000;
const int ENEMIES = 20;
const float DegToRad = 0.0175f;
// for movement
bool thrust = false;
float dx, dy;
float angle;
// for text
int score;
Font MyFont;
Text text;
std::string scoreText;
// lists
std::list<Asteroid*> asteroids;
std::list<Projectile*> projectiles;
// sound
SoundBuffer buffer;
SoundBuffer destroyBuffer;
Sound sound;
Sound destroySound;
bool colission(SpaceObject* a, SpaceObject* b) // check collision between 2 SpaceObjects
{

    return (b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y) <
        (a->getRadius() + b->getRadius()) * (a->getRadius() + b->getRadius());
            
}
void respawn() // respawn more asteroids
{
     int toRespawn = 12;
    if (score > 50)
    {
        toRespawn = floor(score / 50)*2 + 12;
    }
    for (int i = 0; i < toRespawn; i++)
    {
        Asteroid* asteroid = new Asteroid(W, H, player);
        asteroids.push_back(asteroid);

    }
}
void reset() // reset the game
{
    score = 0;

    player.setPos(W / 2, H / 2);
    player.setLife(1);

    dx = 0;
    dy = 0;
    angle = 0;

    asteroids.clear();
    projectiles.clear();
    for (int i = 0; i < ENEMIES; i++)
    {
        Asteroid* asteroid = new Asteroid(W, H,player);
        asteroids.push_back(asteroid);

    }
}
int main()
{
    RenderWindow app(sf::VideoMode(W, H), "SFML works!");
    app.setFramerateLimit(60);
    // Score string
    MyFont.loadFromFile("ariblk.ttf");
    text.setString("SCORE:0");
    text.setFont(MyFont);
    text.setCharacterSize(40);
    text.setFillColor(Color(255, 255, 255));
    text.setScale(2.f, 2.f);
    text.move(W / 2-200, 0);
    // start Background
    Texture sBack;
    sBack.loadFromFile("D:\\testsfml\\Project1\\Project1\\startTitle.png");
    Sprite startBackground(sBack);
    // end Background
    Texture eBack;
    eBack.loadFromFile("D:\\testsfml\\Project1\\Project1\\backTitle.png");
    Sprite endBackground(eBack);
    // sound 
    buffer.loadFromFile("fire.wav");
    sound.setBuffer(buffer);
    destroyBuffer.loadFromFile("bang.wav");
    destroySound.setBuffer(destroyBuffer);

    const int MAXSPEED = player.getMaxSpeed();

    reset();
    bool started = false;
    
    while (app.isOpen())
    {
        Event event;
        while(!started) // set starting Background
        {
            while (app.pollEvent(event))
            {
                
                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::Space )
                    {
                        started = true;
                    }
                }
            }
            app.draw(startBackground);
            app.display();
        }
        dx = 0;
        dy = 0;
        
        while (app.pollEvent(event)) // close app or shoot a projectile
        {
            if (event.type == sf::Event::Closed)
                app.close();

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Space && player.getCooldown() == 0)
                {
                    
                    Projectile* projectile = new Projectile(player.x,player.y,player.getAngle()-90);
                    projectiles.push_back(projectile);
                    player.wasShot();
                    sound.play();
                }
            }
        }
        //Player's movement
        if (Keyboard::isKeyPressed(Keyboard::Right)) angle += 3;
        if (Keyboard::isKeyPressed(Keyboard::Left)) angle -= 3;
        if (Keyboard::isKeyPressed(Keyboard::Up))
            thrust = true;
        else
            thrust = false;
        if (thrust)
        {
            dx += sin(angle* DegToRad) * 7.0f;
            dy += -cos(angle* DegToRad) * 7.0f;
        }
        else
        {
            dx *= 0.99;
            dy *= 0.99;
        }
        float speed = sqrt(dx * dx + dy * dy);
        if (speed > MAXSPEED)
        {
            dx *= MAXSPEED / speed;
            dy *= MAXSPEED / speed;
        }
        int x = player.x;
        int y = player.y;
        x += dx;
        y += dy;
        if (x > W) x = 0;
        if (x < 0) x = W;
        if (y < 0) y = H;
        if (y > H) y = 0;
        player.setPos(x, y);
        player.setAngle(angle);

        for (auto a : asteroids) // collsion with asteroids
        {
            for (auto b : projectiles)
            {

                if (colission(a, b))
                {

                    a->setLife(0);
                    b->setLife(0);
                }
            }
            if (colission(a, &player))
            {
                destroySound.play();
                a->setLife(0);
                player.setLife(0);
                break;
            }
        }
        if (player.getLife() == 0)
        {
            app.clear();
            app.draw(endBackground);
            app.draw(text);
            app.display();
            while (player.getLife() == 0)
            {

                while (app.pollEvent(event))
                {

                    if (event.type == Event::KeyPressed)
                    {
                        if (event.key.code == Keyboard::Space)
                        {
                            reset();

                        }
                    }
                }
            }
            continue;
        }
        for (auto i = asteroids.begin(); i != asteroids.end();) // delete dead asteroids
        {
            SpaceObject *a = *i;
            a->update(W,H);
            
            if (a->getLife() == 0)
            {
                destroySound.play();
                if (a->getSize()%2 == 0 )
                {
                   
                    Asteroid* asteroid = new Asteroid(a->x, a->y, a->getSize(),a->getRadius());
                    asteroids.push_back(asteroid);
                   
                }
                score++;
                i = asteroids.erase(i);
                delete a;
            }
            else
                i++;
        }
        
        for (auto i = projectiles.begin(); i != projectiles.end();) // delete dead projectiles
        {
            Projectile* a = *i;
            a->update(W, H);

            if (a->getLife() == 0)
            {

                i = projectiles.erase(i);
                delete a;
            }
            else
                i++;
        }

        player.cool(); // cooldown of weapon
        // set text with score
        scoreText = "SCORE: " + std::to_string(score);
        text.setString(scoreText);

        // drawning
        app.clear();
        player.draw(app);
        for (auto i : asteroids) i->draw(app);
        for (auto i : projectiles) i->draw(app);
        app.draw(text);
        app.display();

        // check if we have enough asteroids
        if (asteroids.size() < 14)
        {
            respawn();
        }
    }

    return 0;
}