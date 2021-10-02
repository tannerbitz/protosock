#include "messages.pb.h"

#include <zmq.hpp>

#include <iostream>

int main(int argc, char**argv)
{
  auto ctx = zmq::context_t();
  auto socket = zmq::socket_t(ctx, zmq::socket_type::req);

  try {
    socket.connect("tcp://127.0.0.1:5555");
  } catch (const zmq::error_t& err) {
    std::cout << err.what() << std::endl;
    exit;
  }

  auto req = messages::Request();
  req.set_request(messages::RequestType::WHO_ARE_YOU);

  std::cout << "Sending WHO_ARE_YOU request" << std::endl;
  socket.send(
    zmq::message_t(req.SerializeAsString()),
    zmq::send_flags::dontwait);
  std::cout << "Request sent" << std::endl;

  std::vector<zmq::pollitem_t> items;
  items.push_back({socket, 0, ZMQ_POLLIN, 0});

  try {
    zmq::poll(items);
  } catch (const zmq::error_t& err) {
    std::cout << err.what() << std::endl;
    exit;
  }

  if (!(items[0].revents & ZMQ_POLLIN))
  {
    std::cout << "Poll failed... closing" << std::endl;
    exit;
  }

  zmq::message_t msg;
  socket.recv(msg, zmq::recv_flags::none);

  auto person = messages::Person();
  person.ParseFromString(msg.to_string());

  std::cout << "Who they are: " << std::endl << person.DebugString() << std::endl;

  return 0;
}