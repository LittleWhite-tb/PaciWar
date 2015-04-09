#include "Game.hpp"

#include <SFML/Graphics.hpp>

#include "Collisions/Collider.hpp"

#include "Utils.hpp"
#include "globals.hpp"

Game::Game(sf::RenderWindow& targetWindow)
    :m_targetWindow(targetWindow),
     m_spawner(sf::Vector2f(20,20),sf::Vector2f(WIN_WIDTH-20,WIN_HEIGHT-20))
{
    m_uiFont.loadFromFile(FONT_PATH);
#ifndef NDEBUG
     m_debugFont.loadFromFile(DEBUG_FONT_PATH);
#endif
}

void Game::render()
{
    m_targetWindow.clear(sf::Color::Black);

    m_objects.draw(m_targetWindow);

    {
        sf::Text multiplierText;
        multiplierText.setFont(m_uiFont);
        multiplierText.setColor(sf::Color(120,230,50));
        multiplierText.setCharacterSize(16);
        multiplierText.setString("x" + Utils::toString(m_state.getMultiplier()));
        multiplierText.setPosition(m_targetWindow.getSize().x/2-multiplierText.getLocalBounds().width/2,0);

        m_targetWindow.draw(multiplierText);
    }

#ifndef NDEBUG
    {
        sf::Text text;
        text.setFont(m_debugFont);

        text.setColor(sf::Color::White);
        text.setCharacterSize(10);
        text.setString("DeltaTime : " + Utils::toString(m_gameTime.getElapsedTime()));

        m_targetWindow.draw(text);
    }
#endif

    m_targetWindow.display();
}

void Game::update()
{
    m_gameTime.update();
    m_keyboard.update();

    m_objects.getPlayer().move(m_keyboard.getMovement(),m_gameTime.getElapsedTime());
    m_objects.update(m_state, m_gameTime.getElapsedTime());

    if ( m_gameTime.shouldSpawnEnemy())
    {
        m_spawner.spawnEnemies(m_objects);
    }

    if ( m_gameTime.shouldSpawnBarrier())
    {
		m_spawner.spawnBarriers(m_objects);
    }
}

void Game::checkClosure()
{
    // TODO : Find better to catch window closure, or
    // filter most event to not take too much time here (mouse events)
    sf::Event event;
    while (m_targetWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_targetWindow.close();
            break;
        }

        if (event.type == sf::Event::KeyPressed ||
            event.type == sf::Event::KeyReleased )
        {
            if ( event.key.code == sf::Keyboard::Escape )
            {
                m_targetWindow.close();
                break;
            }
        }
    }
}

bool Game::run()
{
    while (m_targetWindow.isOpen())
    {
        render();
        update();

        checkClosure();
    }
    return true;
}
