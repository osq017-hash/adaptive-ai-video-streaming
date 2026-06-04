cmake_minimum_required(VERSION 3.10)
project(adaptive_ai_videostreaming)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(sender
	src/main_sender.cpp
)

add_executable(receiver
	src/main_receiver.cpp
)
