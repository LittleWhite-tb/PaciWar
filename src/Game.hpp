#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "UI.hpp"
#include "GameState.hpp"

#include "Spawner.hpp"

class Settings;

class Game
{
    static constexpr float VIEW_DELAY_FACTOR = 2.f;

private:
    sf::RenderWindow& m_targetWindow;
    sf::View m_view;

    UI m_userInterface;

    GameState m_state;

    Spawner m_spawner;

    void render();
    void update();

    void checkClosure();

public:
    Game(const Settings& settings, sf::RenderWindow& targetWindow);

    bool run();
};

#endif
