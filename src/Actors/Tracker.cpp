#include "Tracker.hpp"

#include "Objects/Entity.hpp"

#include "Math/Vector2.hpp"
#include "Math/Interpolation.hpp"
#include "Math/constants.hpp"

void Tracker::update(sf::Vector2f& position, float& rotation, const Entity &target, float moveSpeed, float rotationSpeed, unsigned int deltaTime)
{
    sf::Vector2f targetDir = target.getPosition() - position;

    float targetRotation = Math::getAngle(targetDir);
    rotation = Math::EaseInEaseOut<Math::Angle<float> >::get(rotation,targetRotation,rotationSpeed);

    sf::Vector2f dir;
    if ( Math::length(targetDir) > 5 )
    {
         dir = Math::getVectorFromAngle(rotation);
         position = position + dir * (moveSpeed * deltaTime);
    }
    else
    {
        position = target.getPosition();
    }

}
