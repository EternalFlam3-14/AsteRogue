
#include <iostream>

#include "game.h"


bool Game::init()
{
    if (!initPlayer())
    {
        return false;
    }
    if (!initGauge())
    {
        return false;
    }
    if (!initBackground())
    {
        return false;
    }
    return true;
}

bool Game::initPlayer()
{
    if (!playertexture.loadFromFile("data/textures/ships/ship.png"))
    {
        return false;
    }

    player = std::make_unique<Player> (playertexture);
    if (!player)
    {
        return false;
    }

    return true;
}

bool Game::initGauge()
{
    if (!gaugefont.loadFromFile("data/fonts/KraftMono.otf"))
    {
        return false;
    }
    gauge = std::make_unique<Gauge> (gaugefont);
    if (!gauge)
    {
        return false;
    }

    gauge->setPosition(sf::Vector2f(window.getPosition() - sf::Vector2i(window.getSize() / 2u)));
    gauge->setNum(player->getBoostlength());
    return true;
}

bool Game::initBackground()
{
    if (!backgroundtexture.loadFromFile("data/textures/background.jpg"))
    {
        return false;
    }
    backgroundtexture.setRepeated(true);

    background.init(backgroundtexture, window);
    return true;

}

void Game::update(float deltaTime)
{
    player->update(deltaTime);

    wrapPlayer();

    updateView();

    gauge->setNum(player->getBoostlength());
    gauge->setPosition(player->getPosition() - sf::Vector2f(window.getSize() / 2u));
}

void Game::wrapPlayer()
{
    auto characterPosition = player->getPosition();

    if (characterPosition.x > background.getBounds().width)
    {// right
        auto xDistance = std::abs(characterPosition.x - background.getBounds().width);
        auto newx = background.getBounds().left + xDistance;
        player->setPosition(newx, characterPosition.y);
    }
    if (characterPosition.x < background.getBounds().left)
    {// left
        auto xDistance = std::abs(background.getBounds().left - characterPosition.x);
        auto newx = background.getBounds().width + xDistance;
        player->setPosition(newx, characterPosition.y);
    }
    if (characterPosition.y > background.getBounds().height)
    {// bottom
        auto yDistance = std::abs(characterPosition.y - background.getBounds().height);
        auto newy = background.getBounds().top - yDistance;
        player->setPosition(characterPosition.x, newy);
    }
    if (characterPosition.y < background.getBounds().top)
    {// top
        auto yDistance = std::abs(background.getBounds().top - characterPosition.y);
        auto newy = background.getBounds().height + yDistance;
        player->setPosition(characterPosition.x, newy);
    }

}

void Game::render()
{
    renderBackground();

    window.draw(*player);
    window.draw(*gauge);
}

void Game::renderBackground()
{
    background.draw(window);
}

void Game::pollEvent(sf::Event &event)
{

    sf::Keyboard::isKeyPressed(sf::Keyboard::W) ?
        player->startForward() : player->stopForward();
    
    sf::Keyboard::isKeyPressed(sf::Keyboard::A) ?
        player->startRotation(false) : player->stopRotation(false);
    
    sf::Keyboard::isKeyPressed(sf::Keyboard::D) ?
        player->startRotation(true) : player->stopRotation(true);

    sf::Keyboard::isKeyPressed(sf::Keyboard::S) ?
        player->startBackward() : player->stopBackward();

    sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
    sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) ?
        player->startBoost() : player->stopBoost();
    updateMousePosition();
}

void Game::updateView()
{
    sf::Vector2f playerPosition = player->getPosition();

    // Set the view's center to the player's position
    sf::View view = window.getView();
    view.setCenter(playerPosition);

    // Apply the updated view
    window.setView(view);
}
