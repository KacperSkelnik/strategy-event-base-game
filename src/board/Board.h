#pragma once

#include "buildings/Building.h"
#include "characters/Character.h"
#include "Grid.h"
#include <vector>

class Board final: public EventEntity {

private:
    std::vector<std::shared_ptr<Building>>  buildings;
    std::vector<std::shared_ptr<Character>> characters;
    std::shared_ptr<Grid>                   grid;

public:
    explicit Board(std::shared_ptr<Grid> grid);
    ~Board() override = default;

    // buildings
    [[nodiscard]] bool createBuilding(BuildingType buildingType, const sf::Vector2i& position);
    [[nodiscard]] std::optional<std::shared_ptr<Building>> trySelectBuilding(const sf::Vector2i& mousePosition) const;
    [[nodiscard]] std::vector<std::shared_ptr<Building>> getBuildings() const { return buildings; }
    // characters
    [[nodiscard]] std::optional<std::shared_ptr<Character>> produceCharacter(CharacterType             characterType,
                                                                             std::shared_ptr<Building> byBuilding);
    void moveCharacter(const std::shared_ptr<Character>& character, const GridPosition& destinationPosition) const;
};