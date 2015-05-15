#ifndef RADIALEXPLOSION_HPP
#define RADIALEXPLOSION_HPP

#include <SFML/Graphics.hpp>

class RadialExplosion
{
private:
    sf::Vector2f m_spawnPoint;
    float m_radius;

    static constexpr float RADIUS_MAX = 115;
    static constexpr float GROWTH_SPEED = 0.6f;

public:
    RadialExplosion(const sf::Vector2f& position)
        :m_spawnPoint(position),m_radius(0) {}

    void draw(sf::RenderWindow& window)const;
    void update(unsigned int time);
    bool isValid()const;

    float getRadius()const { return m_radius; }
    const sf::Vector2f& getCenter()const { return m_spawnPoint; }

    static constexpr float EFFECT_SIZE = 20;
};

#endif
