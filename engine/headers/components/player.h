#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable, public sf::Transformable
{
public:
    Player(sf::Texture &ptexture);

    void update(float dt);

    const float getBoostlength() const { return boostlength; }

    // Rotation bool handling
    void startRotation(bool clockwise);
    void stopRotation(bool clockwise);

    // Forward bool handling
    void startForward();
    void stopForward();

    // Backward bool handling
    void startBackward();
    void stopBackward();

    // Boost bool handling
    void startBoost();
    void stopBoost();
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

    sf::Texture texture;
    sf::Sprite sprite;

    float rotationSpeed = 100.0f;               // Adjust this value to control rotation speed
    float acceleration = 250.f;                 // Adjust this value to control movement speed

    float boostFactor = 2.f;                    // Adjust this value to control boost speed
    float boostDuration = 3.f;                  // Adjust this value to control boost duration
    float boostlength = 0.f;                    // Do not adjust, used for measurement

    sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);
    bool isBoosting = false, Left = false, Right = false, Forward = false, Backward = false;

    const float DEG_TO_RAD = 3.14159265359 / 180.0f;
    const float MAX_BASE_SPEED = 500000.f;
};

#endif // PLAYER_H