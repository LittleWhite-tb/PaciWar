#include "EnemyDeath.hpp"

#include "GameState.hpp"
#include "Enemy.hpp"

EnemyDeath::EnemyDeath(const Enemy& enemy)
    :m_lines{{
         Line(sf::Vector2f(enemy.getPosition().x-5,
                           enemy.getPosition().y+5),45),
         Line(sf::Vector2f(enemy.getPosition().x-5,
                           enemy.getPosition().y-5),45+90),
         Line(sf::Vector2f(enemy.getPosition().x+5,
                           enemy.getPosition().y-5),45+180),
         Line(sf::Vector2f(enemy.getPosition().x+5,
                           enemy.getPosition().y+5),45+270)
            }},
     m_lifeTime(0)
{

}

void EnemyDeath::draw(sf::RenderWindow& window)
{
    for (Line& line : m_lines)
    {
        line.draw(window);
    }
}

void EnemyDeath::update(GameState& gstate)
{
    for (Line& line : m_lines)
    {
        line.update(gstate.getTime().getElapsedTime());
    }

    m_lifeTime += gstate.getTime().getElapsedTime();
}
