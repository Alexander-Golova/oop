#include "translator_utils.h"

void AddWordToDictionaryy(const std::string& word, const std::string& translationWord, Dictionary& dictionary, bool& isDictionaryChange)
{
	dictionary.insert({ word, translationWord });
	dictionary.insert({ translationWord, word });
	isDictionaryChange = true;
}

std::vector<std::string> FindWordInDictionary(const std::string& word, Dictionary& dictionary)
{
	auto translations = dictionary.equal_range(word);
	std::vector<std::string> values;

	for (auto it = translations.first; it != translations.second; ++it)
	{
		values.push_back(it->second);
	}
	return values;
}

void AddNewWord(const std::string& word, Dictionary& dictionary, bool& isDictionaryChange)
{
	std::cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа." << std::endl;
	std::cout << ">";
	std::string translation;
	getline(std::cin, translation);
	if (!translation.empty())
	{
		AddWordToDictionaryy(ToLowerCase(word), ToLowerCase(translation), dictionary, isDictionaryChange);
		std::cout << "Слово \"" + word + "\" сохранено в словаре как \"" + translation + "\"." << std::endl;
	}
	else
	{
		std::cout << "Слово \"" + word + "\" проигнорировано." << std::endl;
	}
}

void HandleNewWord(const std::string& word, Dictionary& dictionary, bool& isDictionaryChange)
{
	auto foundWords = FindWordInDictionary(word, dictionary);
	if (foundWords.empty())
	{
		AddNewWord(word, dictionary, isDictionaryChange);
	}
	else
	{
		for (size_t i = 0; i < foundWords.size(); ++i)
		{
			std::cout << foundWords[i] << " ";
		}
		std::cout << std::endl;
	}
}

void SaveDictionaryToFile(std::ofstream& output, const Dictionary& dictionary)
{
	for (const auto& pair : dictionary)
	{
		output << pair.first << std::endl
			   << pair.second << std::endl;
	}
}

void CompleteTranslation(std::ofstream& output, const Dictionary& dictionary)
{
	char ch;
	std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << std::endl;
	std::cout << ">";
	std::cin >> ch;
	if (ch == 'Y' || ch == 'y')
	{
		SaveDictionaryToFile(output, dictionary);
		std::cout << "Изменения сохранены. До свидания." << std::endl;
	}
	else
	{
		std::cout << "Изменения не сохранены. До свидания." << std::endl;
	}
}

void ReadDictionaryFromFile(std::ifstream& input, Dictionary& dictionary)
{
	std::string word, translationWord;
	while (getline(input, word))
	{
		if (getline(input, translationWord))
		{
			auto foundWords = FindWordInDictionary(word, dictionary);
			bool dictionaryChange = false;
			if (foundWords.empty())
			{
				AddWordToDictionaryy(word, translationWord, dictionary, dictionaryChange);
			}
		}
	}
}

void Translation(Dictionary& dictionary, bool& isDictionaryChange)
{
	std::string inputString;
	while (inputString != "...")
	{
		std::cout << ">";
		getline(std::cin, inputString);
		if (inputString != "...")
		{
			HandleNewWord(ToLowerCase(inputString), dictionary, isDictionaryChange);
		}
	}
}

bool CheckArgumentCount(const int argumentCount)
{
	if (argumentCount > 2)
	{
		std::cout << "Invalid argument count" << std::endl;
		std::cout << "translator [<input dictionary>]" << std::endl;
		return false;
	}
	return true;
}

std::string ToLowerCase(std::string str)
{
	std::locale loc;
	for (auto& ch : str)
	{
		ch = tolower(ch, loc);
	}
	return str;
}
