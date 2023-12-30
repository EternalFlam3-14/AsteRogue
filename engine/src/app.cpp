#include <iostream>
#include <app.h>
#include <utility.hpp>


App::App() : window(sf::VideoMode::getDesktopMode(), "AsteRogue", sf::Style::Fullscreen)
{
    // Set FPS
    window.setFramerateLimit(60);
    // This is V-Sync
    window.setVerticalSyncEnabled(true);
    // Instead of taking repeat keystrokes, we set bools in accordance with input
    window.setKeyRepeatEnabled(false);
}

bool App::setIcon()
{
    sf::Image icon;
    if (!icon.loadFromFile("data/textures/ships/ship.png"))
    {
        return false;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    return true;
}


void App::Run()
{
    StateManager manager(window);
    if (!manager.changeState<Title>())
    {
        window.close();
    }


    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        manager.checkState();

        sf::Event event;
        while (window.pollEvent(event))
        {
            // Overarching application keybinds
            pollEvent(manager);

            // Pass the event to the state manager
            manager.handleInput(event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }


        // Update and draw the current state
        manager.update(deltaTime);
        window.clear(sf::Color(2, 2, 25));
        manager.render();
        window.display();
    }
}

void App::pollEvent(StateManager &manager)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
    {
        switch (manager.getCurrentState())
        {
            case States::TitleState :
            {
                manager.changeState<Game>();
            }
            case States::GameState :
            {
                manager.changeState<Title>();
            }
        }
    }
}

