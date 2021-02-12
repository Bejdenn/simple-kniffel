#include "player.h"
#include <stdlib.h>

void initPlayers(int numbersOfPlayers, Player *players, int availableDice) {
    for (int i = 0; i < numbersOfPlayers; ++i) {
        Player player;
        player.id = i + 1;
        player.points = 0;
        player.availableDiceCount = availableDice;

        players[i] = player;
    }
}

Player *getPlayerForId(const Player *players, int numberOfPlayers, int id) {
    Player *finder = players;
    for (int i = 1; i <= numberOfPlayers; ++i) {
        if (finder->id == id) {
            return finder;
        }

        finder++;
    }

    return NULL;
}
