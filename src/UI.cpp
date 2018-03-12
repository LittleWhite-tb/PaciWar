/*
 * PaciWar : Remake of the "pacifism" mode from Geometry Wars 2
 * Copyright (C) 2014-2015 LittleWhite (lw.demoscene@gmail.com)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "UI.hpp"

#include <string>

#include "Utils/Utils.hpp"

#include "GameState.hpp"

const sf::Color UI::textColor = sf::Color(120,230,50);
#if DEBUG_INFO == 1
    const unsigned int debugTextSize = 8;
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
        text.setCharacterSize(debugTextSize);
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
    m_debugText.setPosition(2, window.getSize().y - 4 * debugTextSize);
	window.draw(m_debugText);
#endif

}

void UI::update(const GameState& state)
{
    m_bonusText.setString("x" + formatTextNumber(state.getScore().getMultiplier()));
    m_scoreText.setString("Score\n" + formatTextNumber(state.getScore().getScore()));

#if DEBUG_INFO == 1
    m_debugText.setString("Draw Time: " + std::to_string(m_drawTime) + "\n" +
                          "Update Time: " + std::to_string(m_updateTime) + "\n" +
                          "Nb enemies : " + std::to_string(state.nbEnemies()));
#endif
}
