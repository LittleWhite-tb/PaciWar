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

#include <iostream>

#include "Settings.hpp"

#include "version.hpp"


Settings::Settings()
    :m_windowWidth(800),m_windowHeight(600),
#if DEBUG_INFO == 1
    m_windowName("PaciWar v" VERSION_MAJOR "." VERSION_MINOR "." VERSION_PATCH " - " VERSION_SHA),
#else
    m_windowName("PaciWar v" VERSION_MAJOR "." VERSION_MINOR "." VERSION_PATCH),
#endif
    m_gameAreaWidth(1024),m_gameAreaHeight(1024),
    m_fontPath("./data/DejaVuSansMono.ttf")
#if DEBUG_INFO == 1
    ,m_debugFontPath("./data/DejaVuSansMono.ttf")
#endif
{

}

void Settings::setTraceFile(const std::string& newTraceFile)
{
    m_traceFile = newTraceFile;
}

void Settings::setRecordFile(const std::string& newRecordFile)
{
    if (isReplaying())
    {
        std::cout << "You can't record and replay at the same time (ignoring record)" << std::endl;
        return;
    }
    m_recordFile = newRecordFile;
}

void Settings::setReplayFile(const std::string& newReplayFile)
{
    if (isRecording())
    {
        std::cout << "You can't replay and record at the same time (ignoring replay)" << std::endl;
        return;
    }
    m_replayFile = newReplayFile;
}

