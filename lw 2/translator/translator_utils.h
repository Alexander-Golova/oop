#pragma once

#include "stdafx.h"
#include <boost/range/adaptor/map.hpp>


typedef multimap<string, string> Dictionary;


void ReadDictionaryFromFile(ifstream & input, Dictionary & dictionary);

void AddWordToDictionaryy(const string & word, const string & translationWord, Dictionary & dictionary);

void SaveDictionaryToFile(ofstream & output, Dictionary & dictionary);

vector<string> FindWordInDictionary(const string & word, Dictionary  & dictionary);


bool CheckArgumentCount(const int argumentCount);

void Translation(Dictionary & dictionary);

void AddANewWordToDictionary(const string & word, Dictionary & dictionary);

void HandleNewWord(const string & str, Dictionary & dictionary);

void CompleteTranslation(ofstream & output, Dictionary & dictionary);
