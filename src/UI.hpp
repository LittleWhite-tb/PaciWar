#ifndef UI_HPP
#define UI_HPP

#include <string>

#include <SFML/Graphics.hpp>

#include "Settings.hpp"

class GameState;

class UI
{
    static const sf::Color textColor;
#if DEBUG_INFO == 1
    static const sf::Color debugTextColor;
#endif

private:
    sf::Font m_font;
#if DEBUG_INFO == 1
    sf::Font m_debugFont;
#endif

    sf::Text m_scoreText;
    sf::Text m_bonusText;
#if DEBUG_INFO == 1
    sf::Text m_debugText;
#endif

    void initText(sf::Text& text);
#if DEBUG_INFO == 1
	void initDebugText(sf::Text& text);
#endif
    
    std::string formatTextNumber(unsigned long number);

public:
    UI(const std::string &fontPath, const std::string& debugFontPath = std::string(""));

    void draw(sf::RenderWindow& window);
    void update(const GameState& state);
};

#endif
