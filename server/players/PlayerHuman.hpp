#ifndef NOTHANKS_PLAYER_HUMAN_HPP
#define NOTHANKS_PLAYER_HUMAN_HPP

#include "Player.hpp"
#include "Definitions.hpp"
#include "Parser.hpp"

/**
 * Human player class. Implements Player class.
 */

class PlayerHuman : public Player {
public:
  /**
   * Constructor
   */
  PlayerHuman();

  /**
   * Destructor
   */
  virtual ~PlayerHuman();  

  /**
   * Choose the move to play
   */
  virtual Action play(const Card& card);
};

#endif
