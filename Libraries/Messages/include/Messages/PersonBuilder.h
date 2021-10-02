#pragma once

#include <messages.pb.h>

#include <string>
#include <vector>

namespace messages
{

enum class PhoneType
{
  MOBILE,
  HOME,
  WORK
};

class PersonBuilder
{
public:

  // chainable settings
  auto set_name(const std::string& name) -> PersonBuilder&;
  auto set_id(int id) -> PersonBuilder&;
  auto set_email(const std::string& email) -> PersonBuilder&;
  auto add_phone(PhoneType type, const std::string& number) -> PersonBuilder&;
  auto build() -> messages::Person;

private:
  struct Phone
  {
    PhoneType type;
    std::string number;
  };

  // members
  std::string m_name;
  int m_id;
  std::string m_email;
  std::vector<Phone> m_phones;
};

}