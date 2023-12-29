#include <string>

#include "gauge.h"

Gauge::Gauge(sf::Font &font)
{
    text.setFont(font);
    text.setCharacterSize(24);
    
    text.setFillColor(sf::Color::White);
}

void Gauge::setNum(float Float)
{
    auto booststring = std::to_string(Float);
    for (int i = 0; i < 5; i++)
    {
        booststring.pop_back();
    }
    text.setString(booststring);
}

void Gauge::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform(); // Apply the player's transformations
    target.draw(text, states); // Draw the player sprite
}