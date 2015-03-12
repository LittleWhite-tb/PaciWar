#ifndef RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP

#include <random>
#include <functional>

class RandomGenerator
{
    private:
        static std::mt19937 m_generator;

    public:

        static float getFloat(float min, float max);
        static int getInt(int min, int max);
};

#endif
