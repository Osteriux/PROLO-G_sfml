#pragma once
#include "interactible.hpp"

class Lever : public Interactible
{
private:
    bool activated;
    int doorId;
    sf::Color color;
    static std::unique_ptr<MultiTexture> createRect(sf::Color color, int nb);

public:
    Lever(sf::Color color, int x, int y, int doorId, int nb);
    std::string getDescription() const override;
    sf::Color getColor() const;
    void interact(DynamicGameObject *user) override;
    ~Lever() = default;
};
