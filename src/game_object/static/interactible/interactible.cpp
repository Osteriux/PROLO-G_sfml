#include "interactible.h"

Interactible::Interactible(std::unique_ptr<MultiTexture> animation, int x, int y)
    : StaticGameObject(std::move(animation), x, y)
{
}

void Interactible::action(DynamicGameObject *user)
{
    interact(user);
}

std::vector<Interactible::InteractibleType> Interactible::getAllInteractibleTypes()
{
    return {InteractibleType::LEVER};
}

std::string Interactible::interactibleTypeToString(InteractibleType type)
{
    switch (type)
    {
    case InteractibleType::LEVER:
        return "LEVER";
    default:
        throw std::invalid_argument("Invalid interactible type");
    }
}

Interactible::InteractibleType Interactible::stringToInteractibleType(std::string type)
{
    if (type == "LEVER")
        return InteractibleType::LEVER;
    else
        throw std::invalid_argument("Invalid interactible type");
}

int Interactible::interactibleTypeToId(InteractibleType type)
{
    switch (type)
    {
    case InteractibleType::LEVER:
        return 0;
    default:
        throw std::invalid_argument("Invalid interactible id");
    }
}

Interactible::InteractibleType Interactible::idToInteractibleType(int id)
{
    switch (id)
    {
    case 0:
        return InteractibleType::LEVER;
    default:
        throw std::invalid_argument("Invalid interactible id");
    }
}

std::string Interactible::texturePath(InteractibleType type)
{
    return "assets/static/" + interactibleTypeToString(type) + ".png";
}
