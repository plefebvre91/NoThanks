#include <iostream>

#define SERVER_TEST 1

#ifdef SERVER_TEST
#include "MockGame.hpp"
#else
#include "NoThanks.hpp"
#endif

#include "server_ws.hpp"

typedef SimpleWeb::SocketServer<SimpleWeb::WS> WsServer;

using namespace SimpleWeb;

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  //WebSocket (WS)-server at port 8080 using 2 threads
  WsServer server(8080, 2);
  auto& echo=server.endpoint["^/$"];
  
#ifdef SERVER_TEST
  MockGame* app = nullptr;
#else
  NoThanks* app = nullptr;
#endif

  // Randomize
  srand(time(0));
    
  echo.onmessage=[&server,&app](std::shared_ptr<WsServer::Connection> connection, std::shared_ptr<WsServer::Message> message) {
    if(app == nullptr){
      std::vector<std::string> names;
      names.push_back("Ahmed");
      names.push_back("Lisa");
      
#ifdef SERVER_TEST
      app = new MockGame(2, names);
#else
      app = new NoThanks(2, names);
#endif
    }
    
    auto message_str=message->string();
    //std::cout << "WS Server: Message received: \"" << message_str << "\" from " << (size_t)connection.get() << std::endl;
    //  std::cout << "WS Server: Sending message \"" << app->getJSON() <<  "\" to " << (size_t)connection.get() << std::endl;
    
    auto send_stream=std::make_shared<WsServer::SendStream>();
    //    *send_stream << message_str;

    app->run();
    *send_stream << app->getJSON();
    server.send(connection, send_stream, [](const boost::system::error_code& ec){
	if(ec) {
	  std::cout << "Server: Error sending message: " << ec << ", error message: " << ec.message() << std::endl;
	}
      });

    
    while(!app->currentPlayerIsAComputer()){
      auto send_stream=std::make_shared<WsServer::SendStream>();
      app->run();
      *send_stream << app->getJSON();
      server.send(connection, send_stream, [](const boost::system::error_code& ec){
	  if(ec) {
	    std::cout << "Server: Error sending message: " << ec << ", error message: " << ec.message() << std::endl;
	  }
	});
      sleep(1);
    }

    
    
  };
    
  echo.onopen=[](std::shared_ptr<WsServer::Connection> connection) {
    std::cout << "Server: Opened connection " << (size_t)connection.get() << std::endl;
  };
    
  //See RFC 6455 7.4.1. for status codes
  echo.onclose=[](std::shared_ptr<WsServer::Connection> connection, int status, const std::string& reason) {
    (void)reason;
    std::cout << "Server: Closed connection " << (size_t)connection.get() << " with status code " << status << std::endl;
  };
    
  //See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
  echo.onerror=[](std::shared_ptr<WsServer::Connection> connection, const boost::system::error_code& ec) {
    std::cout << "Server: Error in connection " << (size_t)connection.get() << ". " << 
    "Error: " << ec << ", error message: " << ec.message() << std::endl;
  };
  
  std::thread server_thread([&server](){
      std::cout << "Waiting for connections..." << std::endl;
      server.start();
    });
    
  //Wait for server to start so that the client can connect
  std::this_thread::sleep_for(std::chrono::seconds(1));
  
  server_thread.join();
    
  return 0;
}
