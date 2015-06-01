#include "UI.hpp"

#include <string>

#include "Utils/Utils.hpp"

#include "Score.hpp"

const sf::Color UI::textColor = sf::Color(120,230,50);

UI::UI(const std::string& fontPath)
{
    m_font.loadFromFile(fontPath);
    initText(m_scoreText);
    initText(m_bonusText);
}

void UI::initText(sf::Text& text)
{
    text.setFont(m_font);
    text.setColor(UI::textColor);
    text.setCharacterSize(16);
}

std::string UI::formatTextNumber(unsigned long number)
{
    std::string rawStr = Utils::toString(number);
    std::string formatStr;

    std::size_t offset = 3-rawStr.size()%3;
    for (std::size_t i = 0 ; i < rawStr.size() ; i++)
    {
        if (i != 0 && (i+offset) % 3 == 0 )
        {
            formatStr.push_back(',');
        }
        formatStr.push_back(rawStr[i]);

    }
    return formatStr;
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
    m_bonusText.setString("x" + formatTextNumber(score.getMultiplier()));
    m_scoreText.setString("Score\n" + formatTextNumber(score.getScore()));
}
