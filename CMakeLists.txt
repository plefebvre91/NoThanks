project(NoThanks)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-Wextra -Wall -O3 --std=c++11")



set(SRC_FILES server/main.cpp 
  server/NoThanks.cpp 
  server/Player.cpp 
  server/PlayerHuman.cpp
  server/PlayerRandom.cpp
  server/PlayerAverage.cpp
  server/Deck.cpp
  server/Card.cpp
  server/Logger.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

link_libraries(${EXE_NAME})

add_executable(NoThanks ${SRC_FILES})                                              
