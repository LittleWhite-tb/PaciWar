#include "Game.hpp"

#include <SFML/Graphics.hpp>

#include "Collisions/Collider.hpp"

#include "Utils/Utils.hpp"
#include "Settings.hpp"

Game::Game(const Settings& settings, sf::RenderWindow& targetWindow)
    :m_targetWindow(targetWindow),m_view(sf::Vector2f(settings.windowWidth/2,settings.windowHeight/2),sf::Vector2f(settings.windowWidth,settings.windowHeight)),m_userInterface(settings.fontPath),
     m_state(settings),
     m_spawner(m_state.getBorders().getRestrictedLimits())
{
#ifndef NDEBUG
     m_debugFont.loadFromFile(settings.debugFontPath);
#endif
}

void Game::render()
{
    m_targetWindow.clear(sf::Color::Black);
    m_targetWindow.setView(m_view);

    m_state.getObjects().draw(m_targetWindow);
    m_state.getBorders().draw(m_targetWindow);


    m_targetWindow.setView(m_targetWindow.getDefaultView());
    m_userInterface.draw(m_targetWindow);

#ifndef NDEBUG
    {
        sf::Text text;
        text.setFont(m_debugFont);

        text.setColor(sf::Color::White);
        text.setCharacterSize(10);
        text.setString("DeltaTime : " + Utils::toString(m_state.getTime().getElapsedTime()));

        m_targetWindow.draw(text);
    }
#endif

    m_targetWindow.display();
}

void Game::update()
{
    m_state.update();
    m_view.setCenter((m_state.getObjects().getPlayer().getPosition())/VIEW_DELAY_FACTOR);

    if ( m_state.getTime().shouldSpawnEnemy())
    {
        m_spawner.spawnEnemies(m_state);
    }

    if ( m_state.getTime().shouldSpawnBarrier())
    {
        m_spawner.spawnBarriers(m_state);
    }

    m_userInterface.update(m_state.getScore());
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
