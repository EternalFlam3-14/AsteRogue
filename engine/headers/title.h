#ifndef TITLE_STATE_H
#define TITLE_STATE_H

#include "state.h"

class Title : public State
{
public:

    Title(sf::RenderWindow &pwindow) : State(pwindow, getState()) {};

    /// @brief Initialization of the game
    /// @return True if initializations completed with no errors
    bool init() override;

    /// @brief To run every tick, calls all ```update()``` functions, such as ```updateView()```
    /// and ```player.update()```
    void update(float deltaTime) override;

    /// @brief To run every tick after the ```update()``` function. Runs all ```render_()``` functions, such as ```renderBackground()```
    void render() override;

    /// @brief Polls window events including but not limited to mouse events, resizing, and keyboard inputs
    void pollEvent(sf::Event &event) override;

    States getState() override {return States::TitleState; };

private:

    bool initLoading();

    void initSprite();

    void initText();

    void initButton();



    bool click = false;


    sf::Texture splashtexture;
    sf::Font font;

    sf::Sprite splashsprite;
    sf::Text splashtext, buttontext;

    sf::RectangleShape button;



};
#endif