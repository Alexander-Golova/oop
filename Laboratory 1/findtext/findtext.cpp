#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		std::cerr << "Invalid arguments count" << std::endl
			<< "Usage: findtext <file name> <text to search>" << std::endl;
		return 1;
	}

	std::ifstream input(argv[1]);
	if (!input.is_open())
	{
		std::cerr << "Failed to open " << argv[1] << " for reading" << std::endl;
		return 1;
	}

	std::string searshingString = argv[2];
	if (!searshingString.length())
	{
		std::cerr << "Searching string must be not empty" << std::endl;
		return 1;
	}

	bool isFound = false;
	unsigned strNum = 0;
	while (!input.eof())
	{
		std::string currentStr = "";
		std::getline(input, currentStr);
		if (currentStr.find(searshingString) != std::string::npos)
		{
			std::cout << searshingString << " was founded on the " << strNum << " line" << std::endl;
			isFound = true;
		}
		++strNum;
	}

	if (!isFound)
	{
		std::cout << "Text not found" << std::endl;
	}

	return 0;
}