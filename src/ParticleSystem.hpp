#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include <vector>

#include <SFML/Graphics.hpp>
#include "ObjectPool.hpp"

class ParticleSystem
{
    struct Particle
    {
        static constexpr float SIZE = 4.0;

        sf::Vector2f position;
        sf::Vector2f direction;
        float speed;

        sf::Vector3f color;


        void draw(sf::RenderWindow& window);
        void update(unsigned int time);
        bool isValid()const;

    };

    struct ParticleDrawer
    {
        bool operator()(sf::RenderWindow& window, const Particle& p)
        {
            sf::Vertex pV[] =
            {
                sf::Vertex(p.position),
                sf::Vertex(p.position-p.direction*Particle::SIZE),
            };

            window.draw(pV,2,sf::Lines);

            return false;
        }
    };

    static constexpr size_t MAX_PARTICULES = 100;

private:
    sf::Vector2f m_spawnPoint;

    Pool<Particle> m_particles;

    std::uniform_real_distribution<float> m_randomFloatDistribution;
    std::uniform_real_distribution<float> m_randomSpeedDistribution;

    void genParticle();

public:
    ParticleSystem(const sf::Vector2f& position);

    void draw(sf::RenderWindow& window);
    void update(unsigned int time);

    std::size_t numberParticlesAlive()const { return m_particles.nbAlive(); }
};

#endif
