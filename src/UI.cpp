#include "UI.hpp"

#include <string>

#include "Utils/Utils.hpp"

#include "GameState.hpp"

const sf::Color UI::textColor = sf::Color(120,230,50);
#if DEBUG_INFO == 1
	const sf::Color UI::debugTextColor = sf::Color(240,240,240);
#endif


UI::UI(const std::string& fontPath, const std::string& debugFontPath)
{
    m_font.loadFromFile(fontPath);
#if DEBUG_INFO == 1
    m_debugFont.loadFromFile(debugFontPath);
#endif

    initText(m_scoreText);
    initText(m_bonusText);
#if DEBUG_INFO == 1
    initDebugText(m_debugText);
#endif
}

void UI::initText(sf::Text& text)
{
    text.setFont(m_font);
    text.setColor(UI::textColor);
    text.setCharacterSize(16);
}

#if DEBUG_INFO == 1
	void UI::initDebugText(sf::Text& text)
	{
		text.setFont(m_debugFont);
		text.setColor(UI::debugTextColor);
		text.setCharacterSize(8);
	}
#endif

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

#if DEBUG_INFO == 1
	window.draw(m_debugText);
#endif

}

void UI::update(const GameState& state)
{
    m_bonusText.setString("x" + formatTextNumber(state.getScore().getMultiplier()));
    m_scoreText.setString("Score\n" + formatTextNumber(state.getScore().getScore()));

#if DEBUG_INFO == 1
	m_debugText.setString("DeltaTime : " + Utils::toString(state.getTime().getElapsedTime()));
#endif
}
