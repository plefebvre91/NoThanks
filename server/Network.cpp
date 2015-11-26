#include "Network.hpp"

Network::Network():s(){}

void Network::run() {
  s.set_message_handler(&on_message);
  s.init_asio();
  s.listen(9001);
  s.start_accept();
  s.run();
}
  
void Network::sendMessage(websocketpp::connection_hdl& hdl, std::string& msg) {
  s.send(handler, msg, websocketpp::frame::opcode::text);  
}


