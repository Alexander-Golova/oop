#include "pch.h"

void ReplaceTextInFile(std::ifstream& input, std::ofstream& output, const std::string& searchString, const std::string& replacingString)
{
	std::string currentString;
	std::string resultString;
	std::string::size_type initialPos;
	std::string::size_type pos;

	while (std::getline(input, currentString))
	{
		resultString.clear();
		initialPos = 0;
		if (currentString.find(searchString) != std::string::npos)
		{
			for (pos = 0; (pos = currentString.find(searchString, initialPos)) != std::string::npos; initialPos = pos + searchString.length())
			{
				resultString.append(currentString, initialPos, pos - initialPos);
				resultString.append(replacingString);
			}
		}
		resultString.append(currentString, initialPos);
		output << resultString << std::endl;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cerr << "Invalid arguments count" << std::endl;
		std::cerr << "Usage: replace <input file> <output file> <search string> <replace string>" << std::endl;
		return 1;
	}

	std::ifstream input(argv[1]);
	if (!input.is_open())
	{
		std::cerr << "Failed to open " << argv[1] << " for reading" << std::endl;
		return 1;
	}

	std::ofstream output(argv[2]);
	if (!output.is_open())
	{
		std::cerr << "Failed to open " << argv[2] << " for writing" << std::endl;
		return 1;
	}

	const std::string searchingString = argv[3];
	const std::string replacingString = argv[4];
	if (searchingString.length() == 0)
	{
		std::cerr << "<search string> must be not empty" << std::endl;
		return 1;
	}

	ReplaceTextInFile(input, output, searchingString, replacingString);

	return 0;
} 


