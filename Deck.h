#ifndef _DECK_H_
#define _DECK_H_

#include <vector>
#include <memory>
#include <random>
#include "Card.h"
using namespace std;

class Deck {

public:
    Deck(std::default_random_engine rng); // construct Deck object with seed
    void shuffle(); // shuffle cards
    void print(); // print current Deck of cards
    shared_ptr<Card> getCard(int pos); // accessor function 

private:   
    std::default_random_engine rng;
    vector<shared_ptr<Card>> cards;
};

#endif
