#pragma once
#include <SFML/Graphics.hpp>

/**
 * @brief Manages viewport scaling and letterboxing for adaptive window sizing
 *
 * Maintains a fixed design resolution (960x540) while allowing the window to be resized.
 * Handles scaling and letterboxing to maintain proper aspect ratio and prevent stretching.
 *
 * How it works:
 * - Game world operates at constant 960x540 internally
 * - When window is resized, ViewportManager calculates scale factor
 * - Letterboxing (black bars) added to maintain aspect ratio on different resolutions
 * - Two rendering modes:
 *   1. Map/game world: Uses scaled view (goes through viewport)
 *   2. UI (HUD/Log): Stays at fixed size in screen coordinates
 */
class ViewportManager
{
private:
    inline static const sf::Vector2u DESIGN_RESOLUTION{960, 540};

    sf::Vector2u windowSize;
    float scaleFactor;
    sf::Vector2f letterboxOffset;
    sf::View cachedGameView;

    void calculateScaling();
    void updateCachedView();

public:
    /**
     * @brief Construct ViewportManager with initial window size
     * @param initialWindowSize Starting window dimensions
     */
    ViewportManager(sf::Vector2u initialWindowSize);

    /**
     * @brief Update viewport for new window size
     * @param newWindowSize New window dimensions
     */
    void updateWindowSize(sf::Vector2u newWindowSize);

    /**
     * @brief Get the scale factor to apply to game content
     * @return Scale factor (e.g., 1.5 means 50% larger)
     */
    float getScaleFactor() const { return scaleFactor; }

    /**
     * @brief Get letterbox offset (position of scaled content in window)
     * @return Offset in screen coordinates
     */
    sf::Vector2f getLetterboxOffset() const { return letterboxOffset; }

    /**
     * @brief Get design resolution (constant game size)
     * @return Design resolution (960x540)
     */
    static sf::Vector2u getDesignResolution() { return DESIGN_RESOLUTION; }

    /**
     * @brief Get current window size
     * @return Window dimensions
     */
    sf::Vector2u getWindowSize() const { return windowSize; }

    /**
     * @brief Create view for game world with proper scaling
     *
     * This view scales the 960x540 design space to fit the window,
     * handling letterboxing internally via viewport offset.
     * Both game content and UI render through this view.
     *
     * @return sf::View configured for scaled rendering
     */
    sf::View getGameView() const;

    /**
     * @brief Get the offset and scale to apply to positions for proper letterboxing
     * 
     * When rendering directly in window coordinates, use this to adjust positions.
     * Multiply position by scale factor, then add offset.
     *
     * @return sf::Vector2f offset in window coordinates
     */
    sf::Vector2f getOffsetForWindowCoordinates() const { return letterboxOffset; }

    /**
     * @brief Convert window coordinates to design resolution coordinates
     *
     * Takes mouse position or other input in window space and converts to
     * the 960x540 design resolution space, accounting for scaling and letterboxing.
     *
     * @param windowCoords Coordinates in window space (e.g., from mouse event)
     * @return Coordinates in design resolution space (960x540)
     */
    sf::Vector2f windowToDesignCoordinates(sf::Vector2f windowCoords) const;
};
