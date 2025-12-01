#pragma once
#include "interactible.h"

class Lever : public Interactible
{
private:
    bool activated;
    int doorId;
    static std::unique_ptr<MultiTexture> createRect(sf::Color color, int nb);

public:
    Lever(sf::Color color, int x, int y, int doorId, int nb);
    std::string getDescription() const override;
    void interact(DynamicGameObject *user) override;
    ~Lever() = default;
};
