#include "color_generator.h"

std::vector<sf::Color> ColorGenerator::generateColors(int num) {
    std::vector<sf::Color> colors = std::vector<sf::Color>();
    if (num < 2)
        return colors;
    float dx = 1.0f / (float) (num - 1);
    for (int i = 0; i < num; i++) {
        colors.push_back(makeColor(i * dx));
    }
    return colors;
}

sf::Color ColorGenerator::makeColor(float x) {
    float r = 0.0f;
    float g = 0.0f;
    float b = 1.0f;
    if (x >= 0.0f && x < 0.2f) {
        x = x / 0.2f;
        r = 0.0f;
        g = x;
        b = 1.0f;
    } else if (x >= 0.2f && x < 0.4f) {
        x = (x - 0.2f) / 0.2f;
        r = 0.0f;
        g = 1.0f;
        b = 1.0f - x;
    } else if (x >= 0.4f && x < 0.6f) {
        x = (x - 0.4f) / 0.2f;
        r = x;
        g = 1.0f;
        b = 0.0f;
    } else if (x >= 0.6f && x < 0.8f) {
        x = (x - 0.6f) / 0.2f;
        r = 1.0f;
        g = 1.0f - x;
        b = 0.0f;
    } else if (x >= 0.8f && x <= 1.0f) {
        x = (x - 0.8f) / 0.2f;
        r = 1.0f;
        g = 0.0f;
        b = x;
    }
    return sf::Color(r, g, b);
}