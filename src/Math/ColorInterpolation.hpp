#ifndef __COLORINTERPOLATION_HPP__
#define __COLORINTERPOLATION_HPP__

#include "Interpolation.hpp"

#include <SFML/Graphics.hpp>

namespace Math
{
    template <>
    class LinearInterpolation<sf::Color>
    {
    public:
        static sf::Color get(const sf::Color& begin, const sf::Color& end, float interp)
        {
            return sf::Color(
                        LinearInterpolation<unsigned char>::get(begin.r,end.r,interp),
                        LinearInterpolation<unsigned char>::get(begin.g,end.g,interp),
                        LinearInterpolation<unsigned char>::get(begin.b,end.b,interp)
                     );
        }
    };
}

#endif
