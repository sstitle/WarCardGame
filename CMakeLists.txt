cmake_minimum_required(VERSION 3.10)

project(War VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(INC
include/Card.hpp 
include/Deck.hpp 
include/WarHelpers.hpp 
)

set(SRC 
source/Card.cpp 
source/Deck.cpp 
source/WarHelpers.cpp
)

add_executable(War main.cpp ${INC} ${SRC})
