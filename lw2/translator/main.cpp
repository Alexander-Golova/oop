#include "pch.h"


#include "translator_utils.h"

using namespace std;

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (!CheckArgumentCount(argc))
	{
		return 1;
	}

	string fileName;
	Dictionary dictionary;
	if (argc == 2)
	{
		fileName = argv[1];
		ifstream input(fileName);
		if (input.is_open())
		{
			ReadDictionaryFromFile(input, dictionary);
			input.close();
		}
	}
	else
	{
		fileName = "dictionary.txt";
	}

	Translation(fileName, dictionary);

	return 0;
}
