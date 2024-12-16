#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class ColorGenerator {
private:
    static sf::Color makeColor(float gen);
public:
    static std::vector<sf::Color> generateColors(int count);
};