#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "Settings.hpp"
#include "Keyboard.hpp"

#include "Barrier.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "globals.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH,WIN_HEIGHT), Settings::windowName);
	window.setVerticalSyncEnabled(true);
	
	Barrier b(sf::Vector2f(WIN_WIDTH/2,WIN_HEIGHT/2));
    Player p(sf::Vector2f(100,100));
    Enemy e(sf::Vector2f(WIN_WIDTH/2,WIN_HEIGHT/2));

    Keyboard keyboard;
	
    sf::Clock gameClock;
    sf::Time elapsedTime = sf::Time::Zero;
    sf::Time previousStartTime  = gameClock.getElapsedTime();

	while (window.isOpen())
    {
        elapsedTime = gameClock.restart() - previousStartTime;

        // TODO : Find better to catch window closure, or
        // filter most event to not take too much time here (mouse events)
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }

            if (event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::KeyReleased )
            {
                if ( event.key.code == sf::Keyboard::Escape )
                {
                    window.close();
                    break;
                }
            }
        }
                
        window.clear(sf::Color::Black);

        // First try with input.
        // TODO : better input, should take time between two iteration
        // TODO : having a progressive system (aka acceleration) on key press
        // float updateSpeed = elapsedTime.asSeconds() * 1000;
        keyboard.update();
        p.move(keyboard.getMovement());

        b.draw(window);
        // e.draw(window);
        p.draw(window);

        window.display();

        previousStartTime = gameClock.getElapsedTime();
        // std::cout << "Elapsed time (s): " << elapsedTime.asSeconds() << std::endl;
    }
	
	return 0;
}
