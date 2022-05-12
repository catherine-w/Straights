#ifndef _CARD_H_
#define _CARD_H_

#include <ostream>
#include <istream>
#include <string>
using namespace std;

class Card {

  public:
    Card(string, string); // creates a card
    string getSuit() const; // returns suit as a string
    string getRank() const; // returns rank as a string
    int getValue() const;

  private:
    string suit;
    string rank;
};

bool operator==(const Card &, const Card &); // returns true if 2 cards are identical in suit and rank
std::istream &operator>>(std::istream &, Card &); // reads into a Card
std::ostream &operator<<(std::ostream &, const Card &); // outputs Card to standard output

#endif
