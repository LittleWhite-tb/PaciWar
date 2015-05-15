#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

#include "InputDevice.hpp"

/**
 * @brief The Joystick class
 * @warning The class will support only one joystick
 */
class Joystick : public InputDevice
{
private:
public:
    Joystick() { m_isEnabled = false; }

    void update();
    sf::Vector2f getMovement()const;
};

#endif
