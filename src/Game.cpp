#include "Game.hpp"

#include <SFML/Graphics.hpp>

#include "Collisions/Collider.hpp"

#include "Settings.hpp"

Game::Game(const Settings& settings, sf::RenderWindow& targetWindow)
    :m_targetWindow(targetWindow),m_view(sf::Vector2f(settings.windowWidth/2,settings.windowHeight/2),sf::Vector2f(settings.windowWidth,settings.windowHeight)),m_userInterface(settings.fontPath
#if DEBUG_INFO == 1
    ,settings.debugFontPath
#endif
    ),
     m_state(settings)
{
}

void Game::render()
{
    m_targetWindow.clear(sf::Color::Black);
    m_targetWindow.setView(m_view);

    m_state.getObjects().draw(m_targetWindow);
    m_state.getBorders().draw(m_targetWindow);


    m_targetWindow.setView(m_targetWindow.getDefaultView());
    m_userInterface.draw(m_targetWindow);

    m_targetWindow.display();
}

void Game::update()
{
    m_state.update();
    m_view.setCenter((m_state.getObjects().getPlayer().getPosition())/VIEW_DELAY_FACTOR);

    m_userInterface.update(m_state);
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
