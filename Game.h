#ifndef _GAME_H
#define _GAME_H

#include <memory>
#include <vector>
#include <random>
#include "Table.h"
#include "Deck.h"

using namespace std;

class Player;

class Game {
  private:
    std::default_random_engine rng;
    shared_ptr<Deck> deck;
    shared_ptr<Table> table;
    int currentPlayer = 0; // varies 0-3
    vector<shared_ptr<Player>> players;
    bool showTable = true;
    bool quitGame = false;
    int maxScore = 0; // change as game progresses

  public:
    Game(std::default_random_engine rng);
    void startGame();
    void setPlayers();
    void dealCards();
    void newRound();
    void clearRound(); // clear player data
    int findFirstPlayer();
    void firstTurn(int player);
    void playTurn(); // executes play/discard a Card
    bool isroundDone();
    bool isQuitGame();
    void printRoundResults();
    void printWinners();
    bool isGameOver();

    int getCurrentPlayer() const; // needed when notifying text observer
    shared_ptr<Table> getTable();
    void updateMaxScore();
    int getMaxScore();
};

#endif
