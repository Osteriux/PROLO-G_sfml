#include "hud_grid.hpp"

HUDGrid::HUDGrid(sf::Vector2f origin, int cellWidth, int cellHeight, sf::Vector2i offset, sf::Vector2i gap, int columns, int rows)
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
                        static_cast<float>(offset.x + col * (cellWidth + gap.x)),
                        static_cast<float>(offset.y + row * (cellHeight + gap.y)));
}

sf::FloatRect HUDGrid::getRegion(int col, int row, int colspan, int rowspan) const
{
    return sf::FloatRect(
        origin.x + offset.x + col * (cellWidth + gap.x),
        origin.y + offset.y + row * (cellHeight + gap.y),
        static_cast<float>(colspan * cellWidth + (colspan - 1) * gap.x),
        static_cast<float>(rowspan * cellHeight + (rowspan - 1) * gap.y));
}

sf::Vector2f HUDGrid::getCellCenter(int col, int row) const
{
    return getCellPosition(col, row) + sf::Vector2f(
                                           static_cast<float>(cellWidth / 2),
                                           static_cast<float>(cellHeight / 2));
}

int HUDGrid::getTotalWidth() const
{
    return 2 * offset.x + columns * cellWidth + (columns - 1) * gap.x;
}

int HUDGrid::getTotalHeight() const
{
    return 2 * offset.y + rows * cellHeight + (rows - 1) * gap.y;
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
