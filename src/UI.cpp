#include "UI.hpp"

#include "GameState.hpp"

#include "Utils.hpp"
#include "SFML/Vector2Utils.hpp"
#include "globals.hpp"

const sf::Color UI::textColor = sf::Color(120,230,50);

UI::UI()
{
    m_font.loadFromFile(FONT_PATH);
    initTest(m_scoreText);
    initTest(m_bonusText);
}

void UI::initTest(sf::Text& text)
{
    text.setFont(m_font);
    text.setColor(UI::textColor);
    text.setCharacterSize(16);
}

void UI::draw(sf::RenderWindow& window)
{
    m_scoreText.setPosition(20,20);
    m_scoreText.setRotation(-8);
    window.draw(m_scoreText);

    m_bonusText.setPosition(window.getSize().x/2-m_bonusText.getLocalBounds().width/2,0);
    window.draw(m_bonusText);
}

void UI::update(const GameState& gstate)
{
    m_bonusText.setString("x" + Utils::toString(gstate.getMultiplier()));
    m_scoreText.setString("Score\n" + Utils::toString(gstate.getScore()));
}
