project(NoThanks)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-Wextra -Wall --std=c++11 -lcrypto")

include_directories(server/ server/players server/network)

#Only tested with versions 1.55 and 1.56
find_package(Boost 1.54.0 COMPONENTS system regex coroutine context thread REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

if(APPLE)
  set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
endif()

#TODO: add requirement for version 1.0.1g (can it be done in one line?)
find_package(OpenSSL REQUIRED)


include_directories(${OPENSSL_INCLUDE_DIR})

find_package(Threads REQUIRED)



set(SRC_FILES server/main.cpp 
  server/NoThanks.cpp 
  server/players/Player.cpp 
  server/players/PlayerHuman.cpp
  server/players/PlayerRandom.cpp
  server/players/PlayerAverage.cpp
  server/Deck.cpp
  server/Card.cpp
  server/Logger.cpp
  server/Parser.cpp)

#target_link_libraries(NoThanks ${CMAKE_THREAD_LIBS_INIT})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


link_libraries(NoThanks boost_system boost_chrono pthread crypto ssl boost_regex)

add_executable(NoThanks ${SRC_FILES})                                              
