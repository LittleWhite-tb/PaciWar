#ifndef INPUT_HPP
#define INPUT_HPP

#include <list>
#include <memory>

#include <SFML/System.hpp>

#include "InputDevice.hpp"

class Input
{
    static constexpr float DEADZONE_LIMIT = 0.15f;

private:
    std::list<std::unique_ptr<InputDevice> > m_devices;
    //std::list<InputDevice* > m_devices;

    Input(const Input&)=delete;

public:
    Input();

    void update();
    sf::Vector2f getMovement()const;
};

#endif
