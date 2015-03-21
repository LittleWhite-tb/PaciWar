#include "Game.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Collisions/Collider.hpp"

#include "globals.hpp"

Game::Game(sf::RenderWindow& targetWindow)
    :m_targetWindow(targetWindow),
     m_spawner(sf::Vector2f(20,20),sf::Vector2f(WIN_WIDTH-20,WIN_HEIGHT-20)),
     m_particleSystemPool(10000),m_explosionsPool(10)
{
}

void Game::render()
{
    m_targetWindow.clear(sf::Color::Black);

    m_objects.draw(m_targetWindow);

    m_particleSystemPool.update(std::bind(&ParticleSystem::draw,
                                          std::placeholders::_1,
                                          std::ref(m_targetWindow)));
    m_explosionsPool.update(std::bind(&RadialExplosion::draw,
                                      std::placeholders::_1,
                                      std::ref(m_targetWindow)));

    m_targetWindow.display();
}

void Game::update()
{
    m_gameTime.update();
    m_keyboard.update();

    m_objects.getPlayer().move(m_keyboard.getMovement());
	m_objects.update(m_gameTime.getElapsedTime());

    m_objects.detectCollision();

    if ( m_gameTime.shouldSpawnEnemy())
    {
        m_spawner.spawnEnemies(m_objects);
    }

    if ( m_gameTime.shouldSpawnBarrier())
    {
		m_spawner.spawnBarriers(m_objects);
    }


    m_particleSystemPool.update(std::bind(&ParticleSystem::update,
                                          std::placeholders::_1,
                                          m_gameTime.getElapsedTime()));
    m_particleSystemPool.purge(std::bind(&ParticleSystem::isDead,
                                          std::placeholders::_1));

    m_explosionsPool.update(std::bind(&RadialExplosion::update,
                                      std::placeholders::_1,
                                      m_gameTime.getElapsedTime()));
    m_explosionsPool.purge(std::bind(&RadialExplosion::isValid,
                                     std::placeholders::_1));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        spawnParticles();
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        spawnExplosion();
    }
}

void Game::spawnParticles()
{
    ParticleSystem p(sf::Vector2f(sf::Mouse::getPosition(m_targetWindow)));
    m_particleSystemPool.add(p);
}

void Game::spawnExplosion()
{
    RadialExplosion explo(sf::Vector2f(sf::Mouse::getPosition(m_targetWindow)));
    m_explosionsPool.add(explo);
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
