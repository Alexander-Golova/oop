#include "stdafx.h"

#include "translator_utils.h"

using namespace std;


void ReadDictionaryFromFile(ifstream & input, Dictionary & dictionary)
{
	string word, translationWord;
	while (getline(input, word))
	{
		getline(input, translationWord);
		AddWordToDictionaryy(word, translationWord, dictionary);
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

void Translation(Dictionary & dictionary)
{
	string inputString;
	while (inputString != "...")
	{
		cout << ">";
		getline(cin, inputString);
		if (inputString != "...")
		{
			HandleNewWord(inputString, dictionary);
		}
	}
	CompleteTranslation(dictionary);
}

void HandleNewWord(const string & word, Dictionary & dictionary)
{
	auto foundWords = FindWordInDictionary(word, dictionary);
	if (foundWords.empty())
	{
		AddANewWordToDictionary(word, dictionary);
	}
	else
	{
		for (size_t i = 0; i < foundWords.size(); ++i)
		{
			cout << foundWords[i] << " ";
		}
		cout << endl;
	}	
}

void AddANewWordToDictionary(const string & word, Dictionary & dictionary)
{
	cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа." << endl;
	cout << ">";
	string translation;
	getline(cin, translation);
	if (!translation.empty())
	{
		AddWordToDictionaryy(word, translation, dictionary);
		cout << "Слово \"" + word + "\" сохранено в словаре как \"" + translation + "\"." << endl;
	}
	else
	{
		cout << "Слово \"" + word + "\" проигнорировано." << endl;
	}	
}

void CompleteTranslation(ofstream & output, Dictionary & dictionary)
{
	char ch;
	cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << endl;
	cin >> ch;
	if (ch == 'Y' || ch == 'y')
	{
		SaveDictionaryToFile(output, dictionary);		
		cout << "Изменения сохранены. До свидания." << endl;
	}
	else
	{
		cout << "Изменения не сохранены. До свидания." << endl;
	}
}
