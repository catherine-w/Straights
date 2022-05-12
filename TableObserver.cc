#include <iostream>
#include <memory>
#include "TableObserver.h"
using namespace std;

TableObserver::TableObserver(shared_ptr<Table> subject) : subject{subject} {
    subject->attach(this);
}


void TableObserver::notify() {
    map<string, shared_ptr<vector<string>>> temp = subject->getState();
    cout << "Cards on the table:" << endl;
    cout << "Clubs:";
    for (size_t i = 0; i < temp["C"]->size(); i++) {
        cout << " " << temp["C"]->at(i);
    }
    cout << endl;

    cout << "Diamonds:";
    for (size_t i = 0; i < temp["D"]->size(); i++) {
        cout << " " << temp["D"]->at(i);
    }
    cout << endl;

    cout << "Hearts:";
    for (size_t i = 0; i < temp["H"]->size(); i++) {
        cout << " " << temp["H"]->at(i);
    }
    cout << endl;

    cout << "Spades:";
    for (size_t i = 0; i < temp["S"]->size(); i++) {
        cout << " " << temp["S"]->at(i);
    }
    cout << endl;
}

TableObserver::~TableObserver() {
    subject->detach(this);
}
