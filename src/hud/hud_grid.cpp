#include "hud_grid.hpp"

HUDGrid::HUDGrid(sf::Vector2f origin, int cellWidth, int cellHeight, int columns, int rows)
    : origin(origin),
      cellWidth(cellWidth),
      cellHeight(cellHeight),
      columns(columns),
      rows(rows) {}

sf::Vector2f HUDGrid::getCellPosition(int col, int row) const
{
    return origin + sf::Vector2f(
                        static_cast<float>(col * cellWidth),
                        static_cast<float>(row * cellHeight));
}

sf::FloatRect HUDGrid::getRegion(int col, int row, int colspan, int rowspan) const
{
    return sf::FloatRect(
        origin.x + col * cellWidth,
        origin.y + row * cellHeight,
        static_cast<float>(colspan * cellWidth),
        static_cast<float>(rowspan * cellHeight));
}

sf::Vector2f HUDGrid::getCellCenter(int col, int row) const
{
    return getCellPosition(col, row) + sf::Vector2f(
                                           static_cast<float>(cellWidth / 2),
                                           static_cast<float>(cellHeight / 2));
}

int HUDGrid::getTotalWidth() const
{
    return columns * cellWidth;
}

int HUDGrid::getTotalHeight() const
{
    return rows * cellHeight;
}

sf::Vector2f HUDGrid::getCellSize() const
{
    return sf::Vector2f(static_cast<float>(cellWidth), static_cast<float>(cellHeight));
}

sf::Vector2f HUDGrid::getOrigin() const
{
    return origin;
}

int HUDGrid::getColumns() const
{
    return columns;
}

int HUDGrid::getRows() const
{
    return rows;
}
