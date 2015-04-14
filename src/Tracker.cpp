#include "Tracker.hpp"

#include "Entity.hpp"

#include "SFML/Vector2Utils.hpp"
#include "Math/Interpolation.hpp"
#include "Math/constants.hpp"

void Tracker::update(sf::Vector2f& position, float& rotation, const Entity &target, float moveSpeed, float rotationSpeed, unsigned int deltaTime)
{
    sf::Vector2f targetDir = target.getPosition() - position;

    float targetRotation = SFMLUtils::getAngle(targetDir);
    rotation = Math::EaseInEaseOut<Math::Angle<float> >::get(rotation,targetRotation,rotationSpeed);

    sf::Vector2f dir;
    if ( SFMLUtils::length(targetDir) > 5 )
    {
         dir = SFMLUtils::getVectorFromAngle(rotation);
         position = position + dir * (moveSpeed * deltaTime);
    }
    else
    {
        position = target.getPosition();
    }

}
