//
// Created by Kacper Skelnik on 21.06.2025.
//

#include "CreateCharacterHandler.h"

CreateCharacterHandler::CreateCharacterHandler(const CreateCharacterParams& params): params(params) {}

bool CreateCharacterHandler::invoke(std::shared_ptr<Board> target) {
    return target->createCharacter(params.characterType, params.sourcePosition);
}