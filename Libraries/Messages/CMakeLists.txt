cmake_minimum_required(VERSION 3.13)

# list proto files 
set(PROTO_SRCS "")
set(PROTO_HDRS "")
set(PROTO_FILES ${CMAKE_CURRENT_LIST_DIR}/proto/messages.proto)

# use protobuf_generate to get names of eventual generated .cc and .h files
protobuf_generate_cpp(
  PROTO_SRCS
  PROTO_HDRS
  APPEND_PATH
  PROTOS ${PROTO_FILES}
)

# define library and link protobuf lib
add_library(libmessages STATIC
  include/Messages/PersonBuilder.h
  src/PersonBuilder.cpp
  ${PROTO_HDRS}
  ${PROTO_SRCS}
)
target_include_directories(libmessages PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${CMAKE_CURRENT_BINARY_DIR}
)
add_library(messages::messages ALIAS libmessages)

target_link_libraries(libmessages PUBLIC protobuf::protobuf)

