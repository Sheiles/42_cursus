#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>

class Contact
{
private:
	std::string _firstName;
	std::string _lastName;
	std::string _nickname;
	std::string _phoneNumber;
	std::string _darkestSecret;
	bool        _isSet;

public:
	Contact();
	~Contact();

	void setFirstName(const std::string &v);
	void setLastName(const std::string &v);
	void setNickname(const std::string &v);
	void setPhoneNumber(const std::string &v);
	void setDarkestSecret(const std::string &v);

	const std::string &getFirstName() const;
	const std::string &getLastName() const;
	const std::string &getNickname() const;
	const std::string &getPhoneNumber() const;
	const std::string &getDarkestSecret() const;

	void markSet(bool v);
	bool isSet() const;
};

#endif
