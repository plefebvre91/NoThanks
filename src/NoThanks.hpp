#ifndef NOTHANKS_HPP
#define NOTHANKS_HPP
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Definitions.hpp"
#include "Player.hpp"
#include "PlayerHuman.hpp"
#include "Deck.hpp"
#include "Logger.hpp"
#include "Action.hpp"
#include "Card.hpp"

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
  void execute(const Action& action, Player& player);
  void display();  
  void selectNextPlayer();
  
  int currentPlayer;
  int chipsOnTable;
  
  Card cardOnTop;
  Deck deck;
  
  
  
};
#endif
