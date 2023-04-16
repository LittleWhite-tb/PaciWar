#ifndef CHRONO_HPP
#define CHRONO_HPP

#include <SFML/System.hpp>

#include <chrono>

class Chrono
{
private:
    std::chrono::time_point<std::chrono::system_clock> m_startTime;

public:
    Chrono():m_startTime(std::chrono::system_clock::now()) {}
    unsigned int get()const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_startTime).count();
    }
};

#endif
