#ifndef NOTHANKS_PLAYER_HPP
#define NOTHANKS_PLAYER_HPP

#include <set>

#include "Definitions.hpp"
#include "Logger.hpp"
#include "Action.hpp"
#include "Card.hpp"

class Player {
public:
  Player();

  virtual ~Player();  
  virtual Action play(const Card& card) = 0;

  int getCards() const;
  
  // accesseurs
  int getNbChips() const;
  bool hasChips() const;
  
  // modifieurs
  void drop();
  void take(int chips, int card);
  void setName(std::string str);
  const std::string& getName() const;
  
  void info() const;

private:
  int chips;
  std::set<int> cards;
  std::string name;
};

#endif