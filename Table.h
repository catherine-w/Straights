#ifndef _TABLE_H
#define _TABLE_H

#include <memory>
#include <vector>
#include <map>
#include <string>
#include "Subject.h"
#include "Card.h"
using namespace std;

class Table : public Subject {
private:
    shared_ptr<Card> recentCard;
    map<string, shared_ptr<vector<string>>> tableCards;
public:
    Table(); // default constructor
    void addCard(string suit, shared_ptr<Card> c);
    bool isLegalPlay(shared_ptr<Card> c);
    bool isEmptyTable();
    void clearTable();
    void printTable();
    map<string, shared_ptr<vector<string>>> getState(); // returns instance of table
};

#endif