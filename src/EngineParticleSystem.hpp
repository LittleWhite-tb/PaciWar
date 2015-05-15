#ifndef ENGINEPARTICLESYSTEM_HPP
#define ENGINEPARTICLESYSTEM_HPP

#include "ParticleSystem.hpp"

#include <SFML/Graphics.hpp>

class EngineParticleSystem : public ParticleSystem
{
    static constexpr unsigned int BIRTH_PERIOD = 8; // in milliseconds
    static constexpr float PARTICLE_DISPERSION = 0.55;
    static constexpr float GRADIENT_SPEED = 0.1;

private:
    sf::Vector2f m_direction;

    float m_rainbowGradient;

    unsigned m_remaining_birth_time;

    void generateParticle();

public:
    EngineParticleSystem(std::size_t nbMaxParticle=100);

    void update(const sf::Vector2f& position, const sf::Vector2f& direction, unsigned int time);
};

#endif
