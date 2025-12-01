#pragma once
#include "../static_game_object.h"

class Interactible : public StaticGameObject
{
public:
    enum class InteractibleType
    {
        LEVER
    };
    static const InteractibleType LEVER = InteractibleType::LEVER;
    static std::string interactibleTypeToString(InteractibleType type);
    static InteractibleType stringToInteractibleType(std::string type);
    static int interactibleTypeToId(InteractibleType type);
    static InteractibleType idToInteractibleType(int id);
    static std::vector<InteractibleType> getAllInteractibleTypes();

    Interactible(std::unique_ptr<MultiTexture> animation, int x, int y);
    void action(DynamicGameObject *user) override;
    virtual void interact(DynamicGameObject *user) = 0;
    ~Interactible() = default;

protected:
    InteractibleType type;
    static std::string texturePath(InteractibleType type);
};
