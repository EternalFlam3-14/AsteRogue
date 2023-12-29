#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <memory>
#include <vector>

#include <SFML/graphics.hpp>

class Background
{
public:


    bool init(sf::Texture &backgroundtexture, sf::RenderWindow &window);


    void draw(sf::RenderWindow &window);


    sf::FloatRect getBounds() const { return mapBounds; };

private:


    std::vector<sf::Sprite> backgrounds;
    sf::FloatRect mapBounds;

    const float BACKGROUND_SCALE = 2.0f;



};

#endif