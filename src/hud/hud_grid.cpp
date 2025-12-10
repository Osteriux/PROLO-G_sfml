#include "hud_grid.hpp"

HUDGrid::HUDGrid(sf::Vector2f origin, int cellWidth, int cellHeight, int offset, int gap, int columns, int rows)
    : origin(origin),
      cellWidth(cellWidth),
      cellHeight(cellHeight),
      offset(offset),
      gap(gap),
      columns(columns),
      rows(rows) {}

sf::Vector2f HUDGrid::getCellPosition(int col, int row) const
{
    return origin + sf::Vector2f(
                        static_cast<float>(offset + col * (cellWidth + gap)),
                        static_cast<float>(offset + row * (cellHeight + gap)));
}

sf::FloatRect HUDGrid::getRegion(int col, int row, int colspan, int rowspan) const
{
    return sf::FloatRect(
        origin.x + offset + col * (cellWidth + gap),
        origin.y + offset + row * (cellHeight + gap),
        static_cast<float>(colspan * cellWidth + (colspan - 1) * gap),
        static_cast<float>(rowspan * cellHeight + (rowspan - 1) * gap));
}

sf::Vector2f HUDGrid::getCellCenter(int col, int row) const
{
    return getCellPosition(col, row) + sf::Vector2f(
                                           static_cast<float>(cellWidth / 2),
                                           static_cast<float>(cellHeight / 2));
}

int HUDGrid::getTotalWidth() const
{
    return 2 * offset + columns * cellWidth + (columns - 1) * gap;
}

int HUDGrid::getTotalHeight() const
{
    return 2 * offset + rows * cellHeight + (rows - 1) * gap;
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
