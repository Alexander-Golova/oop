#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <Windows.h>


typedef std::multimap<std::string, std::string> Dictionary;


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
		AddWordToDictionaryy(word, translation, dictionary, isDictionaryChange);
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







int main()
{
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251);

	Dictionary dictionary;
	bool isDictionaryChange;

	HandleNewWord("cat", dictionary, isDictionaryChange);
	HandleNewWord("кот", dictionary, isDictionaryChange);

	HandleNewWord("cat", dictionary, isDictionaryChange);
	

}
