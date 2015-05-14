#ifndef RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP

#include <random>
#include <functional>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class RandomGenerator
{
private:
    static std::mt19937 m_generator;

public:

    static float getFloat(float min, float max);
    static int getInt(int min, int max);

    static sf::Vector2i getIntVector(int minx, int maxx, int miny, int maxy);
    static sf::Vector2f getFloatVector(float minx, float maxx, float miny, float maxy);

    /**
     * @brief Gets a random normalized direction
     * @return the random normalized direction
     */
    static sf::Vector2f getNormalizedDirection();

    /**
     * @brief Gets a random colour
     * @param min
     * @param max
     * @return the random colour
     */
    static sf::Color getColor(unsigned char min, unsigned char max);
};

#endif
