project(NoThanks)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-Wextra -Wall --std=c++11")
include_directories(server/ server/players)
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


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

link_libraries(${EXE_NAME} boost_system boost_chrono pthread)

add_executable(NoThanks ${SRC_FILES})                                              
