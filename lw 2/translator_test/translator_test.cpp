#include "stdafx.h"

#include "../translator/translator_utils.h"

using namespace std;

bool VectorsAreEqual(std::vector<string> const& x, vector<string> const& y)
{
	return x == y;
}

// функция ToLowerCase
BOOST_AUTO_TEST_SUITE(To_Lower_Case_function)
	// Переводит в нижний регистр английские слова
	BOOST_AUTO_TEST_CASE(translations_into_lowercase_English_words)
	{
		{
			BOOST_CHECK_EQUAL(ToLowerCase("Cat"), "cat");
		}
		{
			BOOST_CHECK_EQUAL(ToLowerCase("cAt"), "cat");
		}
		{
			BOOST_CHECK_EQUAL(ToLowerCase("CAT"), "cat");
		}
	}
	// не изменяет регистр русских букв
	BOOST_AUTO_TEST_CASE(it_does_not_change_the_case_of_russian_letters)
	{
		BOOST_CHECK_EQUAL(ToLowerCase("КошКа"), "КошКа");
	}
	BOOST_AUTO_TEST_SUITE_END()

	// словарь
	BOOST_AUTO_TEST_SUITE(Dictionary_)
		Dictionary dictionary;
		//может быть считан из файла
		BOOST_AUTO_TEST_CASE(it_can_be_read_from_the_file)
		{
			ifstream input("dictionary.txt");
			ReadDictionaryFromFile(input, dictionary);
			auto words = FindWordInDictionary("кошка", dictionary);
			BOOST_CHECK(VectorsAreEqual(words, { "cat" }));
		}
		// может быть записан в файл
		BOOST_AUTO_TEST_CASE(it_can_be_written_to_a_file)
		{
			ifstream input("dictionary.txt");
			ReadDictionaryFromFile(input, dictionary);
			ofstream output("dictionary1.txt");
			SaveDictionaryToFile(output, dictionary);
			output.close();
			Dictionary newDictionary;
			ifstream newInput("dictionary1.txt");
			ReadDictionaryFromFile(newInput, newDictionary);
			BOOST_CHECK(dictionary == newDictionary);
		}
		// может быть пополнен словом, если его в словаре не было
		BOOST_AUTO_TEST_CASE(it_can_be_refilled_in_short_if_it_was_not_in_the_dictionary)
		{
			ifstream input("dictionary.txt");
			ReadDictionaryFromFile(input, dictionary);
			bool dictionaryChange = false;
			AddWordToDictionaryy("red", "красный", dictionary, dictionaryChange);
			BOOST_CHECK(dictionaryChange);
		}
		// если изменен, то 
		BOOST_AUTO_TEST_SUITE(if_changed)
			// происходит запрос записи словаря в файл
			BOOST_AUTO_TEST_CASE(there_is_a_write_request_dictionary_file)
			{
				ifstream input("dictionary.txt");
				ReadDictionaryFromFile(input, dictionary);
				bool dictionaryChange = false;
				AddWordToDictionaryy("red", "красный", dictionary, dictionaryChange);
				BOOST_CHECK(dictionaryChange);
			}
			// если последнее действие приводило к нахождению существующего слова
			BOOST_AUTO_TEST_CASE(if_the_last_action_led_to_the_determination_of_the_current_word)
			{
				ifstream input("dictionary.txt");
				ReadDictionaryFromFile(input, dictionary);
				bool dictionaryChange = false;
				AddWordToDictionaryy("the word is found", "слово найдено", dictionary, dictionaryChange);
				cout << "        ";
				HandleNewWord("слово найдено", dictionary, dictionaryChange);
				BOOST_CHECK(dictionaryChange);
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	// перевод
	BOOST_AUTO_TEST_SUITE(translation)

		// на русский может быть выполнен, если слово есть в словаре
		BOOST_AUTO_TEST_CASE(when_find_russian_word_returns_vector_with_english_translates)
		{
			Dictionary dictionary;
			bool dictionaryChange = false;
			AddWordToDictionaryy("cat", "кошка", dictionary, dictionaryChange);
			auto words = FindWordInDictionary("cat", dictionary);
			BOOST_CHECK(VectorsAreEqual(words, { "кошка" }));
		}
		// на английский может быть выполнен, если слово есть в словаре
		BOOST_AUTO_TEST_CASE(english_can_be_made_if_the_word_is_in_the_dictionary)
		{
			Dictionary dictionary;
			bool dictionaryChange = false;
			AddWordToDictionaryy("cat", "кошка", dictionary, dictionaryChange);
			auto words = FindWordInDictionary("кошка", dictionary);
			BOOST_CHECK(VectorsAreEqual(words, { "cat" }));
		}
		// слова с несколькими значениями может быть выполнен
		BOOST_AUTO_TEST_CASE(words_with_multiple_values_can_be_made)
		{
			Dictionary dictionary;
			bool dictionaryChange = false;
			AddWordToDictionaryy("cat", "кошка", dictionary, dictionaryChange);
			AddWordToDictionaryy("кот", "cat", dictionary, dictionaryChange);
			auto words = FindWordInDictionary("cat", dictionary);
			BOOST_CHECK(VectorsAreEqual(words, { "кошка", "кот" }));
		}		

	BOOST_AUTO_TEST_SUITE_END()
