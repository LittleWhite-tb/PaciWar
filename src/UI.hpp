#ifndef UI_HPP
#define UI_HPP

#include <SFML/Graphics.hpp>

class GameState;

class UI
{
    static const sf::Color textColor;

private:
    sf::Font m_font;

    sf::Text m_scoreText;
    sf::Text m_bonusText;

    void initTest(sf::Text& text);

public:
    UI();

    void draw(sf::RenderWindow& window);
    void update(const GameState& gstate);
};

#endif
