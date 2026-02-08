#include "Contact.hpp"

Contact::Contact() : _isSet(false) {}

void Contact::setFirstName(const std::string &v) { _firstName = v; }
void Contact::setLastName(const std::string &v) { _lastName = v; }
void Contact::setNickname(const std::string &v) { _nickname = v; }
void Contact::setPhoneNumber(const std::string &v) { _phoneNumber = v; }
void Contact::setDarkestSecret(const std::string &v) { _darkestSecret = v; }

const std::string &Contact::getFirstName() const { return _firstName; }
const std::string &Contact::getLastName() const { return _lastName; }
const std::string &Contact::getNickname() const { return _nickname; }
const std::string &Contact::getPhoneNumber() const { return _phoneNumber; }
const std::string &Contact::getDarkestSecret() const { return _darkestSecret; }

void Contact::markSet(bool v) { _isSet = v; }
bool Contact::isSet() const { return _isSet; }
