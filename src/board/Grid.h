#pragma once

#include "BuildingType.h"
#include "EnvironmentType.h"
#include "GridPosition.h"
#include <SFML/Graphics.hpp>

class Grid {
  private:
    float            iX = 1;
    float            iY = 0.57;
    float            jX = -1;
    float            jY = 0.57;
    unsigned         cols, rows;
    std::vector<int> buildingsGrid; // state of occupied cells. 0 = empty, bigger something else
    std::vector<int> environmentGrid;

    [[nodiscard]] static sf::priv::Vector4<float> invertMatrix(sf::priv::Vector4<float> matrix);
    [[nodiscard]] sf::Vector2u                    getGridPosition(float posX, float posY) const;
    [[nodiscard]] sf::Vector2f                    getScreenPosition(unsigned col, unsigned row) const;
    [[nodiscard]] BuildingType                    getBuildingFrom(unsigned col, unsigned row) const;
    [[nodiscard]] EnvironmentType                 getEnvironmentFrom(unsigned col, unsigned row) const;
    [[nodiscard]] static sf::Vector2f             getBuildingPosition(BuildingType building, sf::Vector2f position);

  public:
    Grid() = delete;
    explicit Grid(unsigned cols, unsigned rows);
    ~Grid() = default;

    void                                      draw(const std::optional<BuildingType>& maybeSelectedBuilding) const;
    [[nodiscard]] bool                        isCellOccupied(unsigned col, unsigned row) const;
    [[nodiscard]] std::optional<GridPosition> addBuilding(BuildingType buildingType, const sf::Vector2i& position);
    [[nodiscard]] std::optional<sf::Sprite>   getBuildingSprite(const GridPosition& position) const;
};