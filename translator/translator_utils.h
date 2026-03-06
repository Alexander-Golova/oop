#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <locale>


typedef std::multimap<std::string, std::string> Dictionary;

void AddWordToDictionaryy(const std::string& word, const std::string& translationWord, Dictionary& dictionary, bool& isDictionaryChange);
std::vector<std::string> FindWordInDictionary(const std::string& word, Dictionary& dictionary);
void AddNewWord(const std::string& word, Dictionary& dictionary, bool& isDictionaryChange);
void HandleNewWord(const std::string& word, Dictionary& dictionary, bool& isDictionaryChange);
void SaveDictionaryToFile(std::ofstream& output, const Dictionary& dictionary);
void CompleteTranslation(std::ofstream& output, const Dictionary& dictionary);
void ReadDictionaryFromFile(std::ifstream& input, Dictionary& dictionary);
void Translation(Dictionary& dictionary, bool& isDictionaryChange);
bool CheckArgumentCount(const int argumentCount);
std::string ToLowerCase(std::string str);
