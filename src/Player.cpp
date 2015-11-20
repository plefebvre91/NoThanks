#include "Player.hpp"

Player::Player():cards(),name() {
  chips = NOTHX_NB_CHIPS;
}

Player::~Player() {
  
}

const std::set<int>& Player::getCards() const {
  return cards;
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

const std::string&  Player::getName() const {
  return name;
}

void Player::info() const {
  std::cout << std::endl;
  std::cout <<  name << " (" << chips << ") : ";
  for(auto c : cards) {
    std::cout << c << " - ";
  }
}

