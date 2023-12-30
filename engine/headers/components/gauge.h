#ifndef BOOST_GAGUE_H
#define BOOST_GAGUE_H

#include <SFML/Graphics.hpp>



class Gauge : public sf::Drawable, public sf::Transformable
{
public:

    Gauge(sf::Font &font);

    void setNum(float boostnum);


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

    sf::Text text;


};
#endif