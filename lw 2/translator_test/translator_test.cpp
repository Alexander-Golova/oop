#include "stdafx.h"

#include "../translator/translator_utils.h"

using namespace std;


// функция ToLowerCase
BOOST_AUTO_TEST_SUITE(To_Lower_Case_function)
	// Переводит в нижний регистр английские слова
	BOOST_AUTO_TEST_CASE(Translations_into_lowercase_English_words)
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
		{
			BOOST_CHECK_EQUAL(ToLowerCase("КошКа"), "КошКа");
		}
	}
BOOST_AUTO_TEST_SUITE_END()

// словарь

	//может быть считан из файла

	// может быть записан в файл

	// происходит запрос на запись, только в случае, если словарь был изменен
		
		// если последнее действие было дабавить слово в словарь

		// если последнее действие приводило к нахождению существующего слова

		// если последнее действие приводило к отмене добавления слова в словарь

	// в словарь может быть добавлено пара слов

// перевод
	
	// на русский может быть выполнен, если слово есть в словаре

	// на английский может быть выполнен, если слово есть в словаре

	// если у слова есть несколько значений, то при переводе выводятся все