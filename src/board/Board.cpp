//
// Created by Kacper Skelnik on 16.04.2025.
//

#include "Board.h"

#include "../globals/Screen.h"

Board::Board(std::shared_ptr<Grid> grid): grid(std::move(grid)) {
    buildings.reserve(32);
}

bool Board::createBuilding(const BuildingType buildingType, const sf::Vector2i& position) {
    const std::optional<GridPosition> maybePosition = grid->addBuilding(buildingType, position);
    if (maybePosition.has_value()) {
        buildings.emplace_back(std::make_shared<Building>(buildingType, maybePosition.value()));
        return true;
    }
    return false;
}

std::optional<std::shared_ptr<Building>> Board::trySelectBuilding(const sf::Vector2i& mousePosition) const {
    using namespace Screen;

    Window::mainViewFocus();

    const sf::Vector2f worldPosition = Window::get().mapPixelToCoords(mousePosition);

    for (const auto building : buildings) {
        std::optional<sf::Sprite> maybeSprite = grid->getBuildingSprite(building->getPosition());
        if (maybeSprite.has_value() && maybeSprite.value().getGlobalBounds().contains(worldPosition)) {
            return building;
        }
    }
    return std::nullopt;
}

bool Board::createCharacter(CharacterType characterType, const GridPosition& sourcePosition) {
    std::optional<GridPosition> maybePosition = grid->addCharacter(characterType, sourcePosition);
    if (maybePosition.has_value()) {
        characters.emplace_back(std::make_shared<Character>(characterType, maybePosition.value()));
        return true;
    }
    return false;
}