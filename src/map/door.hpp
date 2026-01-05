#pragma once
#include <sstream>
#include "../animation/multi_texture.hpp"
#include "../manager/game_event_system.hpp"
#include "direction.hpp"

class GameObject;

class Door : public IEventListener
{
private:
    MultiTexture texture;
    sf::RectangleShape bg;
    sf::Vector2f bgOffset;
    bool ouverte;
    Direction::Dir dir;
    sf::Color color;
    int doorId;
    std::string texturePath(Direction::Dir dir);
    sf::RectangleShape createColorRect(Direction::Dir dir, sf::Vector2f position);

public:
    Door(sf::Color color, int doorId, Direction::Dir dir, sf::Vector2f position);
    void init() override;
    bool estOuverte();
    void ouvrir();
    void fermer();
    sf::Color getColor();
    void setPosition(sf::Vector2f position);
    void setScale(sf::Vector2f scale);
    void draw(sf::RenderTarget &target);
    void onEvent(const GameEvent &event) override;
    ~Door();
};
