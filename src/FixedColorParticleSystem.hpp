#ifndef FIXEDCOLORPARTICLESYSTEM_HPP
#define FIXEDCOLORPARTICLESYSTEM_HPP

#include "ParticleSystem.hpp"

#include <SFML/Graphics.hpp>

class FixedColorParticleSystem : public ParticleSystem
{
private:
    sf::Color m_color;

    void generateParticles();

public:
    FixedColorParticleSystem(const sf::Vector2f& position, const sf::Color& color, std::size_t nbMaxParticle=100);
};

#endif
