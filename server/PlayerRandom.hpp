#ifndef NOTHANKS_PLAYER_RANDOM_HPP
#define NOTHANKS_PLAYER_RANDOM_HPP

#include "Player.hpp"
#include "Definitions.hpp"

/**
 * Randomly playing player class. Implements Player class.
 */

class PlayerRandom : public Player {
public:
  /**
   * Constructor
   */
  PlayerRandom();

  /**
   * Destructor
   */
  virtual ~PlayerRandom();  

  /**
   * Choose the move to play
   */
  virtual Action play(const Card& card);
};

#endif
