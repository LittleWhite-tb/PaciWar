#ifndef ENEMYDEATH_HPP
#define ENEMYDEATH_HPP

#include <array>

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class GameState;
class Enemy;

class EnemyDeath : public Entity
{
private:
    struct Line
    {
        sf::Vector2f center;
        float rotation;

        sf::Vector2f moveDirectionBias;
        float moveSpeed;

        float rotationSpeed;

        Line(const sf::Vector2f& center, float rotation);

        void draw(sf::RenderWindow& window);
    };

    std::array<Line,4> m_lines;
    long unsigned int m_lifeTime;

    static constexpr long unsigned int DURATION = 500;

public:
    EnemyDeath(const sf::Vector2f& position);

    void draw(sf::RenderWindow& window);
    void update(GameState& gstate);

    bool isDead()const { return m_lifeTime > DURATION; }

    void getBoundingSpheres(BoundingSpheres& boundingSpheres)const {}
};

#endif
