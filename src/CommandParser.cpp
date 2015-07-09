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

#include "CommandParser.hpp"

#include <string>
#include <iostream>
#include <cassert>

#include "Settings.hpp"
#include "Utils/Utils.hpp"

bool CommandParser::parse(int argc, char** argv, Settings& settings)
{
	assert(argv);

    int i = 1; // We pass the program name
    while (i < argc)
    {
        std::string argument = std::string(argv[i]);

        if (argument == "-w" || argument == "--width")
        {
            if ( i+1 < argc)
            {
                settings.setWindowWidth(Utils::fromString<unsigned int>(std::string(argv[i+1])));
            }
            else
            {
                std::cout << argument << " option needs an argument" << std::endl;
                return false;
            }
            i+=2;
        }
        else if (argument == "-h" || argument == "--height")
        {
            if ( i+1 < argc)
            {
                settings.setWindowHeight(Utils::fromString<unsigned int>(std::string(argv[i+1])));
            }
            else
            {
                std::cout << argument << " option needs an argument" << std::endl;
                return false;
            }
            i+=2;
        }
        else if (argument == "--trace")
        {
            if ( i+1 < argc)
            {
                settings.setTraceFile(std::string(argv[i+1]));
            }
            else
            {
                std::cout << "--trace option needs an argument" << std::endl;
                return false;
            }
            i+=2;
        }
        else if (argument == "--record")
        {
            if ( i+1 < argc)
            {
                settings.setRecordFile(std::string(argv[i+1]));
            }
            else
            {
                std::cout << "--record option needs an argument" << std::endl;
                return false;
            }
            i+=2;
        }
        else if (argument == "--replay")
        {
            if ( i+1 < argc)
            {
                settings.setReplayFile(std::string(argv[i+1]));
            }
            else
            {
                std::cout << "--replay option needs an argument" << std::endl;
                return false;
            }
            i+=2;
        }
        else
        {
            std::cout << argument << " is an unexpected option" << std::endl;
            return false;
        }
    }

    return true;
}
