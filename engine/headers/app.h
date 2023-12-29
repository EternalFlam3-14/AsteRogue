#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>

#include "statemanager.h"


class App
{
public:

    App();

    bool setIcon();

    void Run();


private:

    void pollEvent(StateManager &manager);

    sf::RenderWindow window;

    sf::Clock clock;
    float deltaTime;

};
#endif