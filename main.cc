#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <random>
#include "Table.h"
#include "Game.h"
#include "TableObserver.h"
#include <chrono>
using namespace std;

int main(int argc, char* argv[]) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    if (argc == 2) {
        try{
            seed = stoi(argv[1]);
        } catch(invalid_argument & e ) {
            cerr <<"Please enter valid input: "<< e.what() << " error occured." << endl;
            return 1;
        }
    } else if (argc > 2) {
        cout << "You have entered too many arguments. Please enter 1 integer seed value or nothing" << endl;
        return 0;
    }

    // initialize game settings
    unsigned int s = (unsigned int) seed;
    std::default_random_engine rng{s};
    shared_ptr<Game> g = make_shared<Game>(rng);
    shared_ptr<Table> table = g->getTable();
    shared_ptr<TableObserver> text = make_shared<TableObserver>(table);

    g->startGame();

    while(!g->isGameOver()) {
        g->newRound();
        if(g->isQuitGame()) {
            return 0;
        }
        g->printRoundResults();

        if (g->isGameOver()) {
            g->printWinners();
        }
    }

    return 0;
}