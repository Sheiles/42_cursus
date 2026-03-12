#include <iostream>
#include <string>

static std::string toUpper(const std::string &s)
{
	std::string out = s;
	std::string::size_type i = 0;
	while (i < out.size())
	{
		if (out[i] >= 'a' && out[i] <= 'z')
			out[i] = static_cast<char>(out[i] - 'a' + 'A');
		++i;
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

	int i = 1;
	while (i < argc)
	{
		std::cout << toUpper(argv[i]);
		++i;
	}

	std::cout << std::endl;
	return 0;
}
