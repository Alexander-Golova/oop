#pragma once

typedef std::multimap<std::string, std::string> Dictionary;


void ReadDictionaryFromFile(std::ifstream & input, Dictionary & dictionary);

void AddWordToDictionaryy(const std::string & word, const std::string & translationWord, Dictionary & dictionary);

void SaveDictionaryToFile(std::ofstream & output, Dictionary & dictionary);

std::vector<std::string> FindWordInDictionary(const std::string & word, Dictionary  & dictionary);


bool CheckArgumentCount(const int argumentCount);

void Translation(std::ofstream & output, Dictionary & dictionary);

void AddNewWordToDictionary(const std::string & word, Dictionary & dictionary);

void HandleNewWord(const std::string & str, Dictionary & dictionary);

void CompleteTranslation(std::ofstream & output, Dictionary & dictionary);
