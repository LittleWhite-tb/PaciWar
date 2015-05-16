#ifndef UI_HPP
#define UI_HPP

#include <string>

#include <SFML/Graphics.hpp>

class Score;

class UI
{
    static const sf::Color textColor;

private:
    sf::Font m_font;

    sf::Text m_scoreText;
    sf::Text m_bonusText;

    void initText(sf::Text& text);
    std::string formatTextNumber(unsigned long number);

public:
    UI(const std::string &fontPath);

    void draw(sf::RenderWindow& window);
    void update(const Score& score);
};

#endif
