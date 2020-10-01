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

// TODO we can add a description
typedef std::pair<std::string, std::string> Command; /// Short/long command
struct ARGS {
    enum {
        HELP=0,
        WIDTH,
        HEIGHT,
        FULLSCREEN,
        TRACE,
        RECORD,
        REPLAY,
        END
    };
};


Command commands[] = {
    Command("", "--help"),
    Command("-w", "--width"),
    Command("-h", "--height"),
    Command("", "--fullscreen"),
    Command("", "--trace"),
    Command("", "--record"),
    Command("", "--replay"),
};

void CommandParser::usage()
{
    std::cout << "./PaciWar" << std::endl;
    std::cout << "Available arguments:" << std::endl;
    for(auto c : commands)
    {
        std::cout << "\t" << c.first << "\t" << c.second << std::endl;
    }
}


// TODO find a way to factorise this function using the list of Commands
bool CommandParser::parse(int argc, char** argv, Settings& settings)
{
    assert(argv);

    int i = 1; // We pass the program name
    while (i < argc)
    {
        std::string argument = std::string(argv[i]);

        if (argument == commands[ARGS::HELP].first || argument == commands[ARGS::HELP].second)
        {
            return false;
        }
        if (argument == commands[ARGS::WIDTH].first || argument == commands[ARGS::WIDTH].second)
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
        else if (argument == commands[ARGS::HEIGHT].first || argument == commands[ARGS::HEIGHT].second)
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
        else if (argument == commands[ARGS::FULLSCREEN].first || argument == commands[ARGS::FULLSCREEN].second)
        {
            settings.setFullScreenMode(true);
            i+=1;
        }
        else if (argument == commands[ARGS::TRACE].first || argument == commands[ARGS::TRACE].second)
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
        else if (argument == commands[ARGS::RECORD].first || argument == commands[ARGS::RECORD].second)
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
        else if (argument == commands[ARGS::REPLAY].first || argument == commands[ARGS::REPLAY].second)
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
