#include "Deck.hpp"

Deck::Deck() {
  for(int i=0; i<NOTHX_NB_CARD; i++){
    indexes[i] = i;
    cards[i].setValue(i+3);
  }
  shuffle();
  top = 0;
}

Deck::~Deck() {

}

bool Deck::isEmpty() {
  return top == (NOTHX_NB_CARD-1);
}

const Card& Deck::next() {
  return cards[indexes[top++]];
}

const Card& Deck::top(){
  return cards[indexes[top]];
}

void Deck::shuffle() {
  int randomIndex;

  for(int i=NOTHX_NB_CARD-1; i>0; i--) {
    randomIndex = std::rand()%(i+1);
    std::swap(indexes[i], indexes[randomIndex]);
  }
}
