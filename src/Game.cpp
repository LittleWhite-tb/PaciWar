#include "Game.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Collisions/Collider.hpp"

#include "globals.hpp"

Game::Game(sf::RenderWindow& targetWindow)
    :m_targetWindow(targetWindow),
     m_spawner(sf::Vector2f(20,20),sf::Vector2f(WIN_WIDTH-20,WIN_HEIGHT-20))
{
}

void Game::render()
{
    m_targetWindow.clear(sf::Color::Black);

    m_objects.draw(m_targetWindow);

    m_targetWindow.display();
}

void Game::update()
{
    m_gameTime.update();
    m_keyboard.update();

    m_objects.getPlayer().move(m_keyboard.getMovement(),m_gameTime.getElapsedTime());
	m_objects.update(m_gameTime.getElapsedTime());

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
