#include "Barrier.hpp"

const float Barrier::radius = 5.0f;

const float Barrier::heightSize = barrierSize/16.f;
const float Barrier::midSize = barrierSize/2.f;
const float Barrier::edgeSize = barrierSize/8.f;

const sf::Vector2f Barrier::oj_leftEdgePosition = sf::Vector2f(-midSize+Barrier::edgeSize/2.0f,0);
const sf::Vector2f Barrier::oj_rightEdgePosition = sf::Vector2f(midSize+Barrier::edgeSize/2.0f,0);

Barrier::Barrier(const sf::Vector2f& position)
    :Entity(position)
{
}
	
void Barrier::draw(sf::RenderWindow& window)
{
    const sf::Vertex lines[] =
	{
        sf::Vertex(sf::Vector2f(-midSize, 0)),
        sf::Vertex(sf::Vector2f(-midSize+edgeSize, -heightSize)),
        sf::Vertex(sf::Vector2f(-midSize+edgeSize, heightSize)),
        sf::Vertex(sf::Vector2f(-midSize, 0)),
        sf::Vertex(sf::Vector2f(midSize, 0)),
        sf::Vertex(sf::Vector2f(midSize-edgeSize, -heightSize)),
        sf::Vertex(sf::Vector2f(midSize-edgeSize, heightSize)),
        sf::Vertex(sf::Vector2f(midSize, 0))
	};

    sf::Transform t;
    t.translate(m_position);
    t.rotate(m_rotation);

    window.draw(lines,8 ,sf::LinesStrip,t);
}

void Barrier::debugDraw(sf::RenderWindow& window)
{
    sf::CircleShape debugCircle(Barrier::radius);
    debugCircle.setFillColor(sf::Color::Transparent);
    debugCircle.setOutlineThickness(1);
    debugCircle.setOutlineColor(sf::Color(0,255,0));

    debugCircle.setPosition(leftEdgePosition + sf::Vector2f(-Barrier::radius,-Barrier::radius));

    window.draw(debugCircle);

    debugCircle.setPosition(rightEdgePosition + sf::Vector2f(-Barrier::radius,-Barrier::radius));

    window.draw(debugCircle);
}

std::vector<Sphere> Barrier::getBoundingSpheres()const
{
    std::vector<Sphere> spheres;

    spheres.push_back(Sphere(leftEdgePosition, Barrier::radius));
    spheres.push_back(Sphere(rightEdgePosition, Barrier::radius));

    return spheres;
}

Line Barrier::getLine()const
{
    return Line(leftEdgePosition,rightEdgePosition);
}

void Barrier::update(unsigned int time)
{
    m_rotation+=1;

    // Update internal members
    sf::Transform rotationMatrix;
    rotationMatrix.rotate(m_rotation);

    leftEdgePosition = rotationMatrix.transformPoint(oj_leftEdgePosition) + m_position;
    rightEdgePosition = rotationMatrix.transformPoint(oj_rightEdgePosition) + m_position;
}
