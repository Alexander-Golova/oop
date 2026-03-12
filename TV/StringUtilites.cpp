#include "StringUtilites.h"

void RemoveExtraBlanks(std::string& str)
{
	if (str.empty())
		return;

	size_t write = 0;
	size_t read = 0;
	bool inSpace = false;

	// Пропускаем начальные пробелы
	while (read < str.length() && std::isspace(static_cast<unsigned char>(str[read])))
	{
		read++;
	}

	while (read < str.length())
	{
		if (std::isspace(static_cast<unsigned char>(str[read])))
		{
			if (!inSpace)
			{
				str[write++] = ' ';
				inSpace = true;
			}
		}
		else
		{
			str[write++] = str[read];
			inSpace = false;
		}
		read++;
	}

	// Удаляем trailing пробел
	if (write > 0 && str[write - 1] == ' ')
	{
		write--;
	}
	str.resize(write);
}
