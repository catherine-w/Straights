#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include <memory>
#include <string>
#include "Table.h"
using namespace std;

class Card;
class Table;
class Player {

  friend class Game;

  protected:
    
    // attributes
    int id; // player ID ranges from 0-3
    shared_ptr<Table> table;
    int totalScore = 0;// keeps track of score across all rounds
    vector<shared_ptr<Card>> hand; // list of Cards in hand for current round
    vector<shared_ptr<Card>> discards; // list of Cards in discard pile for current round
    vector<shared_ptr<Card>> legalMoves; // vector of legal moves during each play 

    // functions
    Player(int id, shared_ptr<Table> table); // creates new Player
    Player(int id, shared_ptr<Table> table, int score, vector<shared_ptr<Card>> hand, vector<shared_ptr<Card>> discards); // creates copy of Player in case of ragequit

    virtual pair<string, shared_ptr<Card>> choosePlay() = 0; // either play or discard card
    void dealCard(shared_ptr<Card>); // adds c to hand
    void playCard(shared_ptr<Card> c); // removes card from hand, add to table
    void discardCard(shared_ptr<Card> c); // remove from hand and adds card to discard pile
    void clearCards(); // clear hand and discards after each round
    
    bool has7S(); // returns true if player has 7S card
    bool handEmpty(); // returns true if player has no more cards
    int getPlayerID() const; // returns player id
    int getTotalScore() const; // returns player's total score
    vector<shared_ptr<Card>> getHand() const; // returns vector of hand
    vector<shared_ptr<Card>> getDiscards() const; // returns vector of discard
    vector<shared_ptr<Card>> getLegalMoves() const; // returns vector of legal moves
    int getDiscardScore() const;
    void updateLegalMoves(); // update legal moves
    void updateScore(int score);
    void printDiscards();
};

#endif
