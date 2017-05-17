#include "server_ws.hpp"
#include "NoThanks.hpp"
#include <map>

using namespace std;

typedef SimpleWeb::SocketServer<SimpleWeb::WS> WsServer;





int main() {  
  std::map<size_t,int> map_id;
  int id = 0;
  
  WsServer server(8080, 2);
  //Example 1: echo WebSocket endpoint
  //  Added debug messages for example use of the callbacks
  //  Test with the following JavaScript:
  //    var ws=new WebSocket("ws://localhost:8080/echo");
  //    ws.onmessage=function(evt){console.log(evt.data);};
  //    ws.send("test");
  auto& echo=server.endpoint["^/echo/?$"];
  
  NoThanks* app = new NoThanks();
  
  echo.onmessage=[&server,&app,&map_id](shared_ptr<WsServer::Connection> connection, shared_ptr<WsServer::Message> message) {
    auto message_str=message->string();
    
    int id =  map_id[(size_t)connection.get()];
    cout <<"ID "<< id << " ("<< (size_t)connection.get()<< ")\n";
    
    string response = app->dispatch(id, message_str);
    
    auto send_stream=make_shared<WsServer::SendStream>();

    *send_stream << response;//message_str;

    //server.send is an asynchronous function
    server.send(connection, send_stream, [](const boost::system::error_code& ec){
	if(ec) {
	  cout << "Server: Error sending message. " <<
	    "Error: " << ec << ", error message: " << ec.message() << endl;
	}
      });
  };
  
  echo.onopen=[&map_id,&id](shared_ptr<WsServer::Connection> connection) {

    map_id[(size_t)connection.get()] = id;
    cout << "Server: nouvelle connexion, client " << id << "("<< (size_t)connection.get() <<")" <<endl;
    id++;
    
  };
    
  //See RFC 6455 7.4.1. for status codes
  echo.onclose=[](shared_ptr<WsServer::Connection> connection, int status, const string& /*reason*/) {
    cout << "Server: Closed connection " << (size_t)connection.get() << " with status code " << status << endl;
  };
    
  //See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
  echo.onerror=[](shared_ptr<WsServer::Connection> connection, const boost::system::error_code& ec) {
    cout << "Server: Error in connection " << (size_t)connection.get() << ". " << 
    "Error: " << ec << ", error message: " << ec.message() << endl;
  };

  thread server_thread([&server](){
      //Start WS-server
      server.start();
    });

  server_thread.join();
      
  return 0;
    
}

#if 0

#include <iostream>
#include "NoThanks.hpp"
#include "server_ws.hpp"

typedef SimpleWeb::SocketServer<SimpleWeb::WS> WsServer;

using namespace SimpleWeb;

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  //WebSocket (WS)-server at port 8080 using 2 threads
  WsServer server(8080, 2);

  auto& echo=server.endpoint["^/$"];
  
  NoThanks* app = nullptr;

  // Randomize
  srand(time(0));
    
  echo.onmessage=[&server,&app](std::shared_ptr<WsServer::Connection> connection,
				std::shared_ptr<WsServer::Message> message) {
#if 0
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


#endif















#if 0
#include <iostream>
#include "NoThanks.hpp"
#include "server_ws.hpp"

typedef SimpleWeb::SocketServer<SimpleWeb::WS> WsServer;

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  //WebSocket (WS)-server at port 8080 using 4 threads
  WsServer server(8080, 4);
  
  // Randomize
  srand(time(0));
  
  //Initializes board game, tiles and window
  NoThanks* app = new NoThanks();

  //Starts game
  app->run();

  //Frees memory
  delete app;

  return 0;
}
    
echo.onmessage=[&server](shared_ptr<WsServer::Connection> connection, shared_ptr<WsServer::Message> message) {
    
  auto message_str=message->string();
  cout << "Server: Message received: \"" << message_str << "\" from " << (size_t)connection.get() << endl;
  cout << "Server: Sending message \"" << message_str <<  "\" to " << (size_t)connection.get() << endl;
        
  auto send_stream=make_shared<WsServer::SendStream>();
  *send_stream << message_str;
    
  server.send(connection, send_stream, [](const boost::system::error_code& ec){
      if(ec) {
	cout << "Server: Error sending message. " <<
	  //See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
	  "Error: " << ec << ", error message: " << ec.message() << endl;
      }
    });
};
    
echo.onopen=[](shared_ptr<WsServer::Connection> connection) {
  cout << "Server: Opened connection " << (size_t)connection.get() << endl;
};
    
//See RFC 6455 7.4.1. for status codes
echo.onclose=[](shared_ptr<WsServer::Connection> connection, int status, const string& reason) {
  cout << "Server: Closed connection " << (size_t)connection.get() << " with status code " << status << endl;
};
    
//See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
echo.onerror=[](shared_ptr<WsServer::Connection> connection, const boost::system::error_code& ec) {
  cout << "Server: Error in connection " << (size_t)connection.get() << ". " << 
  "Error: " << ec << ", error message: " << ec.message() << endl;
};

thread server_thread([&server](){
    server.start();
      
  });
    
//Wait for server to start so that the client can connect
this_thread::sleep_for(chrono::seconds(1));
  
server_thread.join();
    
return 0;
}
#endif
