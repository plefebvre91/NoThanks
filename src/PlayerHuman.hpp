#ifndef NOTHANKS_PLAYER_HUMAN_HPP
#define NOTHANKS_PLAYER_HUMAN_HPP

#include "Player.hpp"
#include "Definitions.hpp"

class PlayerHuman : public Player {
public:
  PlayerHuman();

  virtual ~PlayerHuman();  
  virtual Action play();
};

#endif
