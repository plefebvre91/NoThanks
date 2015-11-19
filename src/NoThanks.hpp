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
   /**
    * \return true if there is no more card in deck
    */
   bool gameIsFinished() const;

   /**
    * A player move
    */
   void execute(const Action& action, Player& player);

   /**
    * Information about game
    */
   void display();  

   /**
    * Select the next player
    */
   void selectNextPlayer();

   // Current player index
   int currentPlayer;

   // Chips put on table
   int chipsOnTable;
   int nbPlayers;
  
  // Players scores
  int score[NOTHX_NB_PLAYERS_MAX];
  
  // Visible card on deck
  Card cardOnTop;

  // Deck
  Deck deck;  
  
  Player* players;

};
#endif
