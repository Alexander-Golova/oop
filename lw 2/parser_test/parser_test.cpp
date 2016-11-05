#include "stdafx.h"

#include "../parser/HTML_utils.h"
#include <tuple>

using namespace std;

void ExpectCorrectURL(const string& url, Protocol expectedProtocol, const string& expectedHost, int expectedPort, const string& exepectedDocument)
{
	string host, document;
	Protocol protocol;
	int port;
	BOOST_REQUIRE(ParseURL(url, protocol, port, host, document));
	BOOST_CHECK(
		tie(protocol, port, host, document) ==
		tie(expectedProtocol, expectedPort, expectedHost, exepectedDocument));
}

// Функция ParseURL
BOOST_AUTO_TEST_SUITE(Parse_URL_function)
	// извлекает протокол, хост, порт и документ из URL-а
	BOOST_AUTO_TEST_CASE(it_extracts_the_protocol_host_port_document_from_URL)
	{
		{
			ExpectCorrectURL("http://hostname:87/doc.txt", Protocol::HTTP, "hostname", 87, "doc.txt");
		}
		{
			ExpectCorrectURL("ftp://hostname:87/doc.txt", Protocol::FTP, "hostname", 87, "doc.txt");
		}
		{
			ExpectCorrectURL("https://hostname:87/doc.txt", Protocol::HTTPS, "hostname", 87, "doc.txt");
		}
	}
	// если порт не указан, возвращает его в зависимости от протокола
	BOOST_AUTO_TEST_CASE(if_the_port_is_not_specified_it_returns_depending_on_the_protocol)
	{
		{
			ExpectCorrectURL("http://www.mysite.com/doc.txt", Protocol::HTTP, "www.mysite.com", HTTP_PORT, "doc.txt");
		}
		{
			ExpectCorrectURL("ftp://www.mysite.com/doc.txt", Protocol::FTP, "www.mysite.com", FTP_PORT, "doc.txt");
		}
		{
			ExpectCorrectURL("https://www.mysite.com/doc.txt", Protocol::HTTPS, "www.mysite.com", HTTPS_PORT, "doc.txt");
		}
	}
	// игнорирует регистр символа протокола
	BOOST_AUTO_TEST_CASE(ignores_the_case_of_the_protocol_character)
	{
		{
			ExpectCorrectURL("HTTP://www.mysite.com/doc.txt", Protocol::HTTP, "www.mysite.com", HTTP_PORT, "doc.txt");
		}
		{
			ExpectCorrectURL("FTP://www.mysite.com/doc.txt", Protocol::FTP, "www.mysite.com", FTP_PORT, "doc.txt");
		}
		{
			ExpectCorrectURL("HTTPS://www.mysite.com/doc.txt", Protocol::HTTPS, "www.mysite.com", HTTPS_PORT, "doc.txt");
		}
	}

	// возвращает ошибку если
	BOOST_AUTO_TEST_SUITE(returns_an_error_if)
		// номер порта вне диапазона 1-65535
		BOOST_AUTO_TEST_CASE(port_number_out_of_range_1_65535)
		{
			{
				Protocol protocol;
				int port;
				std::string host;
				std::string document;
				BOOST_CHECK(!ParseURL("ftp://www.mysite.com:65536/doc.html", protocol, port, host, document));
			}
			{
				Protocol protocol;
				int port;
				std::string host;
				std::string document;
				BOOST_CHECK(!ParseURL("ftp://www.mysite.com:0/doc.html", protocol, port, host, document));
			}
		}
		// документ пустой
		BOOST_AUTO_TEST_CASE(empty_document)
		{		
			Protocol protocol;
			int port;
			std::string host;
			std::string document;
			BOOST_CHECK(!ParseURL("ftp://www.mysite.com", protocol, port, host, document));
		}
		// порт не является числом
		BOOST_AUTO_TEST_CASE(port_is_not_a_number)
		{
			Protocol protocol;
			int port;
			std::string host;
			std::string document;
			BOOST_CHECK(!ParseURL("ftp://www.mysite.com:aa/doc.txt", protocol, port, host, document));
		}
		// URL не содержит известных протоколов
		BOOST_AUTO_TEST_CASE(URL_it_does_not_contain_known_protocols)
		{
			Protocol protocol;
			int port;
			std::string host;
			std::string document;
			BOOST_CHECK(!ParseURL("ftps://www.mysite.com:56/doc.txt", protocol, port, host, document));
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
