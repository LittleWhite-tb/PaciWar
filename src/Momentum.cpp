#include "Momentum.hpp"

#include "RandomGenerator.hpp"

Momentum::Momentum()
    :m_direction(sf::Vector2f(RandomGenerator::getFloat(-1,1),
                              RandomGenerator::getFloat(-1,1))),
     m_moveSpeed(0.01f),
     m_rotationSpeed(0.2f)
{

}

Momentum::Momentum(const sf::Vector2f& direction, float moveSpeed, float rotationSpeed)
    :m_direction(direction),m_moveSpeed(moveSpeed),m_rotationSpeed(rotationSpeed)
{

}

void Momentum::update(sf::Vector2f& position, float& rotation, unsigned int deltaTime)
{
    position += m_direction * (m_moveSpeed * deltaTime);
    rotation += m_rotationSpeed;
}
