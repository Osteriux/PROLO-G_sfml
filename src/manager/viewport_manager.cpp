#include "viewport_manager.hpp"
#include <algorithm>
#include "../utils/logger/logger.hpp"

ViewportManager::ViewportManager(sf::Vector2u initialWindowSize)
    : windowSize(initialWindowSize), scaleFactor(1.0f), letterboxOffset(0.0f, 0.0f)
{
    calculateScaling();
    updateCachedView();
    Logger::log("ViewportManager initialized - Design: " + std::to_string(DESIGN_RESOLUTION.x) + "x" +
                    std::to_string(DESIGN_RESOLUTION.y) + ", Window: " + std::to_string(windowSize.x) + "x" +
                    std::to_string(windowSize.y),
                Logger::DEBUG);
}

void ViewportManager::updateWindowSize(sf::Vector2u newWindowSize)
{
    if (newWindowSize.x == 0 || newWindowSize.y == 0)
    {
        Logger::log("Invalid window size, ignoring resize", Logger::WARNING);
        return;
    }

    windowSize = newWindowSize;
    calculateScaling();
    updateCachedView();
    Logger::log("Viewport updated - Window: " + std::to_string(windowSize.x) + "x" +
                    std::to_string(windowSize.y) + ", Scale: " + std::to_string(scaleFactor),
                Logger::DEBUG);
}

void ViewportManager::calculateScaling()
{
    // Calculate scale factor while maintaining aspect ratio
    float scaleX = static_cast<float>(windowSize.x) / DESIGN_RESOLUTION.x;
    float scaleY = static_cast<float>(windowSize.y) / DESIGN_RESOLUTION.y;

    // Use the smaller scale to maintain aspect ratio (adds letterboxing)
    scaleFactor = std::min(scaleX, scaleY);

    // Calculate the scaled content dimensions
    float scaledWidth = DESIGN_RESOLUTION.x * scaleFactor;
    float scaledHeight = DESIGN_RESOLUTION.y * scaleFactor;

    // Center the scaled content in the window
    letterboxOffset.x = (windowSize.x - scaledWidth) / 2.0f;
    letterboxOffset.y = (windowSize.y - scaledHeight) / 2.0f;
}

void ViewportManager::updateCachedView()
{
    cachedGameView.setSize(static_cast<float>(DESIGN_RESOLUTION.x), static_cast<float>(DESIGN_RESOLUTION.y));
    cachedGameView.setCenter(DESIGN_RESOLUTION.x / 2.0f, DESIGN_RESOLUTION.y / 2.0f);

    float viewportLeft = letterboxOffset.x / windowSize.x;
    float viewportTop = letterboxOffset.y / windowSize.y;
    float viewportWidth = (DESIGN_RESOLUTION.x * scaleFactor) / windowSize.x;
    float viewportHeight = (DESIGN_RESOLUTION.y * scaleFactor) / windowSize.y;

    cachedGameView.setViewport(sf::FloatRect(viewportLeft, viewportTop, viewportWidth, viewportHeight));
}

sf::View ViewportManager::getGameView() const
{
    return cachedGameView;
}

sf::Vector2f ViewportManager::windowToDesignCoordinates(sf::Vector2f windowCoords) const
{
    sf::Vector2f viewportCoords = windowCoords - letterboxOffset;

    sf::Vector2f designCoords;
    if (scaleFactor > 0.0f)
    {
        designCoords.x = viewportCoords.x / scaleFactor;
        designCoords.y = viewportCoords.y / scaleFactor;
    }
    else
    {
        designCoords = viewportCoords;
    }

    // Clamp to design resolution bounds (0 to 960x540)
    designCoords.x = std::max(0.0f, std::min(designCoords.x, static_cast<float>(DESIGN_RESOLUTION.x)));
    designCoords.y = std::max(0.0f, std::min(designCoords.y, static_cast<float>(DESIGN_RESOLUTION.y)));

    Logger::log("Coordinate conversion: Window(" + std::to_string(static_cast<int>(windowCoords.x)) + "," +
                    std::to_string(static_cast<int>(windowCoords.y)) + ") -> Design(" +
                    std::to_string(static_cast<int>(designCoords.x)) + "," +
                    std::to_string(static_cast<int>(designCoords.y)) + ") Scale:" +
                    std::to_string(scaleFactor),
                Logger::DEBUG);

    return designCoords;
}
