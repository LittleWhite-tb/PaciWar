#include "Barrier.hpp"

const float Barrier::radius = 15.0f;

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

    window.draw(lines,8 ,sf::LinesStrip,t);
}

void Barrier::debugDraw(sf::RenderWindow& window)
{
    sf::CircleShape debugCircle(Barrier::radius);
    debugCircle.setFillColor(sf::Color::Transparent);
    debugCircle.setOutlineThickness(1);
    debugCircle.setOutlineColor(sf::Color(0,255,0));
    debugCircle.setPosition(m_position - sf::Vector2f(Barrier::radius-Barrier::midSize+Barrier::edgeSize/2,Barrier::radius));

    window.draw(debugCircle);

    debugCircle.setPosition(m_position - sf::Vector2f(Barrier::radius+Barrier::midSize-Barrier::edgeSize/2,Barrier::radius));

    window.draw(debugCircle);
}

std::vector<Sphere> Barrier::getBoundingSpheres()const
{
    std::vector<Sphere> spheres;
    // Stuff is harder than that (need to handle rotation)
    spheres.push_back(Sphere(sf::Vector2f(m_position.x - Barrier::midSize+Barrier::edgeSize/2,m_position.y), Barrier::radius));
    spheres.push_back(Sphere(sf::Vector2f(m_position.x + Barrier::midSize-Barrier::edgeSize/2,m_position.y), Barrier::radius));
    return spheres;
}

Line Barrier::getLine()const
{
    return Line(sf::Vector2f(m_position.x - Barrier::midSize,m_position.y),
                sf::Vector2f(m_position.x + Barrier::midSize,m_position.y));
}
