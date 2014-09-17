#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>

struct Settings
{
	unsigned int windowWidth;
	unsigned int windowHeight;
    static const std::string windowName;

    static const float playerSpeed;
};

#endif
