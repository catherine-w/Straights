#include "Card.h"
#include <string>
using namespace std;

// returns Card with declared suit and rank
Card::Card(string suit, string rank): suit{suit}, rank{rank} {}

string Card::getSuit() const {
    return suit;
}

string Card::getRank() const {
    return rank;
}

int Card::getValue() const {
    if (this->getRank() == "A") {
        return 1;
    }
    else if (this->getRank() == "T") {
        return 10;
    }
    else if (this->getRank() == "J") {
        return 11;
    }
    else if (this->getRank() == "Q") {
        return 12;
    }
    else if (this->getRank() == "K") {
        return 13;
    }
    else {
        return stoi(this->getRank());
    }
}

// returns true if 2 cards are identical in suit and rank
bool operator==(const Card &x, const Card &y) {
    if ((x.getSuit() == y.getSuit()) && (x.getRank() == y.getRank())) {
        return true;
    } else {
        return false;
    }
}

// reads into a Card
std::istream &operator>>(std::istream &in, Card &x) {
    string suits = "CDHS";
    string ranks = "A23456789TJQK";
    string temp;
    in >> temp;

    // check if rank and suit are valid. 
    if ((ranks.find(temp.at(0)) != string::npos) && (suits.find(temp.at(1)) != string::npos) && (temp.length() == 2)) {
        x = Card(string(1,temp.at(1)), string(1,temp.at(0)));
    }
    return in;
}

// prints Card to standard output. for eg "7S"
std::ostream &operator<<(std::ostream &out, const Card &x) {
    out << x.getRank() << x.getSuit();
    return out;
}


