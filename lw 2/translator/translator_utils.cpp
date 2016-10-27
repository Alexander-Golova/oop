#include "stdafx.h"
#include <boost/range/adaptor/map.hpp>

#include "translator_utils.h"

using namespace std;


bool CheckArgumentCount(const int argumentCount)
{
	if (argumentCount > 2)
	{
		cout << "Invalid argument count" << endl;
		cout << "translator [<input dictionary>]" << endl;
		return false;
	}
	return true;
}

string ToLowCase(string str)
{
	locale loc;
	for (auto & ch : str)
	{
		ch = tolower(ch, loc);
	}
	return str;
}

void ReadDictionaryFromFile(ifstream & input, Dictionary & dictionary)
{
	string word, translationWord;
	while (getline(input, word))
	{
		getline(input, translationWord);
		auto foundWords = FindWordInDictionary(word, dictionary);
		if (foundWords.empty())
		{
			AddWordToDictionaryy(word, translationWord, dictionary);
		}
	}
}

void Translation(const string & fileName, Dictionary & dictionary)
{
	bool dictionaryChange = false;
	string inputString;
	while (inputString != "...")
	{
		cout << ">";
		getline(cin, inputString);
		if (inputString != "...")
		{
			HandleNewWord(ToLowCase(inputString), dictionary, dictionaryChange);
		}
	}
	if (dictionaryChange)
	{
		CompleteTranslation(fileName, dictionary);
	}
	else
	{
		cout << "До свидания." << endl;
	}	
}

void HandleNewWord(const string & word, Dictionary & dictionary, bool & dictionaryChange)
{
	auto foundWords = FindWordInDictionary(word, dictionary);
	if (foundWords.empty())
	{
		AddNewWord(word, dictionary, dictionaryChange);
	}
	else
	{
		for (size_t i = 0; i < foundWords.size(); ++i)
		{
			cout << foundWords[i] << " ";
		}
		cout << endl;
		dictionaryChange = false;
	}
}

void CompleteTranslation(const string & fileName, Dictionary & dictionary)
{
	char ch;
	cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << endl;
	cout << ">";
	cin >> ch;
	if (ch == 'Y' || ch == 'y')
	{
		ofstream output(fileName);
		SaveDictionaryToFile(output, dictionary);
		cout << "Изменения сохранены. До свидания." << endl;
	}
	else
	{
		cout << "Изменения не сохранены. До свидания." << endl;
	}
}

void AddNewWord(const string & word, Dictionary & dictionary, bool & dictionaryChange)
{
	cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа." << endl;
	cout << ">";
	string translation;
	getline(cin, translation);
	if (!translation.empty())
	{
		AddWordToDictionaryy(word, translation, dictionary);
		cout << "Слово \"" + word + "\" сохранено в словаре как \"" + translation + "\"." << endl;
		dictionaryChange = true;
	}
	else
	{
		cout << "Слово \"" + word + "\" проигнорировано." << endl;
		dictionaryChange = false;
	}
}

void AddWordToDictionaryy(const string & word, const string & translationWord, Dictionary & dictionary)
{
	dictionary.insert({ word, translationWord });
	dictionary.insert({ translationWord, word });
}

void SaveDictionaryToFile(ofstream & output, Dictionary & dictionary)
{
	auto it = dictionary.begin();
	for (it = dictionary.begin(); it != dictionary.end(); ++it)
	{
		output << (*it).first << endl
			   << (*it).second << endl;
	}
}

vector<string> FindWordInDictionary(const string & word, Dictionary  & dictionary)
{
	auto translations = dictionary.equal_range(word) | boost::adaptors::map_values;
	return{ translations.begin(), translations.end() };
}



