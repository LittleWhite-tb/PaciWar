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

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>

#define DEBUG_INFO 1
#define TRACE_MODE 0
#define RECORD_MODE 0
#define REPLAY_MODE 1
#define GOD_MODE 1

#define MAX_ENEMY_NUMBER 1000

class CommandParser;

struct Settings
{
    int windowWidth;
    int windowHeight;
    static const std::string windowName;

    static const std::string fontPath;
#if DEBUG_INFO == 1
    static const std::string debugFontPath;
#endif

#if TRACE_MODE == 1
    static std::string traceFile;
#endif
#if RECORD_MODE == 1
    static std::string recordFile;
#endif
#if REPLAY_MODE == 1
    static std::string replayFile;
#endif

    Settings():
        windowWidth(800),windowHeight(600) {}

    friend CommandParser;
};

#endif
