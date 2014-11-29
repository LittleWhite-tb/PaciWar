#include "RandomGenerator.hpp"

std::mt19937 RandomGenerator::m_generator = std::mt19937(std::random_device()());
