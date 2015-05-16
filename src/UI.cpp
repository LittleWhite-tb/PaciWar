#include "UI.hpp"

#include "Score.hpp"

#include "Utils/Utils.hpp"
#include "Math/Vector2.hpp"

const sf::Color UI::textColor = sf::Color(120,230,50);

UI::UI(const std::string& fontPath)
{
    m_font.loadFromFile(fontPath);
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

void UI::update(const Score& score)
{
    m_bonusText.setString("x" + Utils::toString(score.getMultiplier()));
    m_scoreText.setString("Score\n" + Utils::toString(score.getScore()));
}
