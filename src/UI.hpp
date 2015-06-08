#ifndef UI_HPP
#define UI_HPP

#include <string>

#include <SFML/Graphics.hpp>

class GameState;

class UI
{
    static const sf::Color textColor;
#ifndef NDEBUG
    static const sf::Color debugTextColor;
#endif

private:
    sf::Font m_font;
#ifndef NDEBUG
    sf::Font m_debugFont;
#endif

    sf::Text m_scoreText;
    sf::Text m_bonusText;
#ifndef NDEBUG
    sf::Text m_debugText;
#endif

    void initText(sf::Text& text);
#ifndef NDEBUG
	void initDebugText(sf::Text& text);
#endif
    
    std::string formatTextNumber(unsigned long number);

public:
    UI(const std::string &fontPath, const std::string& debugFontPath = std::string(""));

    void draw(sf::RenderWindow& window);
    void update(const GameState& state);
};

#endif
