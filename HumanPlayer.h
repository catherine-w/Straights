#ifndef _HUMANPLAYER_H_
#define _HUMANPLAYER_H_

#include <vector>
#include <iostream>
#include "Player.h"

class HumanPlayer : public Player {
public:
    pair<string, shared_ptr<Card>> choosePlay() override;
    HumanPlayer(int id, shared_ptr<Table> table); // constructs new Human Player
};

#endif