#include "Palette.hpp"

#include <cassert>

sf::Color Palette::fromHSV(float hue, float saturation, float value)
{
    assert(saturation>=0);

    // http://en.wikipedia.org/wiki/HSL_and_HSV#From_HSV
    float chroma = value * saturation;
    float huePrime = fmod(hue/60.f, 6);
    float x = chroma * (1 - fabs(fmod(huePrime,2) - 1));
    float m = value - chroma;

    float r=0;
    float g=0;
    float b=0;
    if (huePrime < 0) // Error case
    {
        return sf::Color(0,0,0);
    }
    else if (huePrime < 1 )
    {
        r = chroma;
        g = x;
    }
    else if (huePrime < 2)
    {
        r = x;
        g = chroma;
    }
    else if ( huePrime < 3 )
    {
        g = chroma;
        b = x;
    }
    else if (huePrime < 4)
    {
        g = x;
        b = chroma;
    }
    else if (huePrime < 5)
    {
        r = x;
        b = chroma;
    }
    else if (huePrime < 6)
    {
        r = chroma;
        b = x;
    }
    else
    {
        return sf::Color(0,0,0);
    }
    return sf::Color((r+m)*255,(g+m)*255,(b+m)*255);
}
