#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Barrier.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "globals.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIN_WIDTH,WIN_HEIGHT), WIN_NAME);
	window.setVerticalSyncEnabled(true);
	
	Barrier b(sf::Vector2f(WIN_WIDTH/2,WIN_HEIGHT/2));
    Player p(sf::Vector2f(100,100));
    Enemy e(sf::Vector2f(WIN_WIDTH/2,WIN_HEIGHT/2));
	
	while (window.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
                
            window.clear(sf::Color::Black);

            b.draw(window);
            // e.draw(window);
            p.draw(window);

			window.display();
        }
    }
	
	return 0;
}
