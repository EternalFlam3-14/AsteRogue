#include <iostream>
#include <cmath>
#include <string>

#include <player.h>

Player::Player(sf::Texture &ptexture) : texture(std::move(ptexture))
{
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    sprite.rotate(90);
    rotate(-90);
    
    setPosition(0, 0);
}

void Player::update(float dt)
{
    float rotationAmount = rotationSpeed * dt;
    if (Left)
    {
        rotate(-rotationAmount); // Rotate counterclockwise
    }
    if (Right)
    {
        rotate(rotationAmount); // Rotate clockwise
    }


    if (Backward)
    {
        velocity.x -= acceleration * std::cos(getRotation() * DEG_TO_RAD) * dt;
        velocity.y -= acceleration * std::sin(getRotation() * DEG_TO_RAD) * dt;
    }


    if (Forward)
    {
        if (isBoosting && boostlength > 0)
        {
            velocity.x += (acceleration * boostFactor) * std::cos(getRotation() * DEG_TO_RAD) * dt;
            velocity.y += (acceleration * boostFactor) * std::sin(getRotation() * DEG_TO_RAD) * dt;
            auto nextlength = boostlength -= dt;
            if (nextlength < 0)
            {
                boostlength = 0;
            }
        }
        else
        {
            velocity.x += acceleration * std::cos(getRotation() * DEG_TO_RAD) * dt;
            velocity.y += acceleration * std::sin(getRotation() * DEG_TO_RAD) * dt;
        }

        float maxSpeed = MAX_BASE_SPEED;
        float currentSpeed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        if (currentSpeed > maxSpeed)
        {
            // Normalize the velocity vector and multiply by the maximum speed
            velocity = velocity / currentSpeed * maxSpeed;
        }
    }


    if (!isBoosting)
    {
        // Regen boost when forward is not pressed
        auto newboost = boostlength + dt;
        if (newboost <= boostDuration)
        {
            boostlength = newboost;
        }
        else if (newboost > boostDuration)
        {
            boostlength = boostDuration;
        }
    }


    // Decelerate when neither forward nor backward is pressed
    if (!Forward && !Backward)
    {
        // Decelerate when neither forward nor backward is pressed
        float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        if (speed > 0.0f)
        {
            // Normalize the velocity vector and multiply by the deceleration
            velocity = velocity / speed * (speed - acceleration * dt);

            // Clamp velocity to zero to prevent slow backward drift
            if (speed < 0.01f)
            {
                velocity = sf::Vector2f(0.0f, 0.0f);
            }
        }
    }



    // Use a factor to adjust the effect of the accumulated velocity
    float velocityFactor = 0.7f; // You can adjust this value

    // Update the player's position with accumulated velocity
    move(velocity * velocityFactor * dt);

}

void Player::startRotation(bool clockwise)
{
    if (!clockwise)
    {
        if (!Left)
        {
            Left = true;
        }
    }
    else
    {
        if (!Right)
        {
            Right = true;
        }
    }
}

void Player::stopRotation(bool clockwise)
{
    if (!clockwise)
    {
        if (Left)
        {
            Left = false;
        }
    }
    else
    {
        if (Right)
        {
            Right = false;
        }
    }
}

void Player::startForward()
{
    if (!Forward)
    {
        Forward = true;
    }
}

void Player::stopForward()
{
    if (Forward)
    {
        Forward = false;
    }
}

void Player::startBackward()
{
    if (!Backward)
    {
        Backward = true;
    }
}

void Player::stopBackward()
{
    if (Backward)
    {
        Backward = false;
    }
}

void Player::startBoost()
{
    if (!isBoosting && boostlength > 0)
    {
        isBoosting = true;
    }
}

void Player::stopBoost()
{
    if (isBoosting)
    {
        isBoosting = false;
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform(); // Apply the player's transformations
    target.draw(sprite, states); // Draw the player sprite

}