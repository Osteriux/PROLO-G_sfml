#pragma once
#include "../static_game_object.h"

class Lever : public StaticGameObject
{
private:
    bool activated;
    int doorId;
public:
    Lever(std::unique_ptr<MultiTexture> animation, Carte* carte, int x, int y, int doorId);
    void action(DynamicGameObject* user) override;
    ~Lever() = default;
};
