#include "Network.hpp"

namespace network {

  void run() {
    s.set_message_handler(&on_message);
    s.init_asio();
    s.listen(9001);
    s.start_accept();
    s.run();
  }

  void stop() {
    s.stop();
  }

  void on_message(websocketpp::connection_hdl hdl, server::message_ptr msg){
    Logger::get().info("From client : " + msg->get_payload());
    //    std::string s(msg->get_payload());
    //    received.assign(s);
    handler = hdl;
    std::string m = "{lol}";
    network::conf.is_fresh = true;
    s.send(hdl, m, websocketpp::frame::opcode::text);  
  }
  
  void send(std::string& msg) {
    s.send(handler, msg, websocketpp::frame::opcode::text);  
  }


  void get_data() {

    conf = parser.get(received);
  }
  
}//namespace
