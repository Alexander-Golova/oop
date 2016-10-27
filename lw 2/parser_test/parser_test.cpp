#include "stdafx.h"

#include "../parser/HTML_utils.h"


BOOST_AUTO_TEST_SUITE(MyTest)

BOOST_AUTO_TEST_CASE(Parse_URL)
{
	{
		std::string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		Protocol protocol;
		int port;
		std::string host;
		std::string document;
		bool valid = ParseURL(url, protocol, port, host, document);
		const Protocol correctProtocol = Protocol::HTTP;
		const int correctPort = HTTP_PORT;
		const std::string correctHost = "www.mysite.com";
		const std::string correctDoc = "docs/document1.html?page=30&lang=en#title";
		BOOST_CHECK(protocol == correctProtocol);
		BOOST_CHECK(port == correctPort);
		BOOST_CHECK(host == correctHost);
		BOOST_CHECK(document == correctDoc);
	}
	{
		std::string url = "https://www.mysite.com/docs/document1";
		Protocol protocol;
		int port;
		std::string host;
		std::string document;
		bool valid = ParseURL(url, protocol, port, host, document);
		const Protocol correctProtocol = Protocol::HTTPS;
		const int correctPort = HTTPS_PORT;
		const std::string correctHost = "www.mysite.com";
		const std::string correctDoc = "docs/document1";
		BOOST_CHECK(protocol == correctProtocol);
		BOOST_CHECK(port == correctPort);
		BOOST_CHECK(host == correctHost);
		BOOST_CHECK(document == correctDoc);
	}
	{
		std::string url = "ftp://www.mysite.com/docs/document2";
		Protocol protocol;
		int port;
		std::string host;
		std::string document;
		bool valid = ParseURL(url, protocol, port, host, document);
		const Protocol correctProtocol = Protocol::FTP;
		const int correctPort = FTP_PORT;
		const std::string correctHost = "www.mysite.com";
		const std::string correctDoc = "docs/document2";
		BOOST_CHECK(protocol == correctProtocol);
		BOOST_CHECK(port == correctPort);
		BOOST_CHECK(host == correctHost);
		BOOST_CHECK(document == correctDoc);
	}
	{
		std::string url = "ftp://www.mysite.com:1/docs/document1.html";
		Protocol protocol;
		int port;
		std::string host;
		std::string document;
		bool valid = ParseURL(url, protocol, port, host, document);
		const Protocol correctProtocol = Protocol::FTP;
		const int correctPort = 1;
		const std::string correctHost = "www.mysite.com";
		const std::string correctDoc = "docs/document1.html";
		BOOST_CHECK(protocol == correctProtocol);
		BOOST_CHECK(port == correctPort);
		BOOST_CHECK(host == correctHost);
		BOOST_CHECK(document == correctDoc);
	}
	{
		std::string url = "FTP://www.mysite.com:1/docs/document1.html";
		Protocol protocol;
		int port;
		std::string host;
		std::string document;
		bool valid = ParseURL(url, protocol, port, host, document);
		const Protocol correctProtocol = Protocol::FTP;
		const int correctPort = 1;
		const std::string correctHost = "www.mysite.com";
		const std::string correctDoc = "docs/document1.html";
		BOOST_CHECK(protocol == correctProtocol);
		BOOST_CHECK(port == correctPort);
		BOOST_CHECK(host == correctHost);
		BOOST_CHECK(document == correctDoc);
	}
	{
		std::string url = "HTTP://www.mysite.com/doc/69i57j0l5.667j0j7&sourceid=chrome&ie=UTF-8";
		Protocol protocol;
		int port;
		std::string host;
		std::string document;
		bool valid = ParseURL(url, protocol, port, host, document);
		const Protocol correctProtocol = Protocol::HTTP;
		const int correctPort = HTTP_PORT;
		const std::string correctHost = "www.mysite.com";
		const std::string correctDoc = "doc/69i57j0l5.667j0j7&sourceid=chrome&ie=UTF-8";
		BOOST_CHECK(protocol == correctProtocol);
		BOOST_CHECK(port == correctPort);
		BOOST_CHECK(host == correctHost);
		BOOST_CHECK(document == correctDoc);
	}
	{
		std::string url = "ftp://www.mysite.com:65536/docs/document1.html";
		Protocol protocol;
		int port;
		std::string host;
		std::string document;
		bool invalid = ParseURL(url, protocol, port, host, document);
		BOOST_CHECK(invalid == false);
	}
	{
		std::string url = "ftp://www.mysite.com:0/docs/document1.html";
		Protocol protocol;
		int port;
		std::string host;
		std::string document;
		bool invalid = ParseURL(url, protocol, port, host, document);
		BOOST_CHECK(invalid == false);
	}
	{
		std::string url = "ftpp://www.mysite.com:0/docs/document1.html";
		Protocol protocol;
		int port;
		std::string host;
		std::string document;
		bool invalid = ParseURL(url, protocol, port, host, document);
		BOOST_CHECK(invalid == false);
	}
}
BOOST_AUTO_TEST_SUITE_END()