#include "Game.h"
#include "Table.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include <iostream>
#include <vector>
#include <random>
#include <memory>

Game::Game(std::default_random_engine rng): rng{rng} {
    deck = make_shared<Deck>(rng);
    table = make_shared<Table>();
}

int Game::getCurrentPlayer() const {
    return currentPlayer;
}

void Game::firstTurn(int player) {
    currentPlayer = player;
    playTurn();
}

bool Game::isQuitGame() {
    return quitGame;
}

void Game::playTurn() {
    // check if round is done
    if (isroundDone()) {
        return;
    }
    if (showTable) {
        table->notifyObservers(); // print table
    }
    pair<string, shared_ptr<Card>> command;
    command = players[currentPlayer]->choosePlay();
    if (command.first == "play") {
        players[currentPlayer]->playCard(command.second);
    } else if (command.first == "discard") {
        players[currentPlayer]->discardCard(command.second);
    } else if (command.first == "ragequit") {
        vector<shared_ptr<Card>> hand = players[currentPlayer]->getHand();
        vector<shared_ptr<Card>> discards = players[currentPlayer]->getDiscards();
        int score = players[currentPlayer]->getTotalScore();
        shared_ptr<Player> newPlayer = make_shared<ComputerPlayer>(currentPlayer, table, score, hand, discards);
        players[currentPlayer] = newPlayer;
        showTable = false;
        cout << "Player" << currentPlayer + 1 << " ragequits. A computer will now take over." << endl;
        playTurn(); // again for computer. 
    } else if (command.first == "deck") {
        deck->print();
        showTable = false;
        playTurn();
    } else if (command.first == "quit") {
        quitGame = true;
        return;
    }
    
    if (isroundDone()) {
        // round done
        return;
    }
    if (currentPlayer == 3) {
        currentPlayer = 0;
    } else {
        currentPlayer++;
    }
    showTable = true;
    playTurn();
}

void Game::setPlayers() {
    string temp;
    for (int i = 0; i <= 3; i++) {
        bool valid = false;
        cout << "Is Player" << i + 1 << " a human (h) or computer (c)?" << endl;
        cout << ">";
        while(valid == false) {
        getline(cin, temp);
        if (temp == "h"){
            players.emplace_back(make_shared<HumanPlayer>(i, table));
            valid = true;
        } else if (temp == "c"){
            players.emplace_back(make_shared<ComputerPlayer>(i, table));
            valid = true;
        } else {
            cout << "Please enter a valid player type (h) or (c)"<< endl;
            cout << ">";
            valid = false;
        }
        }
    }
}

void Game::startGame() {
    deck = make_shared<Deck>(rng);
    setPlayers();
}

void Game::newRound() {
    clearRound();
    deck->shuffle();
    dealCards();

    int firstPlayer = 0;
    for (int i = 0; i < 4; i++) {
        if (players[i]->has7S()) {
            firstPlayer = i;
        }
    }
    cout << "A new round begins. It's Player" << firstPlayer + 1 << "'s turn to play." << endl;
    firstTurn(firstPlayer);
}

void Game::updateMaxScore() {
    for (size_t i = 0; i < players.size(); i++) {
        int currentScore = players[i]->getTotalScore() + players[i]->getDiscardScore();
        if (currentScore > maxScore) {
            maxScore = currentScore;
        }
    }
}

int Game::getMaxScore(){
    return maxScore;
}

bool Game::isroundDone() {
    updateMaxScore();
    for (size_t i = 0; i < players.size(); i++) {
        if (!players[i]->handEmpty()) {
            return false;
        }
    }
    return true;
}

void Game::printRoundResults() {
    for (size_t i = 0; i < players.size(); i++) {
        cout << "Player" << i + 1 << "'s discards:";
        players[i]->printDiscards();
        cout << "Player" << i + 1 << "'s score: ";
        int newtotal = players[i]->getTotalScore() + players[i]->getDiscardScore();
        cout << players[i]->getTotalScore() << " + " << players[i]->getDiscardScore() << " = " << newtotal << endl;
        players[i]->updateScore(newtotal);
    }
}

void Game::printWinners() {
    int minScore = 81; // anything above 80 is fine
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i]->getTotalScore() < minScore) {
            minScore = players[i]->getTotalScore();
        }
    }

    for (size_t i = 0; i < players.size(); i++) {
        if (players[i]->getTotalScore() == minScore) {
            cout << "Player" << i + 1 << " wins!" << endl;
        }
    }
}

void Game::clearRound() {
    for(size_t i = 0; i < players.size();i++){
        players[i]->clearCards();
    }
    table->clearTable();
}

void Game::dealCards() {
    for (int i = 0; i < 13; i++) {
        players[0]->dealCard(deck->getCard(i));
    }
    for (int i = 13; i < 26; i++) {
        players[1]->dealCard(deck->getCard(i));
    }
    for (int i = 26; i < 39; i++) {
        players[2]->dealCard(deck->getCard(i));
    }
    for (int i = 39; i < 52; i++) {
        players[3]->dealCard(deck->getCard(i));
    }
}

int Game::findFirstPlayer() {
    int firstPlayer = 0;
    for (int i = 0; i < 4; i++) {
        if (players[i]->has7S()) {
            firstPlayer = i;
        }
    }
    return firstPlayer;
}

bool Game::isGameOver() {
    if (getMaxScore() >= 80) {
        return true;
    } else {
        return false;
    }
}

shared_ptr<Table> Game::getTable() {
    return table;
}
