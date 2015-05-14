#include "RandomGenerator.hpp"

#include "SFML/Vector2Utils.hpp"

std::mt19937 RandomGenerator::m_generator = std::mt19937(std::random_device()());

float RandomGenerator::getFloat(float min, float max)
{
    std::uniform_real_distribution<> dist(min,max);
    return dist(m_generator);
}

int RandomGenerator::getInt(int min, int max)
{
    std::uniform_int_distribution<> dist(min,max);
    return dist(m_generator);
}

sf::Vector2i RandomGenerator::getIntVector(int minx, int maxx, int miny, int maxy)
{
    std::uniform_int_distribution<> distx(minx,maxx);
    std::uniform_int_distribution<> disty(miny,maxy);
    return sf::Vector2i(distx(m_generator),disty(m_generator));
}

sf::Vector2f RandomGenerator::getFloatVector(float minx, float maxx, float miny, float maxy)
{
    std::uniform_real_distribution<> distx(minx,maxx);
    std::uniform_real_distribution<> disty(miny,maxy);
    return sf::Vector2f(distx(m_generator),disty(m_generator));
}

sf::Vector2f RandomGenerator::getNormalizedDirection()
{
    std::uniform_real_distribution<> dist(-1.0f,1.0f);
    sf::Vector2f direction(dist(m_generator),dist(m_generator));
    SFMLUtils::normalise(direction);
    return direction;
}

sf::Color RandomGenerator::getColor(unsigned char min, unsigned char max)
{
    std::uniform_int_distribution<> dist(min,max);
    return sf::Color(dist(m_generator),dist(m_generator),dist(m_generator));
}
