#include "Game.h"

int main() {
    Game game = Game::create({
        TownHall,
        School,
        Farm,
        GoldMine,
        Quarry,
        LumberjackHouse,
        SawMill,
        Tower,
    });
    game.run();
}
