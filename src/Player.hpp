#ifndef NOTHANKS_PLAYER_HPP
#define NOTHANKS_PLAYER_HPP

#include <set>

#include "Definitions.hpp"
#include "Logger.hpp"
#include "Action.hpp"

class Player {
public:
  Player();

  virtual ~Player();  
  virtual Action play() = 0;

  int getCards() const;
  int getChips() const;
  

private:
  int chips;
  std::set<int> cards;
};

#endif
