#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "UI.hpp"
#include "GameState.hpp"
#include "ObjectBank.hpp"

#include "Spawner.hpp"
#include "GameTime.hpp"

#include "Keyboard.hpp"

class Game
{
private:
    sf::RenderWindow& m_targetWindow;
    UI m_userInterface;
#ifndef NDEBUG
    sf::Font m_debugFont;
#endif

    GameState m_state;
    ObjectBank m_objects;

    Spawner m_spawner;

    Keyboard m_keyboard;
    GameTime m_gameTime;

    void render();
    void update();

    void checkClosure();

public:
    Game(sf::RenderWindow& targetWindow);

    bool run();
};

#endif
