#include "kniffel.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "player.h"

void initRandomNumGenerator();

int randomNumber();

int countDiceValues(const int *dice, int diceCount);

int selectDice(int *target);

void startPlayMove(Player *currentPlayer, _Bool isLastRound);

Player *determineWinner(Player *players, int playersCount);

void createRandomDice(int dice, int *target) {
    for (int i = 0; i < dice; ++i) {
        target[i] = randomNumber();
    }
}

void startKniffelGame(int playersCount, int roundsCount, int diceCount) {
    initRandomNumGenerator();
    Player *players = (Player *) malloc(sizeof(Player) * playersCount);
    initPlayers(playersCount, players, diceCount);

    printf("Welcome to Kniffel.\n\n");

    for (int i = 1; i <= roundsCount; ++i) {
        printf("####\t%d. Round.\t####\n", i);

        for (int j = 1; j <= playersCount; ++j) {
            Player *currentPlayer = getPlayerForId(players, playersCount, j);
            _Bool hasDiceLeft = currentPlayer->availableDiceCount > 0;

            if (hasDiceLeft) {
                startPlayMove(currentPlayer, i == roundsCount);
                continue;
            }

            printf("Player %d has no dice left!\n", currentPlayer->id);
        }

        printf("\n\n");
    }

    printf("####\tResults\t####\n");
    for (int i = 0; i < playersCount; ++i) {
        printf("Player %d:\t%d\n", players[i].id, players[i].points);
    }

    printf("\n\n");
    printf("####\tThe winner is Player %d\t####!", determineWinner(players, playersCount)->id);

    free(players);
}

void startPlayMove(Player *currentPlayer, _Bool isLastRound) {
    printf("Player %d, you go!\n", currentPlayer->id);

    int *dice = (int *) malloc(sizeof(int) * currentPlayer->availableDiceCount);
    createRandomDice(currentPlayer->availableDiceCount, dice);

    printf("Player %d rolled %d dice:", currentPlayer->id, currentPlayer->availableDiceCount);

    for (int k = 0; k < currentPlayer->availableDiceCount; ++k) {
        printf(" %d ", dice[k]);
    }
    printf("\n");

    int *pickedDice;
    int pickedDiceCount;
    if (isLastRound) {
        pickedDice = dice;
        pickedDiceCount = currentPlayer->availableDiceCount;
    } else {
        printf("Which dice do you want add to your points? ");

        pickedDice = (int *) malloc(sizeof(int) * currentPlayer->availableDiceCount);
        pickedDiceCount = selectDice(pickedDice);
    }

    currentPlayer->availableDiceCount -= pickedDiceCount;

    printf("Player %d has only %d dice left.\n", currentPlayer->id, currentPlayer->availableDiceCount);

    int newPoints = countDiceValues(pickedDice, pickedDiceCount);

    printf("That makes %d points!\n\n", newPoints);

    currentPlayer->points += newPoints;

    free(dice);

    if (!isLastRound) {
        free(pickedDice);
    }
}

Player *determineWinner(Player *players, int playersCount) {
    Player *winner = malloc(sizeof(Player));

    for (int i = 0; i < playersCount - 1; ++i) {
        if (players[i].points > players[i + 1].points) {
            winner = &players[i];
        } else {
            winner = &players[i + 1];
        }
    }

    return winner;
}

int countDiceValues(const int *dice, int diceCount) {
    int sum = 0;
    for (int i = 0; i < diceCount; ++i) {
        sum += dice[i];
    }

    return sum;
}

int selectDice(int *target) {
    int i = 0;
    char temp;
    do {
        scanf("%d%c", &target[i], &temp);

        if (target[i] == 0) {
            return 0;
        }

        i++;
    } while (temp != '\n');

    return i;
}

void initRandomNumGenerator() {
    srand(time(NULL));
}

int randomNumber() {
    return ((rand() % 6) + 1);
}