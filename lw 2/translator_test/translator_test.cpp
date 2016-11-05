#include "stdafx.h"

#include "../translator/translator_utils.h"

using namespace std;


// ������� ToLowerCase
BOOST_AUTO_TEST_SUITE(To_Lower_Case_function)
	// ��������� � ������ ������� ���������� �����
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
	// �� �������� ������� ������� ����
	BOOST_AUTO_TEST_CASE(it_does_not_change_the_case_of_russian_letters)
	{
		{
			BOOST_CHECK_EQUAL(ToLowerCase("�����"), "�����");
		}
	}
BOOST_AUTO_TEST_SUITE_END()

// �������

	//����� ���� ������ �� �����

	// ����� ���� ������� � ����

	// ���������� ������ �� ������, ������ � ������, ���� ������� ��� �������
		
		// ���� ��������� �������� ���� �������� ����� � �������

		// ���� ��������� �������� ��������� � ���������� ������������� �����

		// ���� ��������� �������� ��������� � ������ ���������� ����� � �������

// �������
	
	// �� ������� ����� ���� ��������, ���� ����� ���� � �������

	// �� ���������� ����� ���� ��������, ���� ���� ���� ���� � �������

	// ���� � ����� ���� ��������� ��������, �� ��� �������� ��������� ���