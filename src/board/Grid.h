#pragma once

#include "buildings/BuildingType.h"
#include "characters/CharacterType.h"
#include "EnvironmentType.h"
#include "GridPosition.h"
#include "OccupationType.h"
#include <SFML/Graphics.hpp>
#include "../globals/Random.h"

struct GridState {
    std::vector<int> buildingsGrid;   // state of occupied cells. 0 = empty, bigger something else
    std::vector<int> environmentGrid; // state of occupied cells. 0 = Grass, bigger something else
    std::vector<int> charactersGrid;  // state of occupied cells. 0 = empty, bigger something else

    GridState(const unsigned cols, const unsigned rows) {
        using namespace Random;

        buildingsGrid = std::vector(cols * rows, 0);

        // Character's occupation
        charactersGrid = std::vector(cols * rows, 0);

        //  Environment occupation
        environmentGrid = std::vector(cols * rows, 0);
        for (unsigned i = 0; i < cols * rows; ++i) {
            const float randomValue = RandomGenerator::getFloat(0, 1);
            if (randomValue < 0.05f) {
                environmentGrid[i] = GoldRock;
            }
        }
    }
};

class Grid final {

private:
    float                      iX = 1;
    float                      iY = 0.57;
    float                      jX = -1;
    float                      jY = 0.57;
    unsigned                   cols, rows;
    std::shared_ptr<GridState> state = nullptr;

    [[nodiscard]] int getIndex(unsigned col, unsigned row) const;

    [[nodiscard]] static sf::priv::Vector4<float> invertMatrix(sf::priv::Vector4<float> matrix);
    [[nodiscard]] sf::Vector2u                    getGridPosition(float posX, float posY) const;
    [[nodiscard]] sf::Vector2f                    getScreenPosition(unsigned col, unsigned row) const;

    [[nodiscard]] BuildingType    getBuildingFrom(unsigned col, unsigned row) const;
    [[nodiscard]] CharacterType   getCharacterFrom(unsigned col, unsigned row) const;
    [[nodiscard]] EnvironmentType getEnvironmentFrom(unsigned col, unsigned row) const;

    [[nodiscard]] static sf::Vector2f getCenterPosition(const sf::Texture& texture, sf::Vector2f position);

    [[nodiscard]] std::vector<OccupationType> checkOccupations(unsigned col, unsigned row) const;
    [[nodiscard]] std::vector<GridPosition>   getNeighbors(const GridPosition& position) const;
    [[nodiscard]] std::vector<GridPosition>   dijkstraPath(const GridPosition& start, const GridPosition& goal) const;

public:
    Grid() = delete;
    explicit Grid(unsigned cols, unsigned rows);
    ~Grid() = default;

    void setState(const std::shared_ptr<GridState>& newState) { state = newState; };
    void draw(const std::optional<BuildingType>& maybeSelectedBuilding) const;

    // buildings
    [[nodiscard]] std::optional<GridPosition>
        addBuilding(BuildingType buildingType, const sf::Vector2i& position) const;
    [[nodiscard]] std::optional<sf::Sprite> getBuildingSprite(const GridPosition& position) const;
    // characters
    [[nodiscard]] std::optional<GridPosition> addCharacter(CharacterType       characterType,
                                                           const GridPosition& schoolPosition) const;
    [[nodiscard]] std::optional<GridPosition> moveCharacter(const GridPosition& sourcePosition,
                                                            const GridPosition& destinationPosition) const;
};