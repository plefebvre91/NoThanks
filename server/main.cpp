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
  auto& echo=server.endpoint["^/nthx/?$"];
  
  NoThanks* app = new NoThanks();
  
  echo.onmessage=[&server,&app,&map_id](shared_ptr<WsServer::Connection> connection, shared_ptr<WsServer::Message> message) {
    auto message_str=message->string();
    auto id =  map_id[(size_t)connection.get()];
    auto response = app->dispatch(id, message_str);
    auto send_stream=make_shared<WsServer::SendStream>();

    cout << "\e[1mReceived : \e[0m" << message_str << std::endl;
    cout << "\e[1mResponse : \e[0m" << response << std::endl << std::endl;

    *send_stream << response;//message_str;

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

