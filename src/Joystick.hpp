#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

#include <SFML/System.hpp>

/**
 * @brief The Joystick class
 * @warning The class will support only one joystick
 */
class Joystick
{
private:
    bool m_isConnected;

public:
    Joystick()
        :m_isConnected(false) {}

    void update();
    sf::Vector2f getMovement()const;

    bool enabled()const { return m_isConnected; }
};

#endif
