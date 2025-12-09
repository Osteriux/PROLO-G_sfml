#ifndef _RELEASE
#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <vector>
#include "../manager/game_event.hpp"
#include "../manager/game_event_system.hpp"
#include "../game_object/static/pickup/pickup.hpp"
#include "../map/direction.hpp"

/**
 * @brief In-game debug console for firing custom events
 *
 * Press F1 to toggle the console on/off.
 * Use number keys to select event types and fire them with preset or custom parameters.
 */
class DebugConsole
{
private:
    bool isVisible;
    sf::Font font;
    sf::Text helpText;
    sf::RectangleShape background;
    sf::Vector2f position;

public:
    DebugConsole(sf::Vector2f position);
    bool loadFont(const std::string &fontPath);

    /**
     * @brief Toggle console visibility
     */
    void toggle();

    /**
     * @brief Handle keyboard input for debug commands
     * @return true if event was handled by console
     */
    bool handleInput(const sf::Event &event);

    /**
     * @brief Draw the console overlay
     */
    void draw(sf::RenderWindow &window);

    /**
     * @brief Check if console is currently visible
     */
    bool visible() const { return isVisible; }

    // Quick fire methods with default parameters
    void quickFirePlayerDamage(int damage = 1);
    void quickFirePlayerHeal(int healing = 1);
    void quickFireInventoryChange(int mine = 1, int battery = 1, int bomb = 1, int detector = 1);
    void quickFireItemPickup(Pickup::PickupType type);
    void quickFireDoorToggle(int doorId);
};
#endif // _RELEASE
