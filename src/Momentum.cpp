#include "Momentum.hpp"

#include "SFML/Vector2Utils.hpp"
#include "RandomGenerator.hpp"

Momentum::Momentum()
    :m_direction(RandomGenerator::getNormalizedDirection()),
     m_moveSpeed(RandomGenerator::getFloat(0,0.1f)),
     m_rotationSpeed(RandomGenerator::getFloat(0,m_moveSpeed))
{
    SFMLUtils::normalise(m_direction);
}

Momentum::Momentum(float maxMoveSpeed, float maxRotationSpeed)
    :m_direction(RandomGenerator::getNormalizedDirection()),
     m_moveSpeed(RandomGenerator::getFloat(0,maxMoveSpeed)),
     m_rotationSpeed(RandomGenerator::getFloat(0,maxRotationSpeed))
{
    SFMLUtils::normalise(m_direction);
}

Momentum::Momentum(const sf::Vector2f& direction, float moveSpeed, float rotationSpeed)
    :m_direction(direction),m_moveSpeed(moveSpeed),m_rotationSpeed(rotationSpeed)
{

}

void Momentum::update(sf::Vector2f& position, float& rotation, unsigned int deltaTime)
{
    position += m_direction * (m_moveSpeed * deltaTime);
    rotation += m_rotationSpeed * deltaTime;
}
