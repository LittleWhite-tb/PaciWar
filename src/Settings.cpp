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

#include "Settings.hpp"

#include "version.hpp"

#if DEBUG_INFO == 1
    const std::string Settings::windowName = "PaciWar v" VERSION_MAJOR "." VERSION_MINOR "." VERSION_PATCH " - " VERSION_SHA;
#else
    const std::string Settings::windowName = "PaciWar v" VERSION_MAJOR "." VERSION_MINOR "." VERSION_PATCH;
#endif

const std::string Settings::fontPath = "./data/DejaVuSansMono.ttf";
#if DEBUG_INFO == 1
    const std::string Settings::debugFontPath = "./data/DejaVuSansMono.ttf";
#endif

#if TRACE_MODE == 1
    const std::string Settings::traceFile = "./paciwar.trace";
#endif
#if RECORD_MODE == 1
    const std::string Settings::recordFile = "./paciwar.input";
#endif
#if REPLAY_MODE == 1
    const std::string Settings::replayFile = "./paciwar.input";
#endif
