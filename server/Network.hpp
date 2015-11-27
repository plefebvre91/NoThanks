#ifndef NOTHX_NETWORK_HPP
#define NOTHX_NETWORK_HPP

#include "Logger.hpp"
#include "Parser.hpp"
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"

#include <iostream>

namespace network {

  typedef websocketpp::server<websocketpp::config::asio> server;
  static server s;
  static std::string received;
  static websocketpp::connection_hdl handler;
  static Info conf;
  
  void run();
  void stop();
  void on_message(websocketpp::connection_hdl h, server::message_ptr m);
  void send(std::string& msg);
  void get_data();
};
#endif
