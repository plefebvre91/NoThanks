#include "Network.hpp"

void network_run() {
  s.set_message_handler(&on_message);
  s.init_asio();
  s.listen(9001);
  s.start_accept();
  s.run();
}

void on_message(websocketpp::connection_hdl hdl, server::message_ptr msg){
  Logger::get().info("From client : " + msg->get_payload());
  std::string s(msg->get_payload());
  received.assign(s);
  handler = hdl;
}
  
void network_send(std::string& msg) {
  s.send(handler, msg, websocketpp::frame::opcode::text);  
}


NetworkMessage network_get_last_data() {
  Parser parser;
  NetworkMessage nm = parser.get(received);
  
  return nm;
}
  

