project(NoThanks)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-Wextra -Wall -O3 --std=c++11")

set(SRC_FILES src/main.cpp src/NoThanks.cpp src/Player.cpp  src/Deck.cpp src/Logger.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "CMakeModules/")

find_package(SFML COMPONENTS system window graphics audio REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
link_libraries(${EXE_NAME} ${SFML_LIBRARIES})

add_executable(NoThanks ${SRC_FILES})                                              
