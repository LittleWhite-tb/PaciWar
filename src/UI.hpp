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
