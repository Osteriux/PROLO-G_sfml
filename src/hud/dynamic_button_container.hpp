#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "button/button_base.hpp"

/**
 * @brief Layout mode for dynamic button containers
 */
enum class LayoutMode
{
    VERTICAL_LIST,   ///< Stack buttons vertically
    HORIZONTAL_LIST, ///< Stack buttons horizontally
    GRID             ///< Arrange buttons in a grid pattern
};

/**
 * @brief Container for dynamically positioned buttons with automatic layout
 *
 * Manages a collection of buttons within a defined region, automatically
 * calculating positions based on the layout mode.
 *
 * @tparam ButtonType Type of button (ButtonImage, ButtonLever, etc.)
 */
template <typename ButtonType,
          typename = typename std::enable_if<std::is_base_of<ButtonBase, ButtonType>::value>::type>
class DynamicButtonContainer
{
private:
    sf::Vector2f regionStart;        ///< Top-left corner of container region
    sf::Vector2f regionSize;         ///< Total available space (width, height)
    sf::Vector2f itemSize;           ///< Size of each button
    int spacing;                     ///< Spacing between buttons in pixels
    LayoutMode mode;                 ///< Layout pattern
    std::vector<ButtonType> buttons; ///< Managed buttons

    /**
     * @brief Recalculate positions for all buttons based on layout mode
     */
    void updatePositions()
    {
        for (size_t i = 0; i < buttons.size(); i++)
        {
            sf::Vector2f pos;

            switch (mode)
            {
            case LayoutMode::VERTICAL_LIST:
                pos = regionStart + sf::Vector2f(0, i * (itemSize.y + spacing));
                break;

            case LayoutMode::HORIZONTAL_LIST:
                pos = regionStart + sf::Vector2f(i * (itemSize.x + spacing), 0);
                break;

            case LayoutMode::GRID:
            {
                int cols = static_cast<int>(regionSize.x / (itemSize.x + spacing));
                if (cols < 1)
                    cols = 1;
                int row = i / cols;
                int col = i % cols;
                pos = regionStart + sf::Vector2f(
                                        col * (itemSize.x + spacing),
                                        row * (itemSize.y + spacing));
                break;
            }
            }

            buttons[i].setPosition(pos);
        }
    }

public:
    /**
     * @brief Construct a new Dynamic Button Container
     *
     * @param regionStart Top-left corner of the container region
     * @param regionSize Size of the available space (width, height)
     * @param itemSize Size of each button
     * @param spacing Spacing between buttons in pixels
     * @param mode Layout mode (default: VERTICAL_LIST)
     */
    DynamicButtonContainer(
        sf::Vector2f regionStart,
        sf::Vector2f regionSize,
        sf::Vector2f itemSize,
        int spacing,
        LayoutMode mode = LayoutMode::VERTICAL_LIST)
        : regionStart(regionStart),
          regionSize(regionSize),
          itemSize(itemSize),
          spacing(spacing),
          mode(mode) {}

    /**
     * @brief Default constructor
     */
    DynamicButtonContainer()
        : regionStart(0, 0),
          regionSize(0, 0),
          itemSize(0, 0),
          spacing(0),
          mode(LayoutMode::VERTICAL_LIST) {}

    /**
     * @brief Clear all buttons from the container
     */
    void clear()
    {
        buttons.clear();
    }

    /**
     * @brief Add a button to the container and recalculate positions
     *
     * @param button Button to add (will be moved)
     */
    void addButton(ButtonType &&button)
    {
        buttons.push_back(std::move(button));
        updatePositions();
    }

    /**
     * @brief Get the number of buttons in the container
     */
    size_t size() const
    {
        return buttons.size();
    }

    /**
     * @brief Check if container is empty
     */
    bool empty() const
    {
        return buttons.empty();
    }

    /**
     * @brief Draw all buttons in the container
     *
     * @param window Render window to draw to
     */
    void draw(sf::RenderWindow &window)
    {
        for (auto &button : buttons)
        {
            button.draw(window);
        }
    }

    /**
     * @brief Handle click detection for all buttons
     *
     * @param mousePos Mouse position to check
     * @param clickedIndex Output parameter for the index of clicked button
     * @return true if a button was clicked, false otherwise
     */
    bool handleClick(sf::Vector2f mousePos, int &clickedIndex)
    {
        for (size_t i = 0; i < buttons.size(); i++)
        {
            if (buttons[i].isClicked(mousePos))
            {
                clickedIndex = static_cast<int>(i);
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Get reference to button at index
     */
    ButtonType &operator[](size_t index)
    {
        return buttons[index];
    }

    /**
     * @brief Get const reference to button at index
     */
    const ButtonType &operator[](size_t index) const
    {
        return buttons[index];
    }

    /**
     * @brief Update container configuration
     *
     * @param regionStart New region start position
     * @param regionSize New region size
     * @param itemSize New item size
     * @param spacing New spacing
     * @param mode New layout mode
     */
    void configure(
        sf::Vector2f regionStart,
        sf::Vector2f regionSize,
        sf::Vector2f itemSize,
        int spacing,
        LayoutMode mode = LayoutMode::VERTICAL_LIST)
    {
        this->regionStart = regionStart;
        this->regionSize = regionSize;
        this->itemSize = itemSize;
        this->spacing = spacing;
        this->mode = mode;
        updatePositions();
    }

    /**
     * @brief Get the region bounds
     */
    sf::FloatRect getRegion() const
    {
        return sf::FloatRect(regionStart, regionSize);
    }
};
