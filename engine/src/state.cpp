#include <iostream>
#include "state.h"

bool State::pollWindowing(sf::Event &event)
{
    if (!(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F11))
    {
        return false;
    }
    resizeWindow();
    return true;
}

void State::updateAspectRatio()
{
    float width = window.getSize().x;
    float height = window.getSize().y;
    aspectRatio = width / height;
    view.setSize(width, height);
    view.setCenter(sf::Vector2f(0.f ,0.f));
    window.setView(view);
}

void State::updateMousePosition()
{
    auto mousePixelPos = sf::Mouse::getPosition(window);

    if (mousePixelPos.x <= window.getSize().x && mousePixelPos.y <= window.getSize().y
    && mousePixelPos.x >= 0 && mousePixelPos.y >= 0)
    {
        windowMousePos = sf::Mouse::getPosition(window);
        worldMousePos = window.mapPixelToCoords(windowMousePos, view);
    }
}

void State::resizeWindow()
{
    switch (isFullscreen)
    {
        case true:
        {
            window.create(videoMode, "Cyberduction");
            isFullscreen = false;
            break;
        }
        default:
        {
            window.create(sf::VideoMode::getDesktopMode(), "Cyberduction", sf::Style::Fullscreen);
            isFullscreen = true;
        }
    }
    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(sf::Vector2f(0.f ,0.f));
    window.setView(view);
}
