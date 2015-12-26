#include "Player.hpp"

using namespace rapidjson;

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
  std::cout << "JSON:" << toJson() << std::endl;
}

bool Player::adjacentCardIsFound(const Card& card) const {
  std::set<int>::iterator pred = cards.find(card.getValue() - 1);
  std::set<int>::iterator succ = cards.find(card.getValue() + 1);
					    
  return (pred != cards.end() || succ != cards.end());
}


int Player::getScore() const {
  return score;
}

void Player::setScore(int s) {
  score = s;
}

std::string Player::toJson() const {  
  StringBuffer s;
  Writer<StringBuffer> writer(s);
  
  writer.StartObject();
  
  writer.String(JSON_KEY_NAME);
  writer.String(name.c_str());

  writer.String(JSON_KEY_SCORE);
  writer.Uint(score);
  
  writer.String(JSON_KEY_COINS);
  writer.Uint(chips);
  
  writer.String(JSON_KEY_CARDS);
  
  writer.StartArray();
  for (auto card : cards) {
    writer.Uint(card);
  }
  writer.EndArray();
  
  writer.EndObject();
  
  return s.GetString();
}
