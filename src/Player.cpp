#include "Player.hpp"

Player::Player():cards(),name() {
  chips = NOTHX_NB_CHIPS;
}

Player::~Player() {
  
}

int Player::getNbChips() const {
  return chips;
}

bool Player::hasChips() const {
  return (chips > 0);
}

void Player::drop() {
  --chips;
}


void Player::take(int chips, int card) {
  this->chips += chips;
  this->cards.insert(card);
}

void Player::setName(std::string str) {
  name = str;
}

void Player::info() const {
  std::cout << "Joueur " << name << " a " << chips << " jetons\n";
  std::cout << "Cartes: ";
  for(auto c : cards) {
    std::cout << c << " - ";
  }
  std::cout << std::endl;
}
