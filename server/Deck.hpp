#ifndef DECK_HPP
#define DECK_HPP

#include <utility>
#include <ctime>
#include <cstdlib>

#include "Definitions.hpp"
#include "Card.hpp"

class Deck {
public:

  /**
   * Constructor
   */
  Deck();
  
  /**
   * Constructor
   */
  ~Deck();
  
  /**
   * \return true if all card have been played
   */
  bool isEmpty() const;
  
  /**
   * \return the next card to play
   */
  const Card& next();

  /**
   * \return the currently played card
   */
  const Card& first();

  
private:
  /**
   * Shuffle the indexes array
   */
  void shuffle();

  // Cards
  Card cards[NOTHX_NB_CARD];

  // Card order after shuffling
  int indexes[NOTHX_NB_CARD];
  
  // Index of top-card
  int top;
};

#endif
