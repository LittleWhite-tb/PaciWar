#ifndef ENEMYDEATH_HPP
#define ENEMYDEATH_HPP

#include <array>

#include <SFML/Graphics.hpp>

#include "Momentum.hpp"

class GameState;
class Enemy;

class EnemyDeath
{
private:
    struct Line
    {
        sf::Vector2f m_center;
        float m_rotation;
        Momentum m_momentum;

        Line(const sf::Vector2f& center, float rotation)
            :m_center(center),m_rotation(rotation) {}

        void draw(sf::RenderWindow& window)
        {
            const sf::Vertex lines[] =
            {
                sf::Vertex(sf::Vector2f(0, 10)),
                sf::Vertex(sf::Vector2f(10, 0))
            };

            sf::Transform t;
            t.translate(m_center);
            t.rotate(m_rotation);

            window.draw(lines,2,sf::Lines,t);
        }

        void update(long unsigned int deltaTime)
        {
            m_momentum.update(m_center,m_rotation,deltaTime);
        }
    };

    std::array<Line,4> m_lines;
    long unsigned int m_lifeTime;

    static constexpr long unsigned int DURATION = 1000;

public:
    EnemyDeath(const Enemy& enemy);

    void draw(sf::RenderWindow& window);
    void update(GameState& gstate);

    bool isDead()const { return m_lifeTime > DURATION; }
};

#endif
