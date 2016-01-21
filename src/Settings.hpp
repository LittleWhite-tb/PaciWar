#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>

#define DEBUG_INFO 1
#ifndef GOD_MODE
	#define GOD_MODE 0
#endif

struct Settings
{
    int windowWidth;
    int windowHeight;
    static const std::string windowName;

    static const std::string fontPath;
#if DEBUG_INFO == 1
    static const std::string debugFontPath;
#endif

    Settings():
        windowWidth(800),windowHeight(600) {}
};

#endif
