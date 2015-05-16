#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>

struct Settings
{
    int windowWidth;
    int windowHeight;
    static const std::string windowName;

    static const std::string fontPath;
#ifndef NDEBUG
    static const std::string debugFontPath;
#endif

    Settings():
        windowWidth(800),windowHeight(600) {}
};

#endif
