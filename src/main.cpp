#include "Game.hpp"

#include "globals.hpp"

#include "Settings.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH,WIN_HEIGHT), Settings::windowName);
	window.setVerticalSyncEnabled(true);

    Game game(window);

    game.run();
	
	return 0;
}
