#ifndef NOTHANKS_HPP
#define NOTHANKS_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "Definitions.hpp"
#include "Player.hpp"
#include "PlayerHuman.hpp"
#include "PlayerRandom.hpp"
#include "PlayerAverage.hpp"
#include "Deck.hpp"
#include "Logger.hpp"
#include "Action.hpp"
#include "Card.hpp"
#include "Network.hpp"

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
  /**
   * \return true if there is no more card in deck
   */
  bool gameIsFinished() const;

  /**
   * A player move
   */
  void execute(const Action& action, Player& player);
  
  /**
   * Compute scores
   */
  void updateScores();
  
  /**
   * Information about game
   */
  void display();  

  /**
   * Select the next player
   */
  void selectNextPlayer();

  /**
   * Show players scores
   */
  void showScores() const;


  // Current player index
  int currentPlayer;

  // Chips put on table
  int chipsOnTable;

  // Nb of Players
  int nbPlayers;
  
  // Players scores
  std::vector<int> scores;
  
  // Visible card on deck
  Card cardOnTop;
  
  // Deck
  Deck deck;  
  
  // Players
  std::vector<Player*> players;
};
#endif
