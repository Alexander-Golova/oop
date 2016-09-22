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

	std::string searchString = argv[2];
	if (searchString.empty())
	{
		std::cerr << "Searching string must be not empty" << std::endl;
		return 1;
	}

	bool isFound = false;
	std::string currentStr;
	unsigned strNum = 1;
	while (std::getline(input, currentStr))
	{
		if (currentStr.find(searchString) != std::string::npos)
		{
			std::cout << "\"" << searchString << "\" was found on the " << strNum << " line" << std::endl;
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