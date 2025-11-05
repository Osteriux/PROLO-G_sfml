#pragma once
#include "../static_game_object.h"

class Lever : public StaticGameObject
{
private:
    bool activated;
    int doorId;
    static std::unique_ptr<MultiTexture> createRect(sf::Color color, int nb);
public:
    Lever(sf::Color color, GameManager* gameManager, int x, int y, int doorId, int nb);
    std::string getDescription() const override;
    void action(DynamicGameObject* user) override;
    ~Lever() = default;
};
