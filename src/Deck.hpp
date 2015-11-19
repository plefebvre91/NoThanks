#ifndef DECK_HPP
#define DECK_HPP

#include <utility>
#include <ctime>
#include <cstdlib>

#include "Definitions.hpp"
#include "Card.hpp"

class Deck {
public:
  //Constructor/Destructor
  Deck();
  ~Deck();
  
  //Returns true if all card have been played
  bool isEmpty();

  //Returns the last removed tile index 
  const Card& getNext();
  
private:
  void shuffle();
  Card cards[NOTHX_NB_CARD];
  int indexes[NOTHX_NB_CARD];
  int top;
};

#endif
