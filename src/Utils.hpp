#ifndef UTILS_HPP
#define UTILS_HPP

#include <sstream>

class Utils
{
public:
    template <typename T>
    inline static std::string toString(T number)
    {
        std::ostringstream oss;
        oss << number;
        return oss.str();
    }
};

#endif
