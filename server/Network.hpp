#ifndef NOTHX_NETWORK_HPP
#define NOTHX_NETWORK_HPP

#include "Logger.hpp"
#include "Parser.hpp"
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"

#include <iostream>

typedef websocketpp::server<websocketpp::config::asio> server;

static server s;
static std::string received;
static websocketpp::connection_hdl handler;

void network_run();
void on_message(websocketpp::connection_hdl h, server::message_ptr msg);
void network_send(std::string& msg);
NetworkMessage network_get_last_data();


#endif
