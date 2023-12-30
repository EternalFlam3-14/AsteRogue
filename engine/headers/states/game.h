#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include <background.h>
#include <state.h>
#include <player.h>
#include <gauge.h>

class Game : public State
{
public:

    Game(sf::RenderWindow &pwindow) : State(pwindow, getState()) {};

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

    States getState() override { return States::GameState; };
    

private:

    /// @brief Initializes the ```player``` including ```playertexture```
    /// @return True if loading successful
    bool initPlayer();

    bool initGauge();

    /// @brief Initializes the ```background``` including ```backgroundtexture```
    /// @return True if loading successful
    bool initBackground();

    void updateView();

    void wrapPlayer();

    void renderBackground();

    // Game Objects
    // Sprites are for textures
    // Shapes are another option
    sf::Texture playertexture, backgroundtexture;
    Background background;
    sf::Font gaugefont;

    const float BACKGROUND_SCALE = 2.0f;

    std::unique_ptr<Player> player;
    std::unique_ptr<Gauge> gauge;

    bool Forward = false, Backward = false, Left = false, Right = false;

};
#endif