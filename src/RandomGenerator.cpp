#include "RandomGenerator.hpp"

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
