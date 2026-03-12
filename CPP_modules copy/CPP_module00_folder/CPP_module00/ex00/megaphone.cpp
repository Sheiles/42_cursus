#include <iostream>
#include <string>

static std::string toUpper(const std::string &s)
{
	std::string out = s;
	for (std::string::size_type i = 0; i < out.size(); ++i)
	{
		if (out[i] >= 'a' && out[i] <= 'z')
			out[i] = static_cast<char>(out[i] - 'a' + 'A');
	}
	return out;
}

int main(int argc, char **argv)
{
	if (argc <= 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return 0;
	}

	for (int i = 1; i < argc; ++i)
		std::cout << toUpper(argv[i]);

	std::cout << std::endl;
	return 0;
}
