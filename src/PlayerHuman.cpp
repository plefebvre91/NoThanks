#include "PlayerHuman.hpp"

PlayerHuman::PlayerHuman(){
}

PlayerHuman::~PlayerHuman() {
}


Action PlayerHuman::play() {
  Action action = ACT_NOTHING;
  Logger::get().info("Calcul de l'action : play()");
  int a;
  std::cin >> a;

  switch(a){
  case 0: action = ACT_NOTHING; break;
  case 1: action = ACT_TAKE_CHIPS; break;
  case 2: action = ACT_GIVE_A_CHIP; break;
  }
  return action;
}
