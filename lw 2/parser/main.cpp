#include "stdafx.h"
#include "HTML_utils.h"

using namespace std;

int main()
{
	string url;
	Protocol protocol;
	int port;
	string host;
	string document;

	while (getline(cin, url))
	{
		if (ParseURL(url, protocol, port, host, document))
		{
			cout << url << endl;
			cout << "HOST: " << host << endl;
			cout << "PORT: " << port << endl;
			cout << "DOC: " << document << endl;
		}
		else
		{
			cout << "The specified URL is invalid" << endl;
		}
	}
    return 0;
}
