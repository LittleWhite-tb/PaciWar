#ifndef RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP

#include <random>

class RandomGenerator
{
    private:
        static std::mt19937 m_generator;

    public:
        static std::mt19937& get()
        {
            return m_generator;
        }

};

#endif
