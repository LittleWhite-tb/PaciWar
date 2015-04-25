#ifndef INPUTDEVICE
#define INPUTDEVICE

#include <SFML/System.hpp>

class InputDevice
{
protected:
    bool m_isEnabled;

public:
    InputDevice()
        :m_isEnabled(true) {}
    virtual ~InputDevice() {}

    virtual void update()=0;
    virtual sf::Vector2f getMovement()const=0;

    bool enabled()const { return m_isEnabled; }
};

#endif
