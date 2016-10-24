#include "stdafx.h"
#include "HTML_utils.h"

using namespace std;

int main(int argc, char* argv[])
{
	string url;
	Protocol protocol;
	int port;
	string host;
	string document;

	while (!cin.eof())
	{
		getline(cin, url);
		ParseURL(url, protocol, port, host, document);
		cout << url << endl;
		cout << "HOST: " << host << endl;
		cout << "PORT: " << port << endl;
		cout << "DOC: " << document << endl;
	}

    return 0;
}
