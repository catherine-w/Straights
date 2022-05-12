#include "ComputerPlayer.h"
#include <vector>
#include <iostream>
#include <string>

ComputerPlayer::ComputerPlayer(int id, shared_ptr<Table> table) : Player(id, table) {}

ComputerPlayer::ComputerPlayer(int id, shared_ptr<Table> table, int score, vector<shared_ptr<Card>> hand, vector<shared_ptr<Card>> discards) 
: Player(id, table, score, hand, discards) {}

// return pair to communicate to Game class whether you play or discard a card, as well as which card.
pair<string, shared_ptr<Card>> ComputerPlayer::choosePlay() {
    updateLegalMoves();
    cout << "Your Hand:";
    for (size_t i = 0; i < hand.size(); i++) {
        cout << " " << *(hand.at(i)); 
    }
    cout << endl;
    cout << "Legal plays:";
    for (size_t i = 0; i < legalMoves.size(); i++) {
        cout << " " << *(legalMoves.at(i));
    }
    cout << endl;
    cout << ">";
    if (legalMoves.size() > 0) {
        // play first card in legalMoves vector
        cout << "Player"<< id + 1 << " plays " << *legalMoves[0] << "." << endl;
        return make_pair("play", legalMoves[0]);
    } else {
        // discard first card in hand
        cout << "Player"<< id + 1 << " discards " << *hand[0] << "." << endl;
        return make_pair("discard", hand[0]);
    }
}