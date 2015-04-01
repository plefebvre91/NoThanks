#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Definitions.hpp"
#include <bitset>

class Player {
public:
  //Constructor/Destructor
  Player();
  ~Player();

  int getCards();
  int getChips();
  int getScore();

private:
  std::bitset<NOTHX_NB_CARD> cards; 
  int chips;
};

#endif
