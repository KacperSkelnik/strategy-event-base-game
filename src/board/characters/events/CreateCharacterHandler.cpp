#pragma once

#include "CreateCharacterHandler.h"

CreateCharacterHandler::CreateCharacterHandler(CreateCharacterParams params): params(std::move(params)) {
}

std::optional<std::shared_ptr<Character>> CreateCharacterHandler::invoke(const std::shared_ptr<Board> target) {
    return target->produceCharacter(params.characterType, params.school);
}