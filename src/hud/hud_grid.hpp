#pragma once
#include <SFML/Graphics.hpp>

/**
 * @brief Grid-based layout system for HUD elements
 *
 * Provides a virtual grid overlay for positioning HUD elements with pixel-perfect
 * alignment. Supports single-cell positioning and multi-cell spanning regions.
 */
class HUDGrid
{
private:
    sf::Vector2f origin; ///< Top-left corner of the grid
    int cellWidth;       ///< Width of each grid cell in pixels
    int cellHeight;      ///< Height of each grid cell in pixels
    int offset;          ///< Offset from outer edges in pixels
    int gap;             ///< Gap between cells in pixels
    int columns;         ///< Number of columns in the grid
    int rows;            ///< Number of rows in the grid

public:
    /**
     * @brief Construct a new HUDGrid
     *
     * @param origin Top-left corner position of the grid
     * @param cellWidth Width of each cell in pixels
     * @param cellHeight Height of each cell in pixels
     * @param offset Offset from outer edges in pixels (default: 0)
     * @param gap Gap between cells in pixels (default: 0)
     * @param columns Number of columns
     * @param rows Number of rows
     */
    HUDGrid(sf::Vector2f origin, int cellWidth, int cellHeight, int offset, int gap, int columns, int rows);

    /**
     * @brief Get the position of a specific grid cell
     *
     * @param col Column index (0-based)
     * @param row Row index (0-based)
     * @return sf::Vector2f Top-left corner position of the cell
     */
    sf::Vector2f getCellPosition(int col, int row) const;

    /**
     * @brief Get a rectangular region spanning multiple cells
     *
     * @param col Starting column index
     * @param row Starting row index
     * @param colspan Number of columns to span
     * @param rowspan Number of rows to span
     * @return sf::FloatRect Rectangle covering the specified cells
     */
    sf::FloatRect getRegion(int col, int row, int colspan, int rowspan) const;

    /**
     * @brief Get the center position of a cell
     *
     * @param col Column index
     * @param row Row index
     * @return sf::Vector2f Center point of the cell
     */
    sf::Vector2f getCellCenter(int col, int row) const;

    /**
     * @brief Get total grid width in pixels
     */
    int getTotalWidth() const;

    /**
     * @brief Get total grid height in pixels
     */
    int getTotalHeight() const;

    /**
     * @brief Get cell dimensions
     */
    sf::Vector2f getCellSize() const;

    /**
     * @brief Get grid origin
     */
    sf::Vector2f getOrigin() const;

    /**
     * @brief Get number of columns
     */
    int getColumns() const;

    /**
     * @brief Get number of rows
     */
    int getRows() const;
};
