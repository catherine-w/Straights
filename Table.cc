#include "Table.h"
#include "Card.h"
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

Table::Table(): recentCard{make_shared<Card>("S", "7")} {
    tableCards["C"] = make_shared<vector<string>>();
    tableCards["D"] = make_shared<vector<string>>();
    tableCards["H"] = make_shared<vector<string>>();
    tableCards["S"] = make_shared<vector<string>>();
}

void Table::addCard(string suit, shared_ptr<Card> c) {
    tableCards[suit]->push_back(c->getRank());
    // sort into ascending order
    sort(tableCards[suit]->begin(), tableCards[suit]->end());
    recentCard = c;
}

void Table::printTable() {
    cout<<"notify"<<endl;
    notifyObservers();
}


bool Table::isLegalPlay(shared_ptr<Card> c) {
    string suit = c->getSuit();
    int rank = c->getValue();
    int rankvalue;

    if (rank == 7) {
        return true;
    }

    for (size_t i = 0; i < tableCards[suit]->size(); i++) {
        if (tableCards[suit]->at(i) == "A") {
            rankvalue = 1;
        } else if (tableCards[suit]->at(i) == "T") {
            rankvalue = 10;
        } else if (tableCards[suit]->at(i) == "J") {
            rankvalue = 11;
        } else if (tableCards[suit]->at(i) == "Q") {
            rankvalue = 12;
        } else if (tableCards[suit]->at(i) == "K") {
            rankvalue = 13;
        } else {
            rankvalue = stoi(tableCards[suit]->at(i));
        }
        if (rankvalue == (rank + 1) || rankvalue == (rank - 1)) {
            return true;
        }
    }
    return false;
}

bool Table::isEmptyTable() {
    return tableCards["C"]->size() == 0 && tableCards["D"]->size() == 0 &&tableCards["H"]->size() == 0 && tableCards["S"]->size() == 0;
}

void Table::clearTable() {
    for (auto i : tableCards) {
        i.second->clear();
    }
}

map<string, shared_ptr<vector<string>>> Table::getState() {
    return tableCards;
}
