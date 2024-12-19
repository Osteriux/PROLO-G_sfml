#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class ColorGenerator {
private:
    static const std::vector<std::string> COLORS;
    static sf::Color hexToColor(const std::string& hex);
public:
    static std::vector<sf::Color> generateColors(int count);
};
