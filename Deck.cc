#include "Deck.h"
#include <random>
#include <string>
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include <iostream>
using namespace std;

// constructs deck of 52 cards in correct inital order
Deck::Deck(std::default_random_engine rng) : rng(rng) {
    string suits = "CDHS";
    string ranks = "A23456789TJQK";

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            shared_ptr<Card> x(new Card(string(1,suits.at(i)), string(1,ranks.at(j))));
            cards.push_back(x);
        }
    }
}

void Deck::shuffle() {
    std::shuffle(cards.begin(), cards.end(), rng);
}

void Deck::print() {
    for (int i = 1; i <= 52; i++) {
        cout << *cards[i - 1] << ' '; 
        if (i % 13 == 0) {
            cout << endl;
        }
    }
}

shared_ptr<Card> Deck::getCard(int pos) {
    return cards.at(pos);
}
