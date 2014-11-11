#ifndef VECTOR2UTILS_HPP
#define VECTOR2UTILS_HPP

#include <SFML/Graphics.hpp>

// Todo :
// Make this class handling all Vector2

namespace SFMLUtils
{
    float length(const sf::Vector2f& v);
    void normalise(sf::Vector2f& v);
    float distance(const sf::Vector2f& v1, const sf::Vector2f& v2);
}

#endif
