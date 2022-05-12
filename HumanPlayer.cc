#include "HumanPlayer.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

HumanPlayer::HumanPlayer(int id, shared_ptr<Table> table) : Player(id, table) {}

/// return pair to communicate to Game class whether you play or discard a card, as well as which card.
pair<string, shared_ptr<Card>> HumanPlayer::choosePlay() {
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
    string temp,command;
    Card c("temp", "temp");

    while(true) {  
        getline(cin, temp);
        stringstream ss1{temp};
        ss1 >> command; 

        if (command == "play") {
            ss1 >> c; // Card c updated with new value  
            if (legalMoves.size() > 0) {
                for (size_t i = 0; i < legalMoves.size(); i++) {
                    if (*legalMoves[i] == c) {
                        // valid move
                        cout << "Player"<< id + 1 << " plays " << c << "." << endl;
                        shared_ptr<Card> temp = make_shared<Card>(c.getSuit(), c.getRank());
                        return make_pair("play", temp);
                    }
                }
                cout << "This is not a legal play." << endl;
                cout << ">";
                continue;
            } else {
                cout << "This is not a legal play." << endl;
                cout << ">";
                continue;
            }
        } else if (command == "discard") {
            ss1 >> c; // Card c updated with new value  
            if (legalMoves.size() == 0) {
                for (size_t i = 0; i < hand.size(); i++) {
                    if (*hand[i] == c) {
                        cout << "Player"<< id + 1 << " discards " << c << "." << endl;
                        shared_ptr<Card> temp = make_shared<Card>(c.getSuit(), c.getRank());
                        return make_pair("discard", temp);
                    }
                }
                cout << "You do not own this card. You cannot discard." << endl;
                cout << ">";
                continue;
            } else if (legalMoves.size() > 0){
                cout << "You have a legal play. You may not discard." << endl;
                cout << ">";
                continue;
            } else {
                cout << "This is not a legal play." << endl;
                cout << ">";
                continue;
            }
        } else if (command == "ragequit") {
            return make_pair("ragequit", make_shared<Card>("0", "0"));
        } else if (command == "deck") {
            return make_pair("deck", make_shared<Card>("0", "0"));
        } else if (command == "quit") {
            return make_pair("quit", make_shared<Card>("0", "0"));
        } else {
            cout << "This is not a valid command"<< endl;
            cout << ">";
        }
    }
}