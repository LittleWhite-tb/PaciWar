#include "Game.hpp"

#include "Settings.hpp"

int main()
{
    Settings settings;
    sf::RenderWindow window(sf::VideoMode(settings.windowWidth,settings.windowHeight), Settings::windowName);
	window.setVerticalSyncEnabled(true);

    Game game(settings,window);

    game.run();
	
	return 0;
}
