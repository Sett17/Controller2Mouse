cmake_minimum_required(VERSION 3.19)
project(Controller2Mouse)

set(CMAKE_CXX_STANDARD 14)

add_executable(Controller2Mouse main.cpp Controller.cpp Controller.h setInterval.cpp Sender.cpp Sender.h)