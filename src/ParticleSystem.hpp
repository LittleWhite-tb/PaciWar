#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "ObjectPool.hpp"
#include "RandomGenerator.hpp"

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

    static constexpr size_t MAX_PARTICULES = 100;

private:
    sf::Vector2f m_spawnPoint;

    Pool<Particle> m_particles;

    void genParticle();

public:
    ParticleSystem(const sf::Vector2f& position);

    void draw(sf::RenderWindow& window);
    void update(unsigned int time);

    std::size_t numberParticlesAlive()const { return m_particles.nbAlive(); }
    bool isDead()const { return m_particles.nbAlive() == 0; }
};

#endif
