#ifndef NOTHX_NETWORK_HPP
#define NOTHX_NETWORK_HPP

#include <iostream>
#include <cstdio>

#include "Logger.hpp"
#include "Parser.hpp"
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

using namespace rapidjson;

typedef websocketpp::server<websocketpp::config::asio> server;

class Network {
public:
  Network();  
  void run();  
  
  static std::string received = "lol";
  static websocketpp::connection_hdl handler;
  

  static void on_message(websocketpp::connection_hdl hdl, server::message_ptr msg) {
    Logger::get().info("From client : " + msg->get_payload());
    std::string s(msg->get_payload());
    received.assign(s);
    handler = hdl;
  }


  void sendMessage(websocketpp::connection_hdl& hdl, std::string& msg);
  
  NetworkMessage getLastData() const {
    Parser parser;
    NetworkMessage nm = parser.get(received);
    return nm;
  }
  
private:
  server s;

};

#endif
