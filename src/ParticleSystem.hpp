#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include <vector>

#include <SFML/Graphics.hpp>

class ParticleSystem
{
    struct Particle
    {
        static constexpr float SIZE = 4.0;

        sf::Vector2f position;
        sf::Vector2f direction;
        float speed;

        sf::Vector3f color;
    };

    static constexpr size_t MAX_PARTICULES = 100;

private:
    sf::Vector2f m_spawnPoint;

    std::vector<Particle> m_particles;
    size_t m_particlesAlive;

    std::uniform_real_distribution<float> m_randomFloatDistribution;
    std::uniform_real_distribution<float> m_randomSpeedDistribution;

    void genParticle(size_t index);
    void killParticle(size_t index);


public:
    ParticleSystem(const sf::Vector2f& position);



    void draw(sf::RenderWindow& window);
    void update(unsigned int time);

    size_t numberParticlesAlive()const { return m_particlesAlive; }
};

#endif
