#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "Settings.hpp"
#include "Keyboard.hpp"

#include "Collisions/Collider.hpp"

#include "Barrier.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

#include "SpawnGrid.hpp"

#include "globals.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH,WIN_HEIGHT), Settings::windowName);
	window.setVerticalSyncEnabled(true);
	
	Barrier b(sf::Vector2f(WIN_WIDTH/2,WIN_HEIGHT/2));
    Player p(sf::Vector2f(100,100));
    std::vector<Enemy> enemies;
    enemies.reserve(100); // Stupid hack :(
    enemies.push_back(Enemy(sf::Vector2f(WIN_WIDTH/2,WIN_HEIGHT/2)));
    std::vector<Entity*> gameEntities;
    gameEntities.push_back(&b);
    gameEntities.push_back(&p);
    gameEntities.push_back(&enemies[enemies.size()-1]);
    SpawnGrid grid(sf::Vector2f(20,20),sf::Vector2f(WIN_WIDTH-20,WIN_HEIGHT-20),3);

    Keyboard keyboard;
	
    sf::Clock gameClock;
    sf::Time elapsedTime = sf::Time::Zero;
    sf::Time previousStartTime  = gameClock.getElapsedTime();
    sf::Time previonsSpawnTime;

	while (window.isOpen())
    {
        elapsedTime = gameClock.getElapsedTime() - previousStartTime;

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


        for(Entity* pGameEntity : gameEntities)
        {
            pGameEntity->draw(window);
        }

        for(Entity* pGameEntity : gameEntities)
        {
            pGameEntity->debugDraw(window);
        }

        if ( Collider::collides(p,b) == CollisionResult::PLAYER)
        {
            std::cout << "PLayer kill" << std::endl;
        }
        if ( Collider::collides(p,b) == CollisionResult::BARRIER)
        {
            std::cout << "Barrier kill" << std::endl;
        }

        for (Enemy& e : enemies)
        {
            e.move(p);
        }
        b.update(elapsedTime.asMilliseconds());

        window.display();

        previousStartTime = gameClock.getElapsedTime();
        if ((gameClock.getElapsedTime() - previonsSpawnTime).asMilliseconds() > 1000 )
        {
            std::cout << "Spawn" << std::endl;
            std::vector<Enemy> newEnemies;
            grid.spawnEnemies(p.getPosition(),newEnemies,2);
            std::cout << "Got enemies" << std::endl;
            for ( unsigned int i = 0 ; i < newEnemies.size() ; i++)
            {
                enemies.push_back(newEnemies[i]);
                gameEntities.push_back(&enemies[enemies.size()-1]);
            }
            std::cout << "Spawn finished (now : " << enemies.size() << ")" << std::endl;

            previonsSpawnTime = gameClock.getElapsedTime();
        }
        // std::cout << "Elapsed time (s): " << elapsedTime.asSeconds() << std::endl;
    }
	
	return 0;
}
