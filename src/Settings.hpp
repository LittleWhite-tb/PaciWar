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
#define TRACE_MODE 1
#define GOD_MODE 1

#define MAX_ENEMY_NUMBER 1000

class CommandParser;

struct Settings
{
private:
    int m_windowWidth;
    int m_windowHeight;
    const std::string m_windowName;

    const int m_gameAreaWidth;
    const int m_gameAreaHeight;

    const std::string m_fontPath;
#if DEBUG_INFO == 1
    const std::string m_debugFontPath;
#endif

    std::string m_traceFile;
    std::string m_recordFile;
    std::string m_replayFile;

public:
    Settings();

    void setWindowWidth(int newWidth) { m_windowWidth = newWidth; }
    void setWindowHeight(int newHeight) { m_windowHeight = newHeight; }

    int getWindowWidth()const { return m_windowWidth; }
    int getWindowHeight()const { return m_windowHeight; }
    const std::string& getWindowName()const { return m_windowName; }

    int getGameAreaWidth()const { return m_gameAreaWidth; }
    int getGameAreaHeight()const { return m_gameAreaHeight; }

    const std::string& getFontPath()const { return m_fontPath; }
#if DEBUG_INFO == 1
    const std::string& getDebugFontPath()const { return m_debugFontPath; }
#endif

    void setTraceFile(const std::string& newTraceFile);
    void setRecordFile(const std::string& newRecordFile);
    void setReplayFile(const std::string& newReplayFile);

    bool isTracing()const
    {
#if TRACE_MODE == 1
        return !m_traceFile.empty();
#else
        return false;
#endif
    }
    bool isRecording()const { return !m_recordFile.empty(); }
    bool isReplaying()const { return !m_replayFile.empty(); }

    const std::string& getTraceFile()const { return m_traceFile; }
    const std::string& getRecordFile()const { return m_recordFile; }
    const std::string& getReplayFile()const { return m_replayFile; }
};

#endif
