#ifndef SIMPLE_KNIFFEL_PLAYER_H
#define SIMPLE_KNIFFEL_PLAYER_H

typedef struct Player {
    int id;
    int points;
    int availableDiceCount;
} Player;

void initPlayers(int numbersOfPlayers, Player *players, int availableDice);

Player *getPlayerForId(const Player *players, int numberOfPlayers, int id);

#endif //SIMPLE_KNIFFEL_PLAYER_H
