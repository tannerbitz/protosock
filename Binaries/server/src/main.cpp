#include <Messages/PersonBuilder.h>

#include <zmq.hpp>

#include <iostream>

// -------------------------------------------------------------------------

int main(int argc, char** argv)
{
  auto ctx = zmq::context_t();
  auto socket = zmq::socket_t(ctx, zmq::socket_type::rep);
  try {
    auto address = "tcp://127.0.0.1:5555";
    socket.bind(address);
    socket.connect(address);
  } catch (const zmq::error_t& err) {
    std::cout << err.what() << std::endl;
    exit;
  }

  std::vector<zmq::pollitem_t> poll_items;
  poll_items.push_back({ socket, 0, ZMQ_POLLIN, 0 });
  
  std::cout << "Waiting for request..." << std::endl;
  try {
    zmq::poll(poll_items);
  } catch (const zmq::error_t& err) {
    std::cout << err.what() << std::endl;
    exit;
  }

  if (!(poll_items[0].revents & ZMQ_POLLIN))
  {
    std::cout << "Poll failed... closing" << std::endl;
    exit;
  }

  zmq::message_t msg;
  socket.recv(msg, zmq::recv_flags::dontwait);
  auto request = messages::Request();
  request.ParseFromString(msg.to_string());

  std::cout << "Received request: " << request.DebugString() << std::endl;

  if (request.request() != messages::RequestType::WHO_ARE_YOU)
  {
    std::cout << "Unrecognized request... closing" << std::endl;
    exit;
  }

  auto person = 
    messages::PersonBuilder()
    .set_name("John Doe")
    .set_id(1234)
    .set_email("jdoe@somewhere.com")
    .add_phone(messages::PhoneType::MOBILE, "555-555-5555")
    .add_phone(messages::PhoneType::MOBILE, "777-777-7777")
    .build();

  std::cout << "Sending reply" << std::endl;
  socket.send(
      zmq::message_t(person.SerializeAsString()),
      zmq::send_flags::none);

  return 0;
}