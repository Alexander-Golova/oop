#include "pch.h"

#include "../parser/HTML_utils.h"

using namespace std;

// ќжидаем успех команды
void ExpectCorrectURL(const string& url, Protocol expectedProtocol, const string& expectedHost, int expectedPort, const string& exepectedDocument)
{
	string host, document;
	Protocol protocol;
	int port;
	REQUIRE(ParseURL(url, protocol, port, host, document));
	CHECK(tie(protocol, port, host, document) == tie(expectedProtocol, expectedPort, expectedHost, exepectedDocument));
}

// ‘ункци€ ParseURL извлекает протокол, хост, порт и документ из URL-а
TEST_CASE("Parse URL function extracts the protocol host port document from URL")
{
	ExpectCorrectURL("http://hostname:87/doc.txt", Protocol::HTTP, "hostname", 87, "doc.txt");
	ExpectCorrectURL("ftp://hostname:87/doc.txt", Protocol::FTP, "hostname", 87, "doc.txt");
	ExpectCorrectURL("https://hostname:87/doc.txt", Protocol::HTTPS, "hostname", 87, "doc.txt");
}
