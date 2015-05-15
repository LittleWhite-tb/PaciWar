#ifndef PALETTE_HPP
#define PALETTE_HPP

#include <SFML/Graphics.hpp>

class Palette
{
private:

public:
    static sf::Color fromHSV(float hue, float saturation, float value);
};

#endif
