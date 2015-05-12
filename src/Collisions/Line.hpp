#ifndef __LINE_HPP__
#define __LINE_HPP__

#include <SFML/Graphics.hpp>

struct Line
{
    sf::Vector2f start;
    sf::Vector2f end;

    Line(const sf::Vector2f& start, const sf::Vector2f& end)
        :start(start),end(end) {}
};

#endif
