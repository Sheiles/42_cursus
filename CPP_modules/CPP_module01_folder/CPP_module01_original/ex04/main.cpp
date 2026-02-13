#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
		return 1;
	}

	std::string filename = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];

	if (s1.empty())
	{
		std::cerr << "Error: s1 cannot be empty" << std::endl;
		return 1;
	}

	std::ifstream inputFile(filename.c_str());
	if (!inputFile.is_open())
	{
		std::cerr << "Error: cannot open file " << filename << std::endl;
		return 1;
	}

	std::string outputFilename = filename + ".replace";
	std::ofstream outputFile(outputFilename.c_str());
	if (!outputFile.is_open())
	{
		std::cerr << "Error: cannot create output file " << outputFilename << std::endl;
		inputFile.close();
		return 1;
	}

	std::string line;
	while (std::getline(inputFile, line))
	{
		size_t pos = 0;
		while ((pos = line.find(s1, pos)) != std::string::npos)
		{
			line.erase(pos, s1.length());
			line.insert(pos, s2);
			pos += s2.length();
		}
		outputFile << line << std::endl;
	}

	inputFile.close();
	outputFile.close();

	std::cout << "File processed successfully: " << outputFilename << std::endl;

	return 0;
}
