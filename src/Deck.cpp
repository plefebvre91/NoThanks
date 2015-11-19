#include "Deck.hpp"

Deck::Deck() {
  for(int i=0; i<NOTHX_NB_CARD; i++){
    deck[i] = i+1;
  }
  shuffle();

  topIndex = 0;

}

Deck::~Deck() {

}

bool Deck::isEmpty() {
  return topIndex == (NOTHX_NB_CARD-1);
}



void Deck::shuffle() {
  int randomIndex;

  for(int i=NOTHX_NB_CARD-1; i>1; i--) {
    randomIndex = std::rand()%(i+1);
    std::swap(deck[i], deck[randomIndex]);
  }
}
