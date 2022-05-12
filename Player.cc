#include "Player.h"
#include "Card.h"
#include <vector>
#include <iostream>

using namespace std;

// Player defualt constructor
Player::Player(int id, shared_ptr<Table> table): id{id}, table{table} {}

// Player copy constructor
Player::Player(int id, shared_ptr<Table> table, int score, vector<shared_ptr<Card>> hand, vector<shared_ptr<Card>> discards) 
: id{id}, table{table}, totalScore{score}, hand{hand}, discards{discards}{}

void Player::playCard(shared_ptr<Card> c) {
    for (size_t i = 0; i < hand.size(); i++) {
        if (*hand[i] == *c) {
            hand.erase(hand.begin()+i);
            break;
        }
    }
    table->addCard(c->getSuit(), c);
}

void Player::discardCard(shared_ptr<Card> c) {
    for (size_t i = 0; i < hand.size(); i++) {
        if (*hand[i] == *c) {
            hand.erase(hand.begin()+i);
            break;
        }
    }
    discards.push_back(c);
}

void Player::clearCards() {
    hand.clear();
    discards.clear();
    legalMoves.clear();
}

void Player::updateLegalMoves() {
    legalMoves.clear(); // reconstructs legalMoves

    // case 1: first turn. only legal move is 7S
    if (table->isEmptyTable()) {
        for (size_t i = 0; i < hand.size(); i++) {
            if (hand[i]->getSuit() == "S" && hand[i]->getRank() == "7") {
                legalMoves.emplace_back(hand[i]);
                return;
            }
        }
    }

    // other rules: any 7 is legal. adjacent cards are legal.
    for (size_t i = 0; i < hand.size(); i++) {
        if (table->isLegalPlay(hand[i])) {
            legalMoves.emplace_back(hand[i]);
        }
    }
}

bool Player::has7S() {
    for (size_t i = 0; i < hand.size(); i++) {
        if (hand[i]->getSuit() == "S" && hand[i]->getRank() == "7") {
            return true;
        }
    }
    return false;
}

void Player::dealCard(shared_ptr<Card> c) {
    hand.push_back(c);
}

int Player::getPlayerID() const{
    return id;
}

int Player::getTotalScore() const {
    return totalScore;
}

std::vector<shared_ptr<Card>> Player::getHand() const {
    return hand;
}

std::vector<shared_ptr<Card>> Player::getDiscards() const {
    return discards;
}

std::vector<shared_ptr<Card>> Player::getLegalMoves() const {
    return legalMoves;
}

void Player::printDiscards() {
    for (size_t i = 0; i < discards.size(); i++) {
        std::cout << " " << *discards[i];
    }
    std::cout << std::endl;
}

int Player::getDiscardScore() const {
    int score = 0;
    for (size_t i = 0; i < discards.size(); i++) {
        score += discards[i]->getValue();
    }
    return score;
}

bool Player::handEmpty() {
    if (hand.size() == 0) {
        return true;
    } else {
        return false;
    }
}

void Player::updateScore(int score) {
    totalScore = score;
}