#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <memory>
#include <map>

#include <states.h>

class StateManager
{
public:
    StateManager(sf::RenderWindow &pwindow) : currentState(nullptr), window(pwindow) {};

    template <typename T>
    bool changeState()
    {
        std::unique_ptr<T> state = std::make_unique<T>(window);
        currentState = std::move(state);
        return initState();
    };

    bool initState()
    {
        if (currentState)
        {
            return currentState->init();
        }
        else return false;
    };

    void handleInput(sf::Event &event)
    {
        if (currentState)
        {
            currentState->pollEvent(event);
        }
    };
    
    void update(float dt)
    {
        if (currentState)
        {
            currentState->update(dt);
        }
    };

    void checkState()
    {
        if (currentState->getState() != currentState->nextState())
        {
            auto state = currentState->nextState();
            switch(state)
            {
                case States::GameState :
                {
                    changeState<Game>();
                    break;
                }
                case States::TitleState :
                {
                    changeState<Title>();
                    break;
                }
            }
        }
    };

    void render()
    {
        if (currentState)
        {
            currentState->render();
        }
    };

    States getCurrentState() const { return currentState->getState(); };


private:


    std::unique_ptr<State> currentState;

    sf::RenderWindow &window;



};
#endif