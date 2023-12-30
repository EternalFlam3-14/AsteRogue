
#include <iostream>

#include <title.h>

bool Title::init()
{
    if (!initLoading())
    {
        return false;
    }
    initSprite();
    initText();
    initButton();
    return true;

}

bool Title::initLoading()
{
    if (!splashtexture.loadFromFile("data/textures/Splash.png")
    ||  !font.loadFromFile("data/fonts/KraftMono.otf"))
    {
        return false;
    }
    return true;
}

void Title::initSprite()
{
    splashsprite.setTexture(splashtexture);
    splashsprite.setOrigin(splashsprite.getLocalBounds().width / 2.f, splashsprite.getLocalBounds().height / 2.f);
    splashsprite.setPosition(window.getView().getCenter());
}

void Title::initText()
{
    splashtext.setFont(font);
    splashtext.setCharacterSize(40);
    splashtext.setFillColor(sf::Color::Blue);
    splashtext.setString("AsteRogue");

    sf::FloatRect bounds = splashtext.getLocalBounds();

    splashtext.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

    splashtext.setPosition(window.getView().getCenter().x, (window.getView().getCenter().y - (view.getSize().y / 2.f)));
    


    buttontext.setFont(font);
    buttontext.setCharacterSize(80);
    buttontext.setFillColor(sf::Color::Green);
    buttontext.setString("Play");

    bounds = buttontext.getLocalBounds();

    buttontext.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

}

void Title::initButton()
{
    button.setSize(sf::Vector2f(buttontext.getLocalBounds().getSize().x + 15.f, buttontext.getLocalBounds().getSize().y + 15.f));
    button.setFillColor(sf::Color::Black);
    button.setOrigin(button.getLocalBounds().width / 2.f, button.getLocalBounds().height / 2.f);
    button.setPosition(window.getView().getCenter().x, (window.getView().getCenter().y + (view.getSize().y / 4.f)));

    buttontext.setPosition(button.getPosition());
}

void Title::update(float deltaTime)
{
    if (windowMousePos.x >= button.getPosition().x - button.getSize().x / 2 &&
        windowMousePos.x <= button.getPosition().x + button.getSize().x / 2 &&
        windowMousePos.y >= button.getPosition().y - button.getSize().y / 2 &&
        windowMousePos.y <= button.getPosition().y + button.getSize().y / 2)
    {
        if (click)
        {
            newState = States::GameState;
        }
    }
}

void Title::render()
{
    window.draw(splashsprite);
    window.draw(splashtext);
    window.draw(button);
    window.draw(buttontext);
}


void Title::pollEvent(sf::Event &event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        event.type = sf::Event::Closed;
    }

    click = sf::Mouse::isButtonPressed(sf::Mouse::Left) ? true : false;


    updateMousePosition();
}
