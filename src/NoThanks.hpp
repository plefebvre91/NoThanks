#ifndef NOTHANKS_HPP
#define NOTHANKS_HPP
#include <iostream>

#include "Definitions.hpp"
#include "Player.hpp"
#include "PlayerHuman.hpp"
#include "Deck.hpp"
#include "Logger.hpp"
#include "Action.hpp"

/**
 * Main class
 */

class NoThanks {
public:
  /**
   * Constructor
   */
  NoThanks();

  /**
   * Destructor
   */
  ~NoThanks();

  /**
   * Main loop
   */
  void run();

private:
  bool gameIsFinished() const;
  void execute(const Action& action);
  void display();  
  void selectNextPlayer();
  
  int currentPlayer;
};
#endif
