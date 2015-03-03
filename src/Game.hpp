#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Barrier.hpp"
#include "Enemy.hpp"
#include "ParticleSystem.hpp"

#include "Spawner.hpp"
#include "GameTime.hpp"

#include "Keyboard.hpp"

class Game
{
private:
    sf::RenderWindow& m_targetWindow;

    std::shared_ptr<Player> m_player;
    std::vector<std::shared_ptr<Barrier> > m_barriers;
    std::vector<std::shared_ptr<Enemy> > m_enemies;

    std::vector<std::shared_ptr<Entity> > m_entities;
    std::vector<std::shared_ptr<ParticleSystem> > m_particleSystem;

    Spawner m_spawner;

    Keyboard m_keyboard;
    GameTime m_gameTime;

    void render();
    void update();

    void spawnParticles();
    void checkClosure();

public:
    Game(sf::RenderWindow& targetWindow);

    bool run();
};

#endif
