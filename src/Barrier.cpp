#include "Barrier.hpp"

const float Barrier::radius = 5.0f;

const float Barrier::heightSize = barrierSize/16.f;
const float Barrier::midSize = barrierSize/2.f;
const float Barrier::edgeSize = barrierSize/8.f;

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

    sf::Vector2f leftEdgePosition = sf::Vector2f(-midSize+Barrier::edgeSize/2,0);
    sf::Vector2f rightEdgePosition = sf::Vector2f(midSize-Barrier::edgeSize/2,0);

    sf::Transform t;
    t.rotate(m_rotation);
    leftEdgePosition = t.transformPoint(leftEdgePosition);
    rightEdgePosition = t.transformPoint(rightEdgePosition);

    debugCircle.setPosition(m_position + leftEdgePosition + sf::Vector2f(-Barrier::radius,-Barrier::radius));

    window.draw(debugCircle);

    debugCircle.setPosition(m_position + rightEdgePosition + sf::Vector2f(-Barrier::radius,-Barrier::radius));

    window.draw(debugCircle);
}

std::vector<Sphere> Barrier::getBoundingSpheres()const
{
    std::vector<Sphere> spheres;

    sf::Vector2f leftEdgePosition = sf::Vector2f(-midSize+Barrier::edgeSize/2,0);
    sf::Vector2f rightEdgePosition = sf::Vector2f(midSize-Barrier::edgeSize/2,0);

    sf::Transform t;
    t.rotate(m_rotation);
    leftEdgePosition = t.transformPoint(leftEdgePosition);
    rightEdgePosition = t.transformPoint(rightEdgePosition);

    spheres.push_back(Sphere(sf::Vector2f(m_position + leftEdgePosition), Barrier::radius));
    spheres.push_back(Sphere(sf::Vector2f(m_position + rightEdgePosition), Barrier::radius));

    return spheres;
}

Line Barrier::getLine()const
{
    sf::Vector2f leftEdgePosition = sf::Vector2f(-midSize+Barrier::edgeSize/2,0);
    sf::Vector2f rightEdgePosition = sf::Vector2f(midSize-Barrier::edgeSize/2,0);

    sf::Transform t;
    t.rotate(m_rotation);
    leftEdgePosition = t.transformPoint(leftEdgePosition);
    rightEdgePosition = t.transformPoint(rightEdgePosition);

    return Line(sf::Vector2f(m_position + leftEdgePosition),
                sf::Vector2f(m_position + rightEdgePosition));
}

void Barrier::update(unsigned int time)
{
    m_rotation+=1;
}
