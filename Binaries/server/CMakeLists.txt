cmake_minimum_required(VERSION 3.11)

set(TARGET_NAME "server")
add_executable(${TARGET_NAME}
  src/main.cpp
)

target_include_directories(${TARGET_NAME} PUBLIC include)

target_link_libraries(${TARGET_NAME} PUBLIC 
  messages::messages
  cppzmq::cppzmq
)