#ifndef NOTHANKS_HPP
#define NOTHANKS_HPP
#include <iostream>

#include "Definitions.hpp"
#include "Player.hpp"
#include "Deck.hpp"
#include "Logger.hpp"

class NoThanks {
public:
  NoThanks();
  ~NoThanks();
  void run();

private:
  bool gameIsFinished() const;
  void execute();
  void display();


  Deck deck;
  Player player[NOTHX_NB_PLAYERS_MAX];
};
#endif
