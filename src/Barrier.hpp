#ifndef BARRIER_HPP
#define BARRIER_HPP

#include <SFML/Graphics.hpp>

#include "Collisions/Line.hpp"
#include "Entity.hpp"
#include "Momentum.hpp"

class Barrier : public Entity
{
private:
    static constexpr int barrierSize = 96;
    static constexpr float heightSize = Barrier::barrierSize/16.f;
    static constexpr float midSize = Barrier::barrierSize/2.f;
    static constexpr float edgeSize = Barrier::barrierSize/8.f;
    static constexpr float radius = 5.0f;

    // Object space position
    static const sf::Vector2f oj_leftEdgePosition;
    static const sf::Vector2f oj_rightEdgePosition;
    Momentum m_momentum;

    sf::Vector2f leftEdgePosition;
    sf::Vector2f rightEdgePosition;

    // static constexpr float ROTATION_SPEED = 0.015f;

public:
    Barrier(const sf::Vector2f& position);
	
	void draw(sf::RenderWindow& window);
    void debugDraw(sf::RenderWindow& window);

    void getBoundingSpheres(BoundingSpheres &boundingSpheres)const;
    Line getLine()const;

    void update(GameState& gstate);

    const sf::Vector2f& getLeftEdgePosition()const { return leftEdgePosition; }
    const sf::Vector2f& getRightEdgePosition()const { return rightEdgePosition; }
};

#endif
