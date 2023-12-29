#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include <statenum.h>


class State
{
public:

    State(sf::RenderWindow &pwindow, States StateEnum)
    : window(pwindow)
    , windowMousePos(0, 0)
    , newState(StateEnum) {};

    virtual bool init() = 0;

    virtual void update(float deltaTime) = 0;

    virtual void render() = 0;

    virtual void pollEvent(sf::Event &event) = 0;

    virtual States getState() = 0;

    States nextState() const { return newState; };

protected:


    bool pollWindowing(sf::Event &event);


    void updateAspectRatio();
    void updateMousePosition();

    // Widowing keybinds
    void resizeWindow();

    States newState;

    bool isFullscreen = true, mouseInWindow, windowResized = false;    
    
    sf::Vector2i windowMousePos;
    sf::Vector2f worldMousePos;

    float aspectRatio;

    sf::View view;

    static inline sf::VideoMode videoMode = sf::VideoMode(800, 600);

    sf::RenderWindow &window;
};
#endif