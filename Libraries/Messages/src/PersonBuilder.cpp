#include <Messages/PersonBuilder.h>

namespace messages
{
// -------------------------------------------------------------------------
auto PersonBuilder::set_name(const std::string &name) -> PersonBuilder&
{
  m_name = name;
  return *this;
}

// -------------------------------------------------------------------------
auto PersonBuilder::set_id(int id) -> PersonBuilder&
{
  m_id = id;
  return *this;
}

// -------------------------------------------------------------------------
auto PersonBuilder::set_email(const std::string &email) -> PersonBuilder&
{
  m_email = email;
  return *this;
}

// -------------------------------------------------------------------------
auto PersonBuilder::add_phone(PhoneType type, const std::string &number) -> PersonBuilder&
{
  m_phones.push_back({type, number});
  return *this;
}

// -------------------------------------------------------------------------
auto PersonBuilder::build() -> messages::Person
{
  auto person = messages::Person();
  person.set_name(m_name);
  person.set_id(m_id);
  person.set_email(m_email);

  for (const auto& phone: m_phones)
  {
    auto temp_phone = person.add_phones();
    temp_phone->set_number(phone.number);
    switch (phone.type)
    {
      case PhoneType::MOBILE:
        temp_phone->set_type(messages::Person::MOBILE);
        break;
      case PhoneType::HOME:
        temp_phone->set_type(messages::Person::HOME);
        break;
      case PhoneType::WORK:
        temp_phone->set_type(messages::Person::WORK);
        break;
    }
  }
  return person;
}
}