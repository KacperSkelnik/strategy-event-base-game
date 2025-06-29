#pragma once

#include "buildings/BuildingType.h"
#include "characters/CharacterType.h"
#include "EnvironmentType.h"
#include "GridPosition.h"
#include "OccupationType.h"
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
    std::vector<int> charactersGrid; // state of occupied cells. 0 = empty, bigger something else

    [[nodiscard]] static sf::priv::Vector4<float> invertMatrix(sf::priv::Vector4<float> matrix);
    [[nodiscard]] sf::Vector2u                    getGridPosition(float posX, float posY) const;
    [[nodiscard]] sf::Vector2f                    getScreenPosition(unsigned col, unsigned row) const;

    [[nodiscard]] BuildingType    getBuildingFrom(unsigned col, unsigned row) const;
    [[nodiscard]] CharacterType   getCharacterFrom(unsigned col, unsigned row) const;
    [[nodiscard]] EnvironmentType getEnvironmentFrom(unsigned col, unsigned row) const;

    [[nodiscard]] static sf::Vector2f getCenterPosition(const sf::Texture& texture, sf::Vector2f position);

    [[nodiscard]] std::vector<GridPosition> getNeighbors(const GridPosition& position) const;

  public:
    Grid() = delete;
    explicit Grid(unsigned cols, unsigned rows);
    ~Grid() = default;

    void                         draw(const std::optional<BuildingType>& maybeSelectedBuilding) const;
    [[nodiscard]] OccupationType checkOccupation(unsigned col, unsigned row) const;
    // buildings
    [[nodiscard]] std::optional<GridPosition> addBuilding(BuildingType buildingType, const sf::Vector2i& position);
    [[nodiscard]] std::optional<sf::Sprite>   getBuildingSprite(const GridPosition& position) const;
    // characters
    [[nodiscard]] std::optional<GridPosition> addCharacter(CharacterType characterType, const GridPosition& sourcePosition);
};