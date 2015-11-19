#include "PlayerHuman.hpp"

PlayerHuman::PlayerHuman(){
}

PlayerHuman::~PlayerHuman() {
}


Action PlayerHuman::play(const Card& card) {
  Action action = ACT_NOTHING;
  Logger::get().info("Calcul de l'action : play()");
  int a;

  std::cout << "1 : prendre la carte et les jetons" << std::endl;
  std::cout << "2 : donner un jeton" << std::endl;

  std::cin >> a;

  switch(a){
  case 1: action = ACT_TAKE_CHIPS; break;
  case 2: action = ACT_GIVE_A_CHIP; break;
  }
  return action;
}
