#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "UI.hpp"
#include "GameState.hpp"

#include "Spawner.hpp"

class Game
{
    static constexpr float VIEW_DELAY_FACTOR = 2.f;

private:
    sf::RenderWindow& m_targetWindow;
    sf::View m_view;

    UI m_userInterface;
#ifndef NDEBUG
    sf::Font m_debugFont;
#endif

    GameState m_state;

    Spawner m_spawner;

    void render();
    void update();

    void checkClosure();

public:
    Game(sf::RenderWindow& targetWindow);

    bool run();
};

#endif
