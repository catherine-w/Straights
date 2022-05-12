#ifndef _COMPUTERPLAYER_H_
#define _COMPUTERPLAYER_H_

#include <vector>
#include "Player.h"

class ComputerPlayer : public Player {
public:
    pair<string, shared_ptr<Card>> choosePlay() override;
    ComputerPlayer(int id, shared_ptr<Table> table);
    ComputerPlayer(int id, shared_ptr<Table> table, int score, vector<shared_ptr<Card>> hand, vector<shared_ptr<Card>> discards); // creates new Computer Player
};

#endif
