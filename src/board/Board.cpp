//
// Created by Kacper Skelnik on 16.04.2025.
//

#include "Board.h"

#include "../globals/Screen.h"
#include "buildings/ResourceFactory.h"
#include "characters/SerfCharacter.h"

Board::Board(std::shared_ptr<Grid> grid): grid(std::move(grid)) {
    buildings.reserve(32);
}

bool Board::createBuilding(const BuildingType buildingType, const sf::Vector2i& position) {
    const std::optional<GridPosition> maybePosition = grid->addBuilding(buildingType, position);
    if (maybePosition.has_value()) {
        if (isFactory(buildingType)) {
            buildings.emplace_back(std::make_shared<ResourceFactory>(buildingType, maybePosition.value()));
        } else {
            buildings.emplace_back(std::make_shared<Building>(buildingType, maybePosition.value()));
        }
        return true;
    }
    return false;
}

std::optional<std::shared_ptr<Building>> Board::trySelectBuilding(const sf::Vector2i& mousePosition) const {
    using namespace Screen;

    Window::mainViewFocus();

    const sf::Vector2f worldPosition = Window::get().mapPixelToCoords(mousePosition);

    for (const auto& building : buildings) {
        std::optional<sf::Sprite> maybeSprite = grid->getBuildingSprite(building->getPosition());
        if (maybeSprite.has_value() && maybeSprite.value().getGlobalBounds().contains(worldPosition)) {
            return building;
        }
    }
    return std::nullopt;
}

std::optional<std::shared_ptr<Character>> Board::produceCharacter(CharacterType                    characterType,
                                                                  const std::shared_ptr<Building>& byBuilding) {
    const std::optional<GridPosition> maybePosition = grid->addCharacter(characterType, byBuilding->getPosition());
    if (maybePosition.has_value()) {
        if (characterType == Serf) {
            auto character = std::make_shared<SerfCharacter>(characterType, maybePosition.value());
            characters.push_back(character);
            return character;
        }
        auto character = std::make_shared<Character>(characterType, maybePosition.value());
        characters.push_back(character);
        return character;
    }
    return std::nullopt;
}

void Board::moveCharacter(const std::shared_ptr<Character>& character, const GridPosition& destinationPosition) const {
    const std::optional<GridPosition> newPosition = grid->moveCharacter(character->getPosition(), destinationPosition);
    if (newPosition.has_value()) {
        character->setPosition(newPosition.value());
    }
}